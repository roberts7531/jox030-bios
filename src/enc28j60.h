#ifndef ENC_H
#define ENC_H

#define ENC_CS 0
#define SPI_OPCODE_RCR 0b00000000
#define SPI_OPCODE_RBM 0b00100000
#define SPI_OPCODE_WCR 0b01000000
#define SPI_OPCODE_WBM 0b01100000
#define SPI_OPCODE_BFS 0b10000000
#define SPI_OPCODE_BFC 0b10100000
#define SPI_OPCODE_RST 0b11100000



#define ENC_REG_B0_ERDPTL   0x0
#define ENC_REG_B0_ERDPTH   0x1
#define ENC_REG_B0_EWRPTL   0x2
#define ENC_REG_B0_EWRPTH   0x3
#define ENC_REG_B0_ETXSTL   0x4
#define ENC_REG_B0_ETXSTH   0x5
#define ENC_REG_B0_ETXNDL   0x6
#define ENC_REG_B0_ETXNDH   0x7
#define ENC_REG_B0_ERXSTL   0x8
#define ENC_REG_B0_ERXSTH   0x9
#define ENC_REG_B0_ERXNDL   0xA
#define ENC_REG_B0_ERXNDH   0xB
#define ENC_REG_B0_ERXRDPTL 0xC
#define ENC_REG_B0_ERXRDPTH 0xD
#define ENC_REG_B0_ERXWRPTL 0xE
#define ENC_REG_B0_ERXWRPTH 0xF
#define ENC_REG_B0_EDMASTL  0x10
#define ENC_REG_B0_EDMASTH  0x11
#define ENC_REG_B0_EDMANDL  0x12
#define ENC_REG_B0_EDMANDH  0x13
#define ENC_REG_B0_EDMADSTL 0x14
#define ENC_REG_B0_EDMADSTH 0x15
#define ENC_REG_B0_EDMACSL  0x16
#define ENC_REG_B0_EDMACSH  0x17

// Bank 1 Registers
#define ENC_REG_B1_ETH0     0x0
#define ENC_REG_B1_ETH1     0x1
#define ENC_REG_B1_ETH2     0x2
#define ENC_REG_B1_ETH3     0x3
#define ENC_REG_B1_ETH4     0x4
#define ENC_REG_B1_ETH5     0x5
#define ENC_REG_B1_ETH6     0x6
#define ENC_REG_B1_ETH7     0x7
#define ENC_REG_B1_EPMM0    0x8
#define ENC_REG_B1_EPMM1    0x9
#define ENC_REG_B1_EPMM2    0xA
#define ENC_REG_B1_EPMM3    0xB
#define ENC_REG_B1_EPMM4    0xC
#define ENC_REG_B1_EPMM5    0xD
#define ENC_REG_B1_EPMM6    0xE
#define ENC_REG_B1_EPMM7    0xF
#define ENC_REG_B1_EPMCSL   0x10
#define ENC_REG_B1_EPMCSH   0x11
#define ENC_REG_B1_EPMOL    0x14
#define ENC_REG_B1_EPMOH    0x15
#define ENC_REG_B1_ERXFCON  0x18
#define ENC_REG_B1_EPKTCNT  0x19

// Bank 2 Registers
#define ENC_REG_B2_MACON1   0x0
#define ENC_REG_B2_MACON3   0x2
#define ENC_REG_B2_MACON4   0x3
#define ENC_REG_B2_MABBIPG  0x4
#define ENC_REG_B2_MAIPGL   0x6
#define ENC_REG_B2_MAIPGH   0x7
#define ENC_REG_B2_MACLCON1 0x8
#define ENC_REG_B2_MACLCON2 0x9
#define ENC_REG_B2_MAMXFLL  0xA
#define ENC_REG_B2_MAMXFLH  0xB
#define ENC_REG_B2_MICMD    0x12
#define ENC_REG_B2_MIREGADR 0x14
#define ENC_REG_B2_MIWRL    0x16
#define ENC_REG_B2_MIWRH    0x17
#define ENC_REG_B2_MIRDL    0x18
#define ENC_REG_B2_MIRDH    0x19

// Bank 3 Registers
#define ENC_REG_B3_MAADR5   0x0
#define ENC_REG_B3_MAADR6   0x1
#define ENC_REG_B3_MAADR3   0x2
#define ENC_REG_B3_MAADR4   0x3
#define ENC_REG_B3_MAADR1   0x4
#define ENC_REG_B3_MAADR2   0x5
#define ENC_REG_B3_EBSTSD   0x6
#define ENC_REG_B3_EBSTCON  0x7
#define ENC_REG_B3_EBSTCSL  0x8
#define ENC_REG_B3_EBSTCSH  0x9
#define ENC_REG_B3_MISTAT   0xA
#define ENC_REG_B3_EREVID   0x12
#define ENC_REG_B3_ECOCON   0x15
#define ENC_REG_B3_EFLOCON  0x17
#define ENC_REG_B3_EPAUSL   0x18
#define ENC_REG_B3_EPAUSH   0x19

// Common Registers
#define ENC_REG_EIE         0x1B
#define ENC_REG_EIR         0x1C
#define ENC_REG_ESTAT       0x1D
#define ENC_REG_ECON2       0x1E
#define ENC_REG_ECON1       0x1F


#define ENC_PHY_REG_PHCON1 0
#define ENC_PHY_REG_PHSTAT1 1
#define ENC_PHY_REG_PHID1 2
#define ENC_PHY_REG_PHID2 3
#define ENC_PHY_REG_PHCON2 0x10
#define ENC_PHY_REG_PHSTAT2 0x11
#define ENC_PHY_REG_PHIE 0x12
#define ENC_PHY_REG_PHIR 0x13
#define ENC_PHY_REG_PHLCON 0x14


#define BIT_EIR_PKTIF 0x40
#define BIT_EIR_DMAIF 0x20
#define BIT_EIR_LINKIF 0x10
#define BIT_EIR_TXIF 0x08
#define BIT_EIR_TXERIF 0x02
#define BIT_EIR_RXERIF 0x01


#define BIT_ECON2_AUTOINC 0x80
#define BIT_ECON2_PKTDEC 0x40
#define BIT_ECON2_PWRSV 0x20
#define BIT_ECON2_VRPS 0x08;

void enableLed(void);
void initialize(void);
#endif
