# Soldering-station-atmega328p-
hakko 9 series &amp; Hot Air Soldering Station based on atmega328p

i'll make a solid 5 in 1, free open source, easy to repair controller at 1 case, so the 2 controller was done Hakko 9series & 858 Hotair, still need some cash and time to finish the 3 controller, if one of them fail / not stable i'll take a change to buy a chinese version.
the project must be independent mcu not just single mcu so if one fail, the other one still usable, also i'll make a front panel to control all of them just by one Encoder , 5 selector , 5 on/off button. maybe an extra button for any application.


This Project is Upgrade Version from Original by alexander & MakerBR
https://www.hackster.io/makerbr555/diy-smd-rework-station-28b6f5
https://create.arduino.cc/projecthub/sfrwmaker/soldering-iron-controller-for-hakko-907-v-2-fc75d7

previous attempt:
* trying a bare project on printed pcb,runs ok but need some improvement.
* using 24v toroidal transformer, not stable sometimes the mcu get stuck.
* try hookup oled display sh1106 using u8x8 for minimum using memory space.
* mistake when using 8mhz 3.3v promini causing a really slow respond.
* change the toroidal to smps , very recommended.

ChangeLog : Firmware 9series v.2.1 Hotair v.1.5 (Board Version 4.1) 2021.
* change component to SMD as possible
* SH1106 Oled 1.3" Used For Display
* Removing class PIDscreen for Hot Air to free some memory
* Protection on Board
* thermocouple / Thermoresistor Select on board
* Fan 24/12volt select on board
* Custom Front Panel for operated just only 1 encoder, I/O via IDC Socket

on progress at 2022...
* add one controller for 200w Hot Plate Reflow based on hotair station. 
* add one controller for c115 nano solder based on https://github.com/Winkelkatze/jbc_nano_solder
* bridging the chinese GVM c210 controller to the front panel.
* put all board in 1U amp/server case.

first test.
https://www.youtube.com/watch?v=hSPyxu3pc1E
