/*
 * Copyright (C) 2013 The Android Open Source Project
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

#include <errno.h>

#include <hardware/memtrack.h>

#include "memtrack_exynos5.h"

int exynos5_memtrack_init(const struct memtrack_module *module __unused)
{
    return 0;
}

int exynos5_memtrack_get_memory(const struct memtrack_module *module __unused,
                                pid_t pid,
                                int type,
                                struct memtrack_record *records,
                                size_t *num_records)
{
    if (type == MEMTRACK_TYPE_GL) {
        return mali_memtrack_get_memory(pid, type, records, num_records);
    }

    if (type == MEMTRACK_TYPE_GRAPHICS) {
        return ion_memtrack_get_memory(pid, type, records, num_records);
    }

    return -EINVAL;
}

static struct hw_module_methods_t memtrack_module_methods = {
    .open = NULL,
};

struct memtrack_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = MEMTRACK_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = MEMTRACK_HARDWARE_MODULE_ID,
        .name = "Exynos5 Memory Tracker HAL",
        .author = "The Android Open Source Project",
        .methods = &memtrack_module_methods,
    },

    .init = exynos5_memtrack_init,
    .getMemory = exynos5_memtrack_get_memory,
};

