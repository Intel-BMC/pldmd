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

#include "platform_association.hpp"

#include "pldm.hpp"

#include <filesystem>
#include <optional>
#include <phosphor-logging/log.hpp>
#include <string>

namespace pldm
{
namespace platform
{
namespace association
{

#if defined(EXPOSE_BASEBOARD_SENSOR)

static constexpr const char* mctpConfigIntf =
    "xyz.openbmc_project.Configuration.MctpConfiguration";

/** @brief Get sensor association path
 *  @return DBus path of baseboard
 *
 *  @todo Use PldmConfiguration interface when it is implemented
 */
std::string getPath()
{
    static std::optional<std::string> baseboardPath{};

    if (!baseboardPath.has_value())
    {
        auto bus = getSdBus();
        auto method_call = bus->new_method_call(
            "xyz.openbmc_project.ObjectMapper",
            "/xyz/openbmc_project/object_mapper",
            "xyz.openbmc_project.ObjectMapper", "GetSubTreePaths");
        method_call.append("/xyz/openbmc_project/inventory/", 0,
                           std::array<std::string, 1>({mctpConfigIntf}));
        auto reply = bus->call(method_call);

        std::vector<std::string> paths;
        reply.read(paths);

        if (paths.empty() || paths[0].empty())
        {
            baseboardPath = "";
            phosphor::logging::log<phosphor::logging::level::ERR>(
                "Failed to get the baseboard DBus object path");
        }
        else
        {
            baseboardPath = std::filesystem::path(paths[0]).parent_path();
        }
    }

    return baseboardPath.value();
}

#else

/** @brief Get sensor association path
 *  @return Empty string
 */
std::string getPath()
{
    return {};
}

#endif

} // namespace association
} // namespace platform
} // namespace pldm
