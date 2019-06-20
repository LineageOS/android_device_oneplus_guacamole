#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAMERA_MOTOR_ENABLE "/sys/devices/platform/vendor/vendor:motor_pl/enable"
#define CAMERA_MOTOR_DIRECTION "/sys/devices/platform/vendor/vendor:motor_pl/direction"
#define DIRECTION_DOWN "1"
#define DIRECTION_UP "0"
#define ENABLED "1"
#define CAMERA_ID_FRONT 1

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

void connect(int cameraId) {
	if (cameraId != CAMERA_ID_FRONT) return;
	set_direction(DIRECTION_UP);
	trigger_motor();
}

void disconnect(int cameraId) {
	if (cameraId != CAMERA_ID_FRONT) return;
	set_direction(DIRECTION_DOWN);
	trigger_motor();
}

int main(int argc, const char *argv[]) {
	if (strcmp(argv[1], "connect")) {
		connect(atoi(argv[2]));
	} else {
		disconnect(atoi(argv[2]));
	}
}
