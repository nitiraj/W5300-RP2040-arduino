#include "w5300_anymcu.h"
#include <Arduino.h>
	// Initlize W5300 in use 8 bit Indirect addressing mode
	void w5300_init(void)
	{
	  // W5300 CONTROL PIN INIT
	  CTRL_DIR |= (1<<CS)+(1<<WR)+(1<<RD)+(1<<ADR2)+(1<<ADR1)+(1<<ADR0); 
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD);
	  // W5300 DATA PIN INIT
	  DATA_DIR = 0x00;
	  DATA_OUT = 0x00;   
	  delay(2000);
	  
	  Serial.println("\r\n--> Modified W5300 Arduino ethernet library for any mcu with Indirect Addressing  (need 14 GPIO Only) \r\n--> Developed by - M.Vaghasia (rcele_85@yahoo.com) \r\n--> Current MCU Selected - Arduino Mega");
      Serial.println("--> Soft Reset W5300");
      w5300_reset();
      delay(1000);
	  // configure W5300 to work in indirect addressing mode
	  w5300_setup_indirect_MR();
	  //Serial.println(w5300_read_indirect(0),HEX);
	  delay(1000);
      if(w5300_read_indirect(0) == 0x3801)	  Serial.println("--> w5300 indirect addressing Init - Success ;)");
      else 
	  {
		  while(1)
		  {
			Serial.println("--> w5300 indirect addressing Init - Fail :(\r\n--> Check w5300 hardware connections and reset mcu");
			delay(5000);
		  }
	  }
	  delay(1000);
	}

	// Setup W5300 to use 8 bit Indirect addressing mode
	void w5300_setup_indirect_MR(void)
	{
	  DATA_DIR = 0xFF; // Make data port Output
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR1;
	  DATA_OUT = 0x01;
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2);
	}

	// Read 16 Bit register of W5300 using 8 bit indirect addressing
	uint16_t w5300_read_indirect(uint16_t addr)
	{
	  uint16_t dataL =0;
	  uint16_t dataH =0;
	  DATA_DIR = 0xFF; // Make data port Output
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR2;
	  DATA_OUT = (addr>>8) & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2);
	  
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR3;
	  DATA_OUT = addr & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2); 
	  
	  DATA_DIR = 0x00; // Make data port input
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR4;
	  CTRL_OUT &= ~((1<<CS)+(1<<RD));
	  delayMicroseconds(2);
	  dataL = DATA_IN;
	  CTRL_OUT |= (1<<RD)+(1<<CS); 
	  delayMicroseconds(2); 
	  
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR5;
	  CTRL_OUT &= ~((1<<CS)+(1<<RD));
	  delayMicroseconds(2);
	  dataH = (dataL<<8)+DATA_IN;
	  CTRL_OUT |= (1<<RD)+(1<<CS); 
	  delayMicroseconds(2);
	  return dataH;
	}
	
	// Write 16 Bit register of W5300 using 8 bit indirect addressing
	void w5300_write_indirect(uint16_t addr, uint16_t data1)
	{
	  uint16_t data = data1;
	  DATA_DIR = 0xFF; // Make data port Output
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR2;
	  DATA_OUT = (addr>>8) & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2);
	  
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR3;
	  DATA_OUT = addr & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2); 

	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR4;
	  DATA_OUT = (data1>>8) & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2);
	  
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR5;
	  DATA_OUT = data1 & 0xFF;
	  delayMicroseconds(2);
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2); 
	}
	
	// Soft Reset W5300
	void w5300_reset(void)
	{
	  DATA_DIR = 0xFF; // Make data port Output
	  CTRL_OUT = (1<<CS)+(1<<WR)+(1<<RD) + AR1;
	  DATA_OUT = 0x80;
	  CTRL_OUT &= ~((1<<CS)+(1<<WR));
	  delayMicroseconds(2);
	  CTRL_OUT |= (1<<CS)+(1<<WR);  
	  delayMicroseconds(2);
	}


