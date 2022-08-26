/**
 * @file Arduboy2Core.cpp
 * \brief
 * The Arduboy2Core class for Arduboy hardware initilization and control.
 */

#include "Arduboy2Core.h"

const uint8_t PROGMEM lcdBootProgram[] = {
#ifdef SLIMBOY
  // slimboy sets all registers to sane defaults since i2c
  // displays usually havn't a reset input

  // Display Off
  0xAE,

  // Set Display Clock Divisor v = 0xF0
  // default is 0x80
  0xD5, 0xF0,

  // Set Multiplex Ratio v = 0x3F
  0xA8, 0x3F,

  // Set Display Offset v = 0
  0xD3, 0x00,

  // Set Start Line (0)
  0x40,

  // Charge Pump Setting v = enable (0x14)
  // default is disabled
  0x8D, 0x14,

  // Set Segment Re-map (A0) | (b0001)
  // default is (b0000)
  0xA1,

  // Set COM Output Scan Direction
  0xC8,

  // Set COM Pins v
  0xDA, 0x12,

  // Set Contrast v = 0xCF
  0x81, 0xCF,

  // Set Precharge = 0xF1
  0xD9, 0xF1,

  // Set VCom Detect
  0xDB, 0x40,

  // Entire Display ON
  0xA4,

  // Set normal/inverse display
  0xA6,

  // Display On
  0xAF,

  // set display mode = horizontal addressing mode (0x00)
  0x20, 0x00,

  // set col address range
  0x21, 0x00, WIDTH-1,

  // set page address range
  0x22, 0x00, 0x07,
#else
  // boot defaults are commented out but left here in case they
  // might prove useful for reference
  //
  // Further reading: https://www.adafruit.com/datasheets/SSD1306.pdf
  //
  // Display Off
  // 0xAE,

  // Set Display Clock Divisor v = 0xF0
  // default is 0x80
  0xD5, 0xF0,

  // Set Multiplex Ratio v = 0x3F
  // 0xA8, 0x3F,

  // Set Display Offset v = 0
  // 0xD3, 0x00,

  // Set Start Line (0)
  // 0x40,

  // Charge Pump Setting v = enable (0x14)
  // default is disabled
  0x8D, 0x14,

  // Set Segment Re-map (A0) | (b0001)
  // default is (b0000)
  0xA1,

  // Set COM Output Scan Direction
  0xC8,

  // Set COM Pins v
  // 0xDA, 0x12,

  // Set Contrast v = 0xCF
  0x81, 0xCF,

  // Set Precharge = 0xF1
  0xD9, 0xF1,

  // Set VCom Detect
  // 0xDB, 0x40,

  // Entire Display ON
  // 0xA4,

  // Set normal/inverse display
  // 0xA6,

  // Display On
  0xAF,

  // set display mode = horizontal addressing mode (0x00)
  0x20, 0x00,

  // set col address range
  // 0x21, 0x00, WIDTH-1,

  // set page address range
  // 0x22, 0x00, 0x07,
#endif
};


Arduboy2Core::Arduboy2Core() { }

void Arduboy2Core::boot()
{
  bootOLED();
}


#ifdef SLIMBOY
#define I2CADDR 0x3c

void i2c_send_byte(uint8_t data) {
  TWDR = data;
  TWCR = _BV(TWINT)  |  _BV(TWEN);
  while( !(TWCR & _BV(TWINT)));
}

void i2c_start() {
  TWCR = _BV(TWINT) | _BV(TWSTA)  | _BV(TWEN);
  while( !(TWCR & _BV(TWINT)));
  i2c_send_byte(I2CADDR<<1);
}

void i2c_stop(void) {
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
  while( (TWCR & _BV(TWSTO)));
}
#endif

