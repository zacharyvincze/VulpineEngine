#include "Utils.h"

namespace Vulpine
{
namespace Utils
{
SDL_Rect ConvertVectorToRect(std::vector<int> &vec)
{
    return (SDL_Rect){vec[0], vec[1], vec[2], vec[3]};
}

Vec2 ConvertVectorToVec2(std::vector<float> &vec)
{
    return (Vec2){vec[0], vec[1]};
}
} // namespace Utils
} // namespace Vulpine