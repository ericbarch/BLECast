#include <BLECast.h>

// define BTLE name
// CAREFUL: each character eats into your usable adv packet length
BLECast bleCast("esp32");

// the data we will advertise
// remember that structs may be extended/packed to match byte boundaries
struct AdvData {
  uint16_t counter;
} advdat;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Beacon");

  advdat.counter = 0;

  bleCast.begin();
}

void loop() {
  // note -- if you have too much data, it will not be added to the adv payload
  bleCast.setManufacturerData((char*)&advdat, sizeof(advdat));

  advdat.counter++;

  delay(1000);
}