void Arduboy2Core::bootOLED()
{
#ifdef SLIMBOY
  TWSR = 0;
  TWBR = F_CPU/(2*100000)-8;

  i2c_start();
  i2c_send_byte(0x00);
  for (uint8_t i = 0; i < sizeof(lcdBootProgram); i++) 
    i2c_send_byte(pgm_read_byte(lcdBootProgram + i));
  i2c_stop();
  
  //  TWBR = F_CPU/(2*400000)-8;
  TWBR = 1; // 12 = 400kHz
#else
  // reset the display
  delayShort(5); // reset pin should be low here. let it stay low a while
  bitSet(RST_PORT, RST_BIT); // set high to come out of reset
  delayShort(5); // wait a while

  // select the display (permanently, since nothing else is using SPI)
  bitClear(CS_PORT, CS_BIT);

  // run our customized boot-up command sequence against the
  // OLED to initialize it properly for Arduboy
  LCDCommandMode();
  for (uint8_t i = 0; i < sizeof(lcdBootProgram); i++) {
    SPItransfer(pgm_read_byte(lcdBootProgram + i));
  }
  LCDDataMode();
#endif
}

#ifndef SLIMBOY
void Arduboy2Core::LCDDataMode()
{
  bitSet(DC_PORT, DC_BIT);
}

void Arduboy2Core::LCDCommandMode()
{
  bitClear(DC_PORT, DC_BIT);
}
#endif


#ifndef SLIMBOY
// Write to the SPI bus (MOSI pin)
void Arduboy2Core::SPItransfer(uint8_t data)
{
  SPDR = data;
  /*
   * The following NOP introduces a small delay that can prevent the wait
   * loop form iterating when running at the maximum speed. This gives
   * about 10% more speed, even if it seems counter-intuitive. At lower
   * speeds it is unnoticed.
   */
  asm volatile("nop");
  while (!(SPSR & _BV(SPIF))) { } // wait
}
#endif




/* Power Management */

void Arduboy2Core::idle()
{
  SMCR = _BV(SE); // select idle mode and enable sleeping
  sleep_cpu();
  SMCR = 0; // disable sleeping
}

void Arduboy2Core::bootPowerSaving()
{
#ifdef SLIMBOY
  // FIXME
#else
  // disable Two Wire Interface (I2C) and the ADC
  // All other bits will be written with 0 so will be enabled
  PRR0 = _BV(PRTWI) | _BV(PRADC);
  // disable USART1
  PRR1 |= _BV(PRUSART1);
#endif
}

#ifndef SLIMBOY
// Shut down the display
void Arduboy2Core::displayOff()
{
  LCDCommandMode();
  SPItransfer(0xAE); // display off
  SPItransfer(0x8D); // charge pump:
  SPItransfer(0x10); //   disable
  delayShort(250);
  bitClear(RST_PORT, RST_BIT); // set display reset pin low (reset state)
}
#endif

// Restart the display after a displayOff()
void Arduboy2Core::displayOn()
{
  bootOLED();
}

uint8_t Arduboy2Core::width() { return WIDTH; }

uint8_t Arduboy2Core::height() { return HEIGHT; }


/* Drawing */

void Arduboy2Core::paint8Pixels(uint8_t pixels)
{
#ifdef SLIMBOY
  i2c_start();
  i2c_send_byte(0x40);
  i2c_send_byte(pixels);
  i2c_stop();
#else
  SPItransfer(pixels);
#endif
}

void Arduboy2Core::paintScreen(const uint8_t *image)
{
#ifdef SLIMBOY
  // I2C
  for (uint8_t i=0; i<(WIDTH*HEIGHT/(16*8));) {
    // send a bunch of data in one xmission
    i2c_start();
    i2c_send_byte(0x40);
    for(uint8_t x=0;x<16;x++,i++) {
      TWDR = pgm_read_byte(image+i);
      TWCR = _BV(TWINT) |  _BV(TWEN);
      while( !(TWCR & _BV(TWINT)));
    }
    i2c_stop();
  }
#else
  for (int i = 0; i < (HEIGHT*WIDTH)/8; i++)
  {
    SPItransfer(pgm_read_byte(image + i));
  }
#endif
}

