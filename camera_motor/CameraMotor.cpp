/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "CameraMotorService"

#include "CameraMotor.h"
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <fstream>

#define CAMERA_MOTOR_ENABLE "/sys/devices/platform/vendor/vendor:motor_pl/enable"
#define CAMERA_MOTOR_DIRECTION "/sys/devices/platform/vendor/vendor:motor_pl/direction"
#define DIRECTION_DOWN "0"
#define DIRECTION_UP "1"
#define ENABLED "1"
#define CAMERA_ID_FRONT 1

namespace vendor {
namespace lineage {
namespace camera {
namespace motor {
namespace V1_0 {
namespace implementation {

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

Return<void> CameraMotor::onConnect(int8_t cameraId) {
    if (cameraId == CAMERA_ID_FRONT) {
        LOG(INFO) << "Popping out front camera";

        set(CAMERA_MOTOR_DIRECTION, DIRECTION_UP);
        set(CAMERA_MOTOR_ENABLE, ENABLED);
    }

    return Void();
}

Return<void> CameraMotor::onDisconnect(int8_t cameraId) {
    if (cameraId == CAMERA_ID_FRONT) {
        LOG(INFO) << "Retracting front camera";

        set(CAMERA_MOTOR_DIRECTION, DIRECTION_DOWN);
        set(CAMERA_MOTOR_ENABLE, ENABLED);
    }

    return Void();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace motor
}  // namespace camera
}  // namespace lineage
}  // namespace vendor
