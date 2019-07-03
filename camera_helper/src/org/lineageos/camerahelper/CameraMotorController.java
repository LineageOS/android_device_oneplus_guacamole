/*
 * Copyright (c) 2019 The LineageOS Project
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

package org.lineageos.camerahelper;

import android.text.TextUtils;
import android.util.Log;

public class CameraMotorController {
    private static final String TAG = "CameraMotorController";
    private static final boolean DEBUG = true;

    // Camera motor paths
    private static final String CAMERA_MOTOR_ENABLE_PATH = "/sys/devices/platform/vendor/vendor:motor_pl/enable";
    private static final String CAMERA_MOTOR_DIRECTION_PATH = "/sys/devices/platform/vendor/vendor:motor_pl/direction";

    // Motor control values
    private static final String DIRECTION_DOWN = "0";
    private static final String ENABLED = "1";

    private CameraMotorController() {
        // This class is not supposed to be instantiated
    }

    /**
      * Make sure that the front camera is closed
      */
    public static void ensureCameraClosed() {
        if (DEBUG) Log.d(TAG, "Writing camera direction down");
        // Write the direction
        FileUtils.writeLine(CAMERA_MOTOR_DIRECTION_PATH, DIRECTION_DOWN);
        if (DEBUG) Log.d(TAG, "Writing camera enabled");
        // Run the camera
        FileUtils.writeLine(CAMERA_MOTOR_ENABLE_PATH, ENABLED);
    }
}
