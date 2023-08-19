// Written By Madhuri Vaghasia edited by njchhasatia to use RP2040 instead of Arduino Mega
#include "w5300_anymcu.h"
#include <Arduino.h>
// Initlize W5300 in use 8 bit Indirect addressing mode
void w5300_init(void)
{
	// init all w5300 connection pins as output
	gpio_init_mask((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT)); 
	gpio_set_dir_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT)); 
	delay(2000);
	Serial.println("\r\n--> Modified W5300 Arduino ethernet library for any mcu with Indirect Addressing  (need 14 GPIO Only) \r\n--> Developed by - M.Vaghasia (rcele_85@yahoo.com) edited ny njchhasatia \r\n--> Current MCU Selected - Raspberry Pi Pico");
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

// Soft Reset W5300
void w5300_reset(void)
{
	gpio_init_mask(DBUS_MASK<<DBUS_STRT); // Set Databus as output
	gpio_set_dir_masked(DBUS_MASK<<DBUS_STRT,DBUS_MASK<<DBUS_STRT);

	// Write 0x80 to MR_LOW (Addr - 0x01) for soft reset w5300
	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (0x80<<DBUS_STRT) | (ADDR_1<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);
}

// Setup W5300 to use 8 bit Indirect addressing mode	  
void w5300_setup_indirect_MR(void)
{
	gpio_init_mask(DBUS_MASK<<DBUS_STRT); // Set Databus as output
	gpio_set_dir_masked(DBUS_MASK<<DBUS_STRT,DBUS_MASK<<DBUS_STRT);

	// Write 0x01 to MR_LOW (Addr - 0x01) for configure w5300 indirect addressing
	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (0x01<<DBUS_STRT) | (ADDR_1<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);
}

// Write 16 Bit register of W5300 using 8 bit indirect addressing
void w5300_write_indirect(uint16_t addr, uint16_t data1)
{
	uint16_t data = data1;
	gpio_init_mask(DBUS_MASK<<DBUS_STRT); // Set Databus as output
	gpio_set_dir_masked(DBUS_MASK<<DBUS_STRT,DBUS_MASK<<DBUS_STRT);
	  
	// set desired addr in indirect address reg 0x02, 0x03 address
	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (((addr>>8) & 0xFF)<<DBUS_STRT) | (ADDR_2<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), ((addr & 0xFF)<<DBUS_STRT) | (ADDR_3<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	// set desired data in indirect data reg 0x04, 0x05 address
	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (((data1>>8) & 0xFF)<<DBUS_STRT) | (ADDR_4<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), ((data1 & 0xFF)<<DBUS_STRT) | (ADDR_5<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);
}

// Read 16 Bit register of W5300 using 8 bit indirect addressing
uint16_t w5300_read_indirect(uint16_t addr)
{
	uint16_t data =0;
	uint32_t data1 = 0;
	uint32_t data2 = 0;
	gpio_init_mask(DBUS_MASK<<DBUS_STRT); // Set Databus as output
	gpio_set_dir_masked(DBUS_MASK<<DBUS_STRT, DBUS_MASK<<DBUS_STRT);
	  
	// set desired addr in indirect address reg 0x02, 0x03 address
	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (((addr>>8) & 0xFF)<<DBUS_STRT) | (ADDR_2<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	gpio_put_masked((DBUS_MASK<<DBUS_STRT) | (ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), ((addr & 0xFF)<<DBUS_STRT) | (ADDR_3<<ADDR_STRT) | (CTRL_WRST<<CTRL_STRT)); 
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_WREX<<CTRL_STRT);
	delayMicroseconds(1);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	gpio_init_mask(DBUS_MASK<<DBUS_STRT); // Set Data Bus input
	gpio_set_dir_masked(DBUS_MASK<<DBUS_STRT,0);
	  
	// read data from indirect data register
	gpio_put_masked((ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (ADDR_4<<ADDR_STRT) | (CTRL_RDEX<<CTRL_STRT)); 
	delayMicroseconds(2);
	data1 = (gpio_get_all()>>DBUS_STRT)&0xFF;
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);

	gpio_put_masked((ADDR_MASK<<ADDR_STRT) | (CTRL_MASK<<CTRL_STRT), (ADDR_5<<ADDR_STRT) | (CTRL_RDEX<<CTRL_STRT)); 
	delayMicroseconds(2);
	data2 = (gpio_get_all()>>DBUS_STRT)&0xFF;
	data = (uint16_t)((data1<<8)|data2);
	gpio_put_masked(CTRL_MASK<<CTRL_STRT, CTRL_IDLE<<CTRL_STRT);
	delayMicroseconds(1);
	return data;
}