// paint from a memory buffer, this should be FAST as it's likely what
// will be used by any buffer based subclass
//
// The following assembly code runs "open loop". It relies on instruction
// execution times to allow time for each byte of data to be clocked out.
// It is specifically tuned for a 16MHz CPU clock and SPI clocking at 8MHz.
void Arduboy2Core::paintScreen(uint8_t image[], bool clear)
{
#ifdef SLIMBOY
  // I2C
  uint16_t i;
  i2c_start();
  TWDR = 0x40;
  TWCR = _BV(TWINT) | _BV(TWEN);
  for (uint16_t i=0; i<(WIDTH*HEIGHT/8);i++) {
    while( !(TWCR & _BV(TWINT)));
    TWDR = image[i];
    TWCR = _BV(TWINT) | _BV(TWEN);
    if(clear) image[i] = 0;
  }
  while( !(TWCR & _BV(TWINT)));
  i2c_stop();
#else
  uint16_t count;

  asm volatile (
    "   ldi   %A[count], %[len_lsb]               \n\t" //for (len = WIDTH * HEIGHT / 8)
    "   ldi   %B[count], %[len_msb]               \n\t"
    "1: ld    __tmp_reg__, %a[ptr]      ;2        \n\t" //tmp = *(image)
    "   out   %[spdr], __tmp_reg__      ;1        \n\t" //SPDR = tmp
    "   cpse  %[clear], __zero_reg__    ;1/2      \n\t" //if (clear) tmp = 0;
    "   mov   __tmp_reg__, __zero_reg__ ;1        \n\t"
    "2: sbiw  %A[count], 1              ;2        \n\t" //len --
    "   sbrc  %A[count], 0              ;1/2      \n\t" //loop twice for cheap delay
    "   rjmp  2b                        ;2        \n\t"
    "   st    %a[ptr]+, __tmp_reg__     ;2        \n\t" //*(image++) = tmp
    "   brne  1b                        ;1/2 :18  \n\t" //len > 0
    "   in    __tmp_reg__, %[spsr]                \n\t" //read SPSR to clear SPIF
    : [ptr]     "+&e" (image),
      [count]   "=&w" (count)
    : [spdr]    "I"   (_SFR_IO_ADDR(SPDR)),
      [spsr]    "I"   (_SFR_IO_ADDR(SPSR)),
      [len_msb] "M"   (WIDTH * (HEIGHT / 8 * 2) >> 8),   // 8: pixels per byte
      [len_lsb] "M"   (WIDTH * (HEIGHT / 8 * 2) & 0xFF), // 2: for delay loop multiplier
      [clear]   "r"   (clear)
  );
#endif
}

void Arduboy2Core::blank()
{
#ifdef SLIMBOY
  for (uint8_t i=0; i<(WIDTH*HEIGHT/(16*8)); i++) {
    i2c_start();
    i2c_send_byte(0x40);
    for(uint8_t x=0;x<16;x++) {
      TWDR = 0;
      TWCR = _BV(TWINT) |  _BV(TWEN);
      while( !(TWCR & _BV(TWINT)));
    }
    i2c_stop();
  }
#else
  for (int i = 0; i < (HEIGHT*WIDTH)/8; i++)
    SPItransfer(0x00);
#endif
}

void Arduboy2Core::sendLCDCommand(uint8_t command)
{
#ifdef SLIMBOY
  i2c_start();
  i2c_send_byte(0x00);
  i2c_send_byte(command);
  i2c_stop();
#else
  LCDCommandMode();
  SPItransfer(command);
  LCDDataMode();
#endif
}

// invert the display or set to normal
// when inverted, a pixel set to 0 will be on
void Arduboy2Core::invert(bool inverse)
{
  sendLCDCommand(inverse ? OLED_PIXELS_INVERTED : OLED_PIXELS_NORMAL);
}

// turn all display pixels on, ignoring buffer contents
// or set to normal buffer display
void Arduboy2Core::allPixelsOn(bool on)
{
  sendLCDCommand(on ? OLED_ALL_PIXELS_ON : OLED_PIXELS_FROM_RAM);
}

// flip the display vertically or set to normal
void Arduboy2Core::flipVertical(bool flipped)
{
  sendLCDCommand(flipped ? OLED_VERTICAL_FLIPPED : OLED_VERTICAL_NORMAL);
}

// flip the display horizontally or set to normal
void Arduboy2Core::flipHorizontal(bool flipped)
{
  sendLCDCommand(flipped ? OLED_HORIZ_FLIPPED : OLED_HORIZ_NORMAL);
}



// delay in ms with 16 bit duration
void Arduboy2Core::delayShort(uint16_t ms)
{
  delay((unsigned long) ms);
}



