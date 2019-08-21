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

package org.lineageos.camerahelper;

import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.KeyEvent;
import android.view.WindowManager;

import com.android.internal.os.DeviceKeyHandler;

public class KeyHandler implements DeviceKeyHandler {
    private static final String TAG = KeyHandler.class.getSimpleName();

    // Camera motor event key codes
    private static final int MOTOR_EVENT_MANUAL_TO_DOWN = 184;
    private static final int MOTOR_EVENT_UP = 185;
    private static final int MOTOR_EVENT_UP_ABNORMAL = 186;
    private static final int MOTOR_EVENT_UP_NORMAL = 187;
    private static final int MOTOR_EVENT_DOWN = 188;
    private static final int MOTOR_EVENT_DOWN_ABNORMAL = 189;
    private static final int MOTOR_EVENT_DOWN_NORMAL = 190;

    private final Context mContext;

    public KeyHandler(Context context) {
        mContext = context;
    }

    public KeyEvent handleKeyEvent(KeyEvent event) {
        int scanCode = event.getScanCode();

        switch (scanCode) {
            case MOTOR_EVENT_MANUAL_TO_DOWN:
                if (event.getAction() == KeyEvent.ACTION_DOWN) {
                    showCameraMotorPressWarning();
                }
                break;
            case MOTOR_EVENT_UP_ABNORMAL:
                if (event.getAction() == KeyEvent.ACTION_DOWN) {
                    showCameraMotorCannotGoUpWarning();
                }
                break;
            case MOTOR_EVENT_DOWN_ABNORMAL:
                if (event.getAction() == KeyEvent.ACTION_DOWN) {
                    showCameraMotorCannotGoDownWarning();
                }
                break;
            default:
                return event;
        }

        return null;
    }

    private Context getPackageContext() {
        try {
            return mContext.createPackageContext("org.lineageos.camerahelper", 0);
        } catch (NameNotFoundException | SecurityException e) {
            Log.e(TAG, "Failed to create package context", e);
        }
        return null;
    }

    private void showCameraMotorCannotGoDownWarning() {
        // Show the alert
        new Handler(Looper.getMainLooper()).post(() -> {
            Context packageContext = getPackageContext();
            if (packageContext != null) {
                AlertDialog alertDialog = new AlertDialog.Builder(packageContext)
                        .setTitle(R.string.warning)
                        .setMessage(R.string.motor_cannot_go_down_message)
                        .setPositiveButton(R.string.retry, (dialog, which) -> {
                            // Close the camera
                            CameraMotorController.setMotorDirection(
                                    CameraMotorController.DIRECTION_DOWN);
                            CameraMotorController.setMotorEnabled();
                        })
                        .create();
                alertDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
                alertDialog.setCanceledOnTouchOutside(false);
                alertDialog.show();
            }
        });
    }

    private void showCameraMotorCannotGoUpWarning() {
        // Show the alert
        new Handler(Looper.getMainLooper()).post(() -> {
            Context packageContext = getPackageContext();
            if (packageContext != null) {
                AlertDialog alertDialog = new AlertDialog.Builder(packageContext)
                        .setTitle(R.string.warning)
                        .setMessage(R.string.motor_cannot_go_up_message)
                        .setNegativeButton(R.string.retry, (dialog, which) -> {
                            // Reopen the camera
                            CameraMotorController.setMotorDirection(
                                    CameraMotorController.DIRECTION_UP);
                            CameraMotorController.setMotorEnabled();
                        })
                        .setPositiveButton(R.string.close, (dialog, which) -> {
                            // Close the camera
                            CameraMotorController.setMotorDirection(
                                    CameraMotorController.DIRECTION_DOWN);
                            CameraMotorController.setMotorEnabled();

                            // Go back to home screen
                            Intent intent = new Intent(Intent.ACTION_MAIN);
                            intent.addCategory(Intent.CATEGORY_HOME);
                            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                            mContext.startActivity(intent);
                        })
                        .create();
                alertDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
                alertDialog.setCanceledOnTouchOutside(false);
                alertDialog.show();
            }
        });
    }

    private void showCameraMotorPressWarning() {
        // Go back to home to close all camera apps first
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        mContext.startActivity(intent);

        // Show the alert
        new Handler(Looper.getMainLooper()).post(() -> {
            Context packageContext = getPackageContext();
            if (packageContext != null) {
                AlertDialog alertDialog = new AlertDialog.Builder(packageContext)
                        .setTitle(R.string.warning)
                        .setMessage(R.string.motor_press_message)
                        .setPositiveButton(android.R.string.ok, null)
                        .create();
                alertDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
                alertDialog.setCanceledOnTouchOutside(false);
                alertDialog.show();
            }
        });
    }
}
