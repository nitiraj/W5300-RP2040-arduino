// Written By Madhuri Vaghasia 
#ifndef	_W5300_ANYMCU_H_
#define	_W5300_ANYMCU_H_
#include <Arduino.h>
#include <avr/io.h>
// Assign W5300 DATA Lines to 8 bit port (PORTK used here)
#define DATA_OUT  PORTK
#define DATA_DIR  DDRK
#define DATA_IN   PINK
// Assign W5300 COntrol lines in any sequence to 6 pins of any port (PORTF used here)
#define CTRL_OUT  PORTF
#define CTRL_DIR  DDRF
#define CTRL_IN   PINF
// control pin numbers
#define ADR0 7
#define ADR1 6
#define ADR2 5

#define RD  2
#define WR  3
#define CS  4 

#define AR0  (0<<ADR2)+(0<<ADR1)+(0<<ADR0)
#define AR1  (0<<ADR2)+(0<<ADR1)+(1<<ADR0)
#define AR2  (0<<ADR2)+(1<<ADR1)+(0<<ADR0)
#define AR3  (0<<ADR2)+(1<<ADR1)+(1<<ADR0)
#define AR4  (1<<ADR2)+(0<<ADR1)+(0<<ADR0)
#define AR5  (1<<ADR2)+(0<<ADR1)+(1<<ADR0)

uint16_t w5300_read_indirect(uint16_t addr);
void w5300_write_indirect(uint16_t addr, uint16_t data1);
void w5300_setup_indirect_MR(void);
void w5300_init(void);
void w5300_reset(void);

#endif   
