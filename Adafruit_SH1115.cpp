#include "Adafruit_SH110X.h"
#include <Arduino.h>

static const uint8_t PROGMEM sh1115_init[] = {
  0xAE,       // Display OFF
  0xD5, 0x80, // Set display clock divide
  0xA8, 0x3F, // Multiplex 1/64
  0xD3, 0x00, // Display offset
  0x40,       // Start line = 0
  0xAD, 0x8B, // DC-DC charge pump ON  (CRITICAL for CH1115)
  0xA1,       // Segment remap
  0xC8,       // COM scan direction
  0xDA, 0x12, // COM pins
  0x81, 0x80, // Contrast
  0xD9, 0x22, // Pre-charge
  0xDB, 0x35, // VCOMH
  0xA4,       // Resume RAM
  0xA6,       // Normal display
  0xAF        // Display ON
};

Adafruit_SH1115::Adafruit_SH1115(uint16_t w, uint16_t h, TwoWire *twi,
                                 int8_t rst_pin, uint32_t clkDuring,
                                 uint32_t clkAfter)
    : Adafruit_SH110X(w, h, twi, rst_pin, clkDuring, clkAfter) {

  // CH1115 is TRUE 128 columns, no hidden offset
  _colstart = 0;
}

bool Adafruit_SH1115::begin(uint8_t i2caddr, bool reset) {
  if (!Adafruit_SH110X::begin(i2caddr, reset))
    return false;

  delay(100); // Datasheet power-on delay

  displayOff();
  sendCommandList(sh1115_init, sizeof(sh1115_init));
  clearDisplay();
  display();

  return true;
}
