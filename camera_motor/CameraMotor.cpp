#define LOG_TAG "vendor.lineage.camera.motor@1.0-service.oneplus_msmnile"

#include "CameraMotor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hidl/HidlTransportSupport.h>
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>

#define CAMERA_MOTOR_ENABLE "/sys/devices/platform/vendor/vendor:motor_pl/enable"
#define CAMERA_MOTOR_DIRECTION "/sys/devices/platform/vendor/vendor:motor_pl/direction"
#define DIRECTION_DOWN "0"
#define DIRECTION_UP "1"
#define ENABLED "1"
#define CAMERA_ID_FRONT 1

using vendor::lineage::camera::motor::V1_0::ICameraMotor;
using vendor::lineage::camera::motor::V1_0::implementation::CameraMotor;
using android::hardware::Return;
using android::hardware::Void;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

void set_direction(const char *direction) {
	FILE *fp = fopen(CAMERA_MOTOR_DIRECTION, "w");
	if (fp != NULL) {
		fputs(direction, fp);
	}
	fclose(fp);
}

void trigger_motor() {
	FILE *fp = fopen(CAMERA_MOTOR_ENABLE, "w");
	if (fp != NULL) {
		fputs(ENABLED, fp);
	}
	fclose(fp);
}

Return<void> CameraMotor::onConnect(int8_t cameraId) {
	if (cameraId != CAMERA_ID_FRONT) return Void();
	LOG(INFO) << "Popping out front camera";
	set_direction(DIRECTION_UP);
	trigger_motor();
	return Void();
}

Return<void> CameraMotor::onDisconnect(int8_t cameraId) {
	if (cameraId != CAMERA_ID_FRONT) return Void();
	LOG(INFO) << "Retracting front camera";
	set_direction(DIRECTION_DOWN);
	trigger_motor();
	return Void();
}

CameraMotor::CameraMotor() {
}

int main() {
	android::sp<ICameraMotor> service = new CameraMotor();
	configureRpcThreadpool(1, true);
	android::status_t status = service->registerAsService();
	if (status != android::OK) {
		LOG(ERROR) << "Cannot register Camera Motor HAL service";
	}
	LOG(INFO) << "Camera Motor HAL ready";
	joinRpcThreadpool();
	LOG(ERROR) << "Camera Motor service failed to join thread pool";
	return 1;
}
