#
# Copyright (C) 2018-2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#
$(call inherit-product, device/oneplus/sm8150-common/common.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
	$(LOCAL_PATH)/overlay

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/rootdir/etc/fstab.qcom:system/etc/fstab.qcom

# Camera
PRODUCT_PACKAGES += \
	vendor.lineage.camera.motor@1.0 \
	vendor.lineage.camera.motor@1.0-service.oneplus_msmnile
