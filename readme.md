Modified W5300 ethernet library to use with Arduino Mega 2560 (Can be used with other AVR based arduino boards by editing pin assignment)<br><br>
Project Documentation available at :<br>
https://maker.wiznet.io/mvpatel/contest/w5300-custom-library-for-any-arduino-board-and-application/<br>
<br>
Usage :<br>
Replace ethernet library of your arduino installation directory with supplied ethernet library to use it with W5300 TOE Shield and Arduino Mega<br>
to use NTP time server need <a href="https://github.com/PaulStoffregen/Time">timelib</a> and for MQTT need <a href="https://github.com/knolleary/pubsubclient">pubsubclient</a> library.
<br>
Modification Guide :<br>
edit w5300_anymcu.h with pin assignment of desired MCU<br>
edit w5300_anymcu.cpp with w5300 io driver logic by keeping function name, return type and argument as it is for following functions,<br>
<br>
uint16_t w5300_read_indirect(uint16_t addr);<br>
void w5300_write_indirect(uint16_t addr, uint16_t data1);<br>
void w5300_setup_indirect_MR(void);<br>
void w5300_init(void);<br>
void w5300_reset(void);<br>
<br>
As this functions are used in remaining sourcefiles of Arduino Ethernet library of W5300<br>
<br>
visit https://maker.wiznet.io/mvpatel/contest/w5300-custom-library-for-any-arduino-board-and-application/ project documentation page for more details..<br>
