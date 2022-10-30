#pragma once

#include "Vulpine/Core/DataStructures/Vector.h"
#include "Vulpine/vppch.h"

namespace Vulpine
{
namespace Utils
{
extern SDL_Rect ConvertVectorToRect(std::vector<int> &vec);
extern Vec2 ConvertVectorToVec2(std::vector<float> &vec);
extern float RandomFloat(float min, float max);
} // namespace Utils
} // namespace Vulpine