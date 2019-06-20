#include <vendor/lineage/camera/motor/1.0/ICameraMotor.h>

namespace vendor {
namespace lineage {
namespace camera {
namespace motor {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Return;

class CameraMotor : public ICameraMotor {
	public:
		CameraMotor();
		Return<void> onConnect(int8_t cameraId) override;
		Return<void> onDisconnect(int8_t cameraVoid) override;
};

}
}
}
}
}
}
