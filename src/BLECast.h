// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _BLE_CAST_H_
#define _BLE_CAST_H_

#include "sdkconfig.h"

#if defined(CONFIG_BT_ENABLED) && defined(CONFIG_BLUEDROID_ENABLED)

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_bt.h"

#include "Arduino.h"

class BLECast {
    public:
        BLECast(std::string localName);
        ~BLECast(void);

        bool begin();
        void setManufacturerData(char* payload, uint8_t len);
        void end(void);
    private:
        bool _init_gap();
        bool _stop_gap();
        void setAdvData(std::string data);

        std::string local_name;
        std::string m_payload;
        bool running = false;
};

#endif

#endif
