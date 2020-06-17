#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

const int scanTimeSeconds = 1;

std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789abcdef";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

class AdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (strcmp(advertisedDevice.getName().c_str(), "esp32") == 0) {
      Serial.print(advertisedDevice.getName().c_str());
      std::string hexAdvData = string_to_hex(advertisedDevice.getManufacturerData());
      Serial.printf(": %s \n", hexAdvData.c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); // create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(false); // active scan (true) uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(scanTimeSeconds, false);
  pBLEScan->clearResults();
}