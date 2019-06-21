#include <vendor/lineage/biometrics/fingerprint/inscreen/1.0/IFingerprintInscreen.h>
#include <vendor/oneplus/fingerprint/extension/1.0/IVendorFingerprintExtensions.h>
#include <vendor/oneplus/hardware/display/1.0/IOneplusDisplay.h>

namespace vendor {
namespace lineage {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_0 {
namespace implementation {

using ::android::sp;
using ::android::hardware::Return;
using ::vendor::oneplus::fingerprint::extension::V1_0::IVendorFingerprintExtensions;
using ::vendor::oneplus::hardware::display::V1_0::IOneplusDisplay;

class FingerprintInscreen : public IFingerprintInscreen {
	private:
		sp<IVendorFingerprintExtensions> mVendorFpService;
		sp<IOneplusDisplay> mVendorDisplayService;

	public:
		FingerprintInscreen();
		Return<void> onStartEnroll();
		Return<void> onFinishEnroll();
		Return<void> onPress();
		Return<void> onRelease();
		Return<void> onShowFODView();
		Return<void> onHideFODView();
		Return<bool> shouldHandleError(int32_t error);
		Return<void> setLongPressEnabled(bool enabled);
		Return<int32_t> getDimAmount(int32_t cur_brightness);
		Return<bool> shouldBoostBrightness();

};

}
}
}
}
}
}
}
