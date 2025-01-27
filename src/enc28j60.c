#include <stdint.h>
#include "uart.h"
#include "enc28j60.h"
#include "exception.h"
#include "util.h"

uint8_t mac[] = {0x02,0x00,0x00,0x00,0x00,0x01};
uint8_t packetBuffer[1518];
static uint16_t nextPacketPointer;

void write_enc_register(uint8_t reg, uint8_t data){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_WCR|reg);
    spiExchange(0,data);
    setOutput(ENC_CS);
}

uint8_t read_enc_register(uint8_t reg){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_RCR|reg);
    uint8_t data = spiExchange(0,0xff);
    setOutput(ENC_CS);
    return data;
}

uint8_t read_enc_register_macmii(uint8_t reg){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_RCR|reg);
    spiExchange(0,0xff);
    uint8_t data = spiExchange(0,0xff);
    setOutput(ENC_CS);
    return data;
}

void read_enc_buffer(uint16_t address,uint16_t len, uint8_t* data){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_RBM|0x1a);
    while(len>0){
        *data = spiExchange(0,0xff);
        data++;
        len--;
    }
    setOutput(ENC_CS);
}

void bitFieldSet(uint8_t reg, uint8_t bit){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_BFS|reg);
    spiExchange(0,bit);
    setOutput(ENC_CS);
}
void bitFieldClear(uint8_t reg, uint8_t bit){
    resetOutPut(ENC_CS);
    spiExchange(0,SPI_OPCODE_BFC|reg);
    spiExchange(0,bit);
    setOutput(ENC_CS);
}

void setBank(uint8_t bank) {
    uint8_t ori = read_enc_register(ENC_REG_ECON1);
    write_enc_register(ENC_REG_ECON1,(ori&0xfE)| (bank & 7));   
}


void write_enc_phy_register(uint8_t reg, uint16_t data){
    setBank(2);
    write_enc_register(ENC_REG_B2_MIREGADR,reg);
    write_enc_register(ENC_REG_B2_MIWRL,data&0xff);
    write_enc_register(ENC_REG_B2_MIWRH,data>>8);
}

void enableLed(){
    setOutput(0);
    write_enc_phy_register(ENC_PHY_REG_PHLCON,0x0480);
}


void setReceiveBuffer(uint16_t start, uint16_t end){
    setBank(0);
    nextPacketPointer = start;
    write_enc_register(ENC_REG_B0_ERXSTL,start&0xff);
    write_enc_register(ENC_REG_B0_ERXSTH,start>>8);

    write_enc_register(ENC_REG_B0_ERXNDL,end&0xff);
    write_enc_register(ENC_REG_B0_ERXNDH,end>>8);

    write_enc_register(ENC_REG_B0_ERXRDPTL,start&0xff);
    write_enc_register(ENC_REG_B0_ERXRDPTH,start>>8);
}

void configureFilters(){
    setBank(1);
    write_enc_register(ENC_REG_B1_ERXFCON, 0x00);
}

void waitForOST(){
    volatile uint16_t counter = 0xffff;
    while(read_enc_register(ENC_REG_ESTAT)&1 != 1){
        if(counter==0) {
            print("Timeout waiting for clkrdy!\n");
            break;
        }
        counter--;
    }
}

void onPacketReceive(){
    setBank(1);
    uint8_t packetCount = read_enc_register(ENC_REG_B1_EPKTCNT);
    print("Got packets:");
    printNumHex(packetCount);
    uint8_t nextPackLow;
    uint8_t nextPackHigh;
    read_enc_buffer(nextPacketPointer,1,&nextPackLow);
    read_enc_buffer(nextPacketPointer+1,1,&nextPackHigh);
    uint16_t nextPacket = (nextPackHigh<<8)|nextPackLow;
    print("next packet at:");
    printNumHex(nextPacket);
    read_enc_buffer(nextPacketPointer+6,nextPacket-(nextPacketPointer+6),packetBuffer);
    print("byte 0: ");
    printNumHex(packetBuffer[0]);
    print(" ");
    printNumHex(packetBuffer[1]);
    print(" ");
    printNumHex(packetBuffer[2]);
    print(" ");
    printNumHex(packetBuffer[3]);
    print(" ");
    printNumHex(packetBuffer[4]);
    print(" ");
    printNumHex(packetBuffer[5]);
    print(" ");
    printNumHex(packetBuffer[6]);
    print(" ");
    
    
    
    bitFieldSet(ENC_REG_ECON2,BIT_ECON2_PKTDEC);


}

void __attribute__((interrupt)) networkInterrupt(void){
    print("NetworkInterrupt\n");
    uint8_t interruptState = read_enc_register(ENC_REG_EIR);
    if(interruptState&BIT_EIR_PKTIF){
        print("packet received!\n");
        onPacketReceive();
    }
}


void configureMAC(){
    setBank(2);
    write_enc_register(ENC_REG_B2_MACON1,0x0D);
    write_enc_register(ENC_REG_B2_MACON3,0xF0);
    write_enc_register(ENC_REG_B2_MACON4,0x40);
    write_enc_register(ENC_REG_B2_MAMXFLL,1518&0xff);
    write_enc_register(ENC_REG_B2_MAMXFLH,1518>>8);
    write_enc_register(ENC_REG_B2_MABBIPG,0x12);
    write_enc_register(ENC_REG_B2_MAIPGL,0x12);
    write_enc_register(ENC_REG_B2_MAIPGH,0xc);
    write_enc_register(ENC_REG_B2_MACLCON1,0x0f);
    
    setBank(3);
    write_enc_register(ENC_REG_B3_MAADR1,mac[5]);
    write_enc_register(ENC_REG_B3_MAADR2,mac[4]);
    write_enc_register(ENC_REG_B3_MAADR3,mac[3]);
    write_enc_register(ENC_REG_B3_MAADR4,mac[2]);
    write_enc_register(ENC_REG_B3_MAADR5,mac[1]);
    write_enc_register(ENC_REG_B3_MAADR6,mac[0]);
}

void configurePHY(){
    write_enc_phy_register(ENC_PHY_REG_PHCON1,0x0000);
    write_enc_phy_register(ENC_PHY_REG_PHCON2,0x0100);
}

void setupReception(){
    write_enc_register(ENC_REG_EIE,0xc0);
    write_enc_register(ENC_REG_ECON1,0x04);
}
void initialize(){
    installHandler(28,(uint32_t) networkInterrupt);
    setReceiveBuffer(0,0x17ff);
    configureFilters();
    waitForOST();
    configureMAC();
    configurePHY();
    setupReception();
    bitFieldSet(ENC_REG_ECON2,BIT_ECON2_AUTOINC);
}