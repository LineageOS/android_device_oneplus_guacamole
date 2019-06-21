#define LOG_TAG "vendor.lineage.biometrics.fingerprint.inscreen@1.0-service.oneplus_msmnile"

#include "FingerprintInscreen.h"
#include <hidl/HidlTransportSupport.h>
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <fstream>
#include <unistd.h>

#define OP_ENABLE_FP_LONGPRESS 3
#define OP_DISABLE_FP_LONGPRESS 4
#define OP_RESUME_FP_ENROLL 8
#define OP_FINISH_FP_ENROLL 10

#define OP_DISPLAY_AOD_MODE 8
#define OP_DISPLAY_NOTIFY_PRESS 9
#define OP_DISPLAY_SET_DIM 10

// This is not a typo by me. It's by oneplus.
#define HBM_ENABLE_PATH "/sys/class/drm/card0-DSI-1/op_friginer_print_hbm"
#define DIM_AMOUNT_PATH "/sys/class/drm/card0-DSI-1/dim_alpha"

using vendor::oneplus::fingerprint::extension::V1_0::IVendorFingerprintExtensions;
using vendor::oneplus::hardware::display::V1_0::IOneplusDisplay;
using vendor::lineage::biometrics::fingerprint::inscreen::V1_0::IFingerprintInscreen;
using vendor::lineage::biometrics::fingerprint::inscreen::V1_0::implementation::FingerprintInscreen;
using android::hardware::Return;
using android::hardware::Void;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

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

int main() {
	android::sp<IFingerprintInscreen> service = new FingerprintInscreen();
	configureRpcThreadpool(1, true);
	android::status_t status = service->registerAsService();
	if (status != android::OK) {
		LOG(ERROR) << "Cannot register FOD HAL";
	}
	LOG(INFO) << "FOD HAL ready";
	joinRpcThreadpool();
	LOG(ERROR) << "FOD HAL exitted unexpectedly";
	return 1;
}

FingerprintInscreen::FingerprintInscreen() {
	this->mVendorFpService = IVendorFingerprintExtensions::getService();
	this->mVendorDisplayService = IOneplusDisplay::getService();
}

Return<void> FingerprintInscreen::onStartEnroll() {
	LOG(INFO) << "onStartEnroll";
	this->mVendorFpService->updateStatus(OP_DISABLE_FP_LONGPRESS);
	this->mVendorFpService->updateStatus(OP_RESUME_FP_ENROLL);
	return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
	LOG(INFO) << "onFinishEnroll";
	this->mVendorFpService->updateStatus(OP_FINISH_FP_ENROLL);
	return Void();
}

Return<void> FingerprintInscreen::onPress() {
	LOG(INFO) << "onPress";
	this->mVendorDisplayService->setMode(OP_DISPLAY_AOD_MODE, 2);
	this->mVendorDisplayService->setMode(OP_DISPLAY_SET_DIM, 1);
	set(HBM_ENABLE_PATH, 1);
	this->mVendorDisplayService->setMode(OP_DISPLAY_NOTIFY_PRESS, 1);
	return Void();
}

Return<void> FingerprintInscreen::onRelease() {
	LOG(INFO) << "onRelease";
	this->mVendorDisplayService->setMode(OP_DISPLAY_AOD_MODE, 0);
	this->mVendorDisplayService->setMode(OP_DISPLAY_SET_DIM, 0);
	set(HBM_ENABLE_PATH, 0);
	this->mVendorDisplayService->setMode(OP_DISPLAY_NOTIFY_PRESS, 0);
	return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
	LOG(INFO) << "onShowFODView";
	return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
	LOG(INFO) << "onHideFODView";
	this->mVendorDisplayService->setMode(OP_DISPLAY_AOD_MODE, 0);
	this->mVendorDisplayService->setMode(OP_DISPLAY_SET_DIM, 0);
	set(HBM_ENABLE_PATH, 0);
	this->mVendorDisplayService->setMode(OP_DISPLAY_NOTIFY_PRESS, 0);
	return Void();
}

Return<bool> FingerprintInscreen::shouldHandleError(int32_t error) {
	if (error == 8) return false;
	return true;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool enabled) {
	this->mVendorFpService->updateStatus(enabled ? OP_ENABLE_FP_LONGPRESS : OP_DISABLE_FP_LONGPRESS);
	return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t cur_brightness) {
	UNUSED(cur_brightness);
	LOG(INFO) << "getDimAmount";
	int dim_amount = get(DIM_AMOUNT_PATH, 0);
	LOG(INFO) << "dimAmount = " << dim_amount;
	return dim_amount;
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
	return false;
}
