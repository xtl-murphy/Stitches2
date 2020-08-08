

/**
 * Types
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:17
 **/
#include "Types.hpp"

USING_STITCHES_VK

bool UniformLocation::operator==(const UniformLocation &other) const
{
    return (this->shaderStage == other.shaderStage &&
            this->location[0] == other.location[0] &&
            this->location[1] == other.location[1]);
}

std::size_t UniformLocation::operator()(const UniformLocation &uniform) const
{
    return (((size_t) this->shaderStage) & 0xF)|((size_t)(this->location[0] << 4))|((size_t)(this->location[1] << 8));
}
