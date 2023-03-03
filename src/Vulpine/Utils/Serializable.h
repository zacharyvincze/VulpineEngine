#pragma once

#include <nlohmann/json.hpp>

#include "Vulpine/vppch.h"

namespace Vulpine
{
class Serializable
{
  public:
    virtual void ToObject(nlohmann::json &j) = 0;

    // TODO: This does not need to be implemented at the moment. Commenting out to
    // avoid annoying compiler warnings like the brilliant developer I am.

    // virtual nlohmann::json ToJson() {}
};
} // namespace Vulpine