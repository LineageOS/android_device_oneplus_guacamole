#!/usr/bin/env -S PYTHONPATH=../../../tools/extract-utils python3
#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

from extract_utils.main import (
    ExtractUtils,
    ExtractUtilsModule,
)

from extract_utils.fixups_blob import (
    blob_fixups_user_type,
    blob_fixup,
)

namespace_imports = [
    'vendor/oneplus/sm8150-common',
]

blob_fixups: blob_fixups_user_type = {
    'vendor/lib/hw/audio.primary.msmnile.so': blob_fixup().replace_needed("/vendor/lib/liba2dpoffload.so", "/odm/lib/liba2dpoffload.so"),
}

module = ExtractUtilsModule(
    'guacamole',
    'oneplus',
    namespace_imports=namespace_imports,
    blob_fixups=blob_fixups,
    check_elf=True,
)

if __name__ == '__main__':
    utils = ExtractUtils.device_with_common(
        module, 'sm8150-common', module.vendor
    )
    utils.run()
