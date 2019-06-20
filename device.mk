#
# Copyright (C) 2018-2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Get non-open-source specific aspects
$(call inherit-product-if-exists, vendor/oneplus/guacamole/guacamole-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
	$(LOCAL_PATH)/overlay \

# AID/fs configs
PRODUCT_PACKAGES += \
	fs_config_files

# Audio
PRODUCT_PACKAGES += \
	audio.a2dp.default \
	tinymix

# Audio Policy
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/audio/audio_policy_configuration.xml:system/etc/audio_policy_configuration.xml

# Camera
PRODUCT_PACKAGES += \
	Snap

# Common init scripts
PRODUCT_PACKAGES += \
	init.qcom.rc

# Display
PRODUCT_PACKAGES += \
	libvulkan \
	vendor.display.config@1.0

# Fingerprint
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.fingerprint.xml:system/etc/permissions/android.hardware.fingerprint.xml
PRODUCT_PACKAGES += \
	android.hardware.biometrics.fingerprint@2.1-service

# HIDL
PRODUCT_PACKAGES += \
	android.hidl.base@1.0 \
	android.hidl.base@1.0_system \
	android.hidl.manager@1.0 \
	android.hidl.manager@1.0_system

# IMS
PRODUCT_PACKAGES += \
	ims-ext-common

# Input
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/keylayout/fpc1020.kl:system/usr/keylayout/fpc1020.kl \
	$(LOCAL_PATH)/keylayout/gf_input.kl:system/usr/keylayout/gf_input.kl \
	$(LOCAL_PATH)/keylayout/gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \

# Lights
PRODUCT_PACKAGES += \
	android.hardware.light@2.0-service.oneplus_msmnile

# Media
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/configs/media_profiles_vendor.xml:system/etc/media_profiles_vendor.xml

# Net
PRODUCT_PACKAGES += \
	netutils-wrapper-1.0

# QTI
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/configs/qti_whitelist.xml:system/etc/sysconfig/qti_whitelist.xml \
	$(LOCAL_PATH)/permissions/privapp-permissions-qti.xml:system/etc/permissions/privapp-permissions-qti.xml

# RCS
PRODUCT_PACKAGES += \
	rcs_service_aidl \
	rcs_service_aidl.xml \
	rcs_service_api \
	rcs_service_api.xml

# Seccomp: TBD

# Telephony
PRODUCT_PACKAGES += \
	telephony-ext

PRODUCT_BOOT_JARS += \
	telephony-ext

# NFC
PRODUCT_PACKAGES += \
	android.hardware.nfc@1.0:64 \
	android.hardware.nfc@1.1:64 \
	android.hardware.secure_element@1.0:64 \
	com.android.nfc_extras \
	Tag \
	vendor.nxp.nxpese@1.0:64 \
	vendor.nxp.nxpnfc@1.0:64

# TextClassifier
PRODUCT_PACKAGES += \
	textclassifier.bundle1

# Trust HAL
PRODUCT_PACKAGES += \
	vendor.lineage.trust@1.0-service

# VNDK-SP
PRODUCT_PACKAGES += \
	vndk_package

# Wifi Display: TBD

AB_OTA_UPDATER := true

AB_OTA_PARTITIONS += \
	boot \
	dtbo \
	system \
	vbmeta \

AB_OTA_POSTINSTALL_CONFIG += \
	RUN_POSTINSTALL_system=true \
	POSTINSTALL_PATH_system=system/bin/otapreopt_script \
	FILESYSTEM_TYPE_system=ext4 \
	POSTINSTALL_OPTIONAL_system=true

PRODUCT_PACKAGES += \
	otapreopt_script \
	brillo_update_payload \
	update_engine \
	update_engine_sideload \
	update_verifier

# Boot control
PRODUCT_STATIC_BOOT_CONTROL_HAL := \
	bootctrl.msmnile \
	libcutils \
	libgptutils \
	libz \

# Sensors
PRODUCT_PACKAGES += \
	android.hardware.sensors@1.0-impl \
	android.hardware.sensors@1.0-service \
	libsensorndkbridge
