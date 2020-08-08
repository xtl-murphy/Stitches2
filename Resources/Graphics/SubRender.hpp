
/**
 * SubRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 18:20
 **/

#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/CommandBuffer.hpp"
#include "Utils/TypeInfo.hpp"
NS_STITCHES_BEGIN

class SubRender
{
public:
    explicit SubRender() { }

    virtual ~SubRender() = default;

    /**
     * Runs the render pipeline in the current renderpass.
     * @param commandBuffer The command buffer to record render command into.
     */
    virtual void Render(const CommandBuffer &commandBuffer) = 0;

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool enable) { this->enabled = enable; }
private:
    bool enabled = true;
};

template class TypeInfo<SubRender>;

/**
 * Gets the Type ID for the SubRender.
 * @tparam T The SubRender type.
 * @return The Type ID.
 */
template<typename T>
TypeId GetSubRenderTypeId() noexcept
{
    static_assert(std::is_base_of<SubRender, T>::value, "T must be a SubRender.");

    return TypeInfo<SubRender>::GetTypeId<T>();
}

NS_STITCHES_END