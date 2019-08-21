#
# Copyright (C) 2018-2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#
$(call inherit-product, device/oneplus/sm8150-common/common.mk)

# Vendor properties
-include $(LOCAL_PATH)/vendor_props.mk

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay

# Camera
PRODUCT_PACKAGES += \
    vendor.lineage.camera.motor@1.0 \
    vendor.lineage.camera.motor@1.0-service.guacamole \
    OnePlusCameraHelper

# Device init scripts
PRODUCT_PACKAGES += \
    fstab.qcom \
    init.display.guacamole.rc
