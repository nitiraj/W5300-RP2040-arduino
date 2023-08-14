Project Documentation available at :<br>
https://maker.wiznet.io/mvpatel/contest/w5300-custom-library-for-any-arduino-board-and-application/<br>
<br>
Usage :<br>
Replace ethernet library of your arduino installation directory with supplied ethernet library to use it with W5300 TOE Shield and Arduino Mega

Modification Guide :
edit w5300_anymcu.h with pin assignment of desired MCU
edit w5300_anymcu.cpp with w5300 io driver logic by keeping function name, return type and argument as it is for following functions,
uint16_t w5300_read_indirect(uint16_t addr);
void w5300_write_indirect(uint16_t addr, uint16_t data1);
void w5300_setup_indirect_MR(void);
void w5300_init(void);
void w5300_reset(void);

As this functions are used in remaining sourcefiles of Arduino Ethernet library of W5300

visit https://maker.wiznet.io/mvpatel/contest/w5300-custom-library-for-any-arduino-board-and-application/ project documentation page for more details..
