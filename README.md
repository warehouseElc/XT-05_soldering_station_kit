# XT-05 Soldering station kit
5 in 1 Soldering Station "not unisolder"

This project come for DIYers to make a good and reliable soldering station kit.
all firmware not originaly made by me, but it's a lot of effort to moded and bugfixes.
if you want to copy or modified any of this resource, please let me know the result of your work.
this controller is still upgradable, but i dont have enough time to made this full of feature.

<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/unit_working.jpg" width="480" title="hover text">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/unit_off.jpg" width="480" alt="accessibility text">
</p> 

# Main Unit :
  * This unit controlled by atmega328p mount at FrontPanel board, it use I/O to select which controller you wanna uses and activated independent optocoupler for each controller and each signal.
  * ACC remote to turn on acc like fume extractor or etc by push a software latch button.
  * it's also come with one encoder and 2 button to operate the controller.
  * the CTRL switch operated directly to main controller power.
  * when push up & down button at the same time it will lock the I/O.
  * after 2 hour at Lock mode the unit goes to stby mode by switch off the relay main 5v & 12v , as indicator STBY turn green.
  * baypass mode working just for Hotair station.
  * an ESD plug was separated by main groung / AC earth socket.
    
<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/complete_assy.jpg" width="720" title="hover text">
</p> 

<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/display_assy.jpg" width="480" title="hover text">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/main_button_assy.jpg" width="480" alt="accessibility text">
</p> 


# This controller contains :

1. Nano solder NT-115.
   this controller use stm32f030f4 work at max 18v supply but the tip it self consume just 15w at 9v.
   i used 12v supply for this and calibrated it for chinese tip. if you want to use jbc original or diffrent vendor you just need re-calibrated it.
     
     Feature : 
     
       * can be use with any c-115 handle or tips.
       * sleep seat.
       * stable & fast respond time.
       * small PCB dimension.
       * less component
       * voltage supply, 3v3 & temp measurment.
       * calibrated menu.
       * error hi/lo-Temp, hi/lo-volt detection.
       
     Known Bug :
       
       * No buzzer/bepper
       * input supply must stable & avoid get voltage spike.
       * using medium-high cost & almost at rare status by now of component.
       * "dont cut" any 3v3 input since it use low-side mosfet it will directly supply 12v to the tip if 3v3 not coming.
       * need some protection if 12v on standby but 3v3 not coming.
       * encoder issue with some incompatible devices.
       * open 3v coming from the seat need more attention. "dont swap with Microsolder seat" 
       
2. Micro solder T-210.
   This controller still use Chinese GVM stc32. in future we can adapt NT-115 controller work for c-210 tip, but !!!
   i need more time to fix a bug and test it.
       
      Feature :
       
        * do i need to explain it ? i dont thing so.
        
   
3. iron solder hakko 9series.
    This controller use atmega328p (promini), and run at DC 24v very smoothly.
      
      Feature :
      
        * Tune & Calibrated Menu
        * error screen.
        * easy to use and interactive display.
        * isolated to main power.
        
      Known Bug :
      
        * hard to calibrate cause by slow reading.
        * auto sleep sometimes not working.
        * noisy at heater when start up.
        * no preset temp.
        
4. Hotair 858D.
    This controller use atmega328p (promini), with 700w 220v heater element.
      
      Feature :
      
        * Tune & Calibrated Menu
        * error screen.
        * easy to use and interactive display.
        * add bypass mode to active cool air.
        * isolated to main power
        
      Known Bug :
      
        * hard to calibrate cause by slow reading.
        * seat sleep is lag by 3second.
        * sometimes display get stuck.
        * no preset temp.
        
5. Pre-heater.
   This controller use atmega328p (promini), with 200w/400w 220v heater element.
   (based on Hotair station firmware).
   
      Feature :
      
        * Tune & Calibrated Menu
        * error screen.
        * easy to use and interactive display.
        * isolated to main power

      Known Bug :
      
        * hard to calibrate cause by slow reading.
        * very slow respond.
        * no preset temp.

# Technical Image.
<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/button_and_display.jpg" width="720" title="hover text">
</p> 
<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/PCB Block.jpg" width="720" title="hover text">
</p> 
<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_sttation_kit/Case .jpg" width="720" title="hover text">
</p> 
<p align="center">
  <img src="https://github.com/warehouseElc/Soldering-station-atmega328p-/blob/main/Documentation/XT-05_soldering_station_kit/Relay board.jpg" width="720" title="hover text">
</p> 

# Progress on 2023 :
  * get some data by measure at maximum load
  * testing c210 on nano controller.
  * hardware & software bug fixes.
  * make some improvement.
  * added more protection.


# ChangeLog : 

  (2022)
  Firmware 9series v.2.1 Hotair v.1.5 PreHeater v.1.0 (Board v4.0) Nanosolder v.1.2 (Board v.1.1) F.panel v.1.2.1 (Board v.1.4.0) 
  
    * Put all controller in a 1u case.
    * add two extra button as simulated encoder output @10ms using FP_MCU.
    * using 2 PSU, 24v for iron,hotair,Preheater, 12v for nano & micro.
    * output can be use with extention box or just plug to main unit.
    * modified some powerline for controlling using FP_MCU.
        * 2 Relay add to main 220v control directly with power button
        * add relay module for ACC remote.
        * 2 Relay add for 5vreg & 12v main.
   
  (2021)
  Firmware 9series v.2.1 Hotair v.1.5 (Board Version 4.0) 
  
    * change component to SMD as possible
    * SH1106 Oled 1.3" Used For Display
    * Removing class PIDscreen for Hot Air to free some memory
    * Protection on Board
    * thermocouple / Thermoresistor Select on board
    * Fan 24/12volt select on board
    * Custom Front Panel for operated just only 1 encoder, I/O via IDC Socket

# Resource :
  This Project is Upgrade Version from Original.
   * Iron : https://create.arduino.cc/projecthub/sfrwmaker/soldering-iron-controller-for-hakko-907-v-2-fc75d7
   * Nano : https://github.com/Winkelkatze/jbc_nano_solder
   * Hotair & Preheater : https://www.hackster.io/makerbr555/diy-smd-rework-station-28b6f5

# first test of Board v3.0
https://www.youtube.com/watch?v=hSPyxu3pc1E

# first test of Board v4.0
https://youtu.be/PgkWCMdGw-8

# first test of full build (New Firmware)
coming soon...
