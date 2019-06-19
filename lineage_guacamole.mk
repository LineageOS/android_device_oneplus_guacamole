#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

$(call inherit-product, device/oneplus/guacamole/device.mk)
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := lineage_guacamole
PRODUCT_DEVICE := guacamole
PRODUCT_BRAND := OnePlus
PRODUCT_MODEL := OnePlus 7 Pro
PRODUCT_MANUFACTURER := OnePlus

PRODUCT_AAPT_CONFIG := xxxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxxhdpi
PRODUCT_CHARACTERISTICS := nosdcard

# Boot animation
TARGET_SCREEN_HEIGHT := 3120
TARGET_SCREEN_WIDTH := 1440

# Build info
BUILD_FINGERPRINT := "OnePlus/OnePlus7Pro/OnePlus7Pro:9/PKQ1.190110.001/1906032330:user/release-keys"
PRODUCT_BUILD_PROP_OVERRIDES += \
	TARGET_DEVICE=OnePlus7Pro \
	PRODUCT_NAME=OnePlus7Pro \
	PRIVATE_BUILD_DESC="OnePlus7Pro-user 9 PKQ1.190110.001 1906032330 release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-oneplus
