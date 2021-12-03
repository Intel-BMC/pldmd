/**
 * Copyright © 2021 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "pldm.hpp"

#include <string>

namespace pldm
{
namespace platform
{
namespace association
{
/** @brief Get sensor association path of tid*/
std::string getPath(pldm_tid_t tid);

/** @brief Set sensor association path of tid*/
void setPath(pldm_tid_t tid, const std::string& path);

} // namespace association
} // namespace platform
} // namespace pldm
