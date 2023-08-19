// Written By Madhuri Vaghasia edited by njchhasatia to use RP2040 instead of Arduino Mega

#ifndef	_W5300_ANYMCU_H_
#define	_W5300_ANYMCU_H_
#include <Arduino.h>
#include <hardware/gpio.h> // needed to access rp2040 32 bit gpio API

#define DBUS_STRT   14  // 8bit Databus GPIO 22 ... 14
#define ADDR_STRT   7   // 3bit Address (A2 A1 A0) 7->A0, 8->A1, 9->A2
#define CTRL_STRT   10  // 3bit Control (CS WR RD) 10->RD, 11->WR, 12->CS

#define DBUS_MASK   0xFF // 8bits
#define ADDR_MASK   0x07 // 8bits
#define CTRL_MASK   0x07 // 8bits

#define ADDR_0  0x00  //bit seq A2 A1 A0
#define ADDR_1  0x01
#define ADDR_2  0x02
#define ADDR_3  0x03
#define ADDR_4  0x04
#define ADDR_5  0x05
#define ADDR_6  0x06
#define ADDR_7  0x07

#define CTRL_IDLE 0x07  //b111  //bit seq CS WR RD
#define CTRL_RDST 0x06  //b110
#define CTRL_RDEX 0x02  //b010
#define CTRL_WRST 0x05  //b101
#define CTRL_WREX 0x01  //b001
	
uint16_t w5300_read_indirect(uint16_t addr);
void w5300_write_indirect(uint16_t addr, uint16_t data1);
void w5300_setup_indirect_MR(void);
void w5300_init(void);
void w5300_reset(void);

#endif   
