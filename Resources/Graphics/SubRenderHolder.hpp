
/**
 * SubRenderHolder
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:24
 **/
#pragma once


#include "Stitches.hpp"
#include "Graphics/Base/CommandBuffer.hpp"
#include "SubRender.hpp"
#include "Utils/NonCopyable.hpp"
#include "Utils/TypeInfo.hpp"
NS_STITCHES_BEGIN

class SubRender;
class CommandBuffer;

class SubRenderHolder : NonCopyable
{
public:
    /**
     * Gets a SubRender.
     * @tparam T The SubRender type.
     * @return The SubRender.
     */
    template<typename T>
    T *Get() const
    {
        const auto typeId = GetSubRenderTypeId<T>();

        auto it = subRenders.find(typeId);

        if (it == subRenders.end() || !it->second) {
            //throw std::runtime_error("SubRender Holder does not have requested SubRender");
            return nullptr;
        }

        return static_cast<T *>(it->second.get());
    }

    /**
     * Adds a SubRender.
     * @tparam T The SubRender type.
     * @param stage The SubRender pipeline stage.
     * @param subRender The subrender.
     * @return The added renderer.
     */
    template<typename T, typename... Args>
    T *Add(const CommandBuffer::Stage &stage, std::unique_ptr<T> &&subRender) {
        // Remove previous SubRender, if it exists.
        //Remove<T>();

        const auto typeId = GetSubRenderTypeId<T>();

        // Insert the stage value
        stages.insert({StageIndex(stage, subRenders.size()), typeId});

        // Then, add the SubRender
        subRenders[typeId] = std::move(subRender);
        return static_cast<T *>(subRenders[typeId].get());
    }

    /**
     * Removes a SubRender.
     * @tparam T The SubRender type.
     */
    template<typename T>
    void Remove()
    {
        const auto typeId = GetSubRenderTypeId<T>();

        // Remove the stage value for this SubRender.
        RemoveSubrenderStage(typeId);

        // Then, remove the SubRender.
        subRenders.erase(typeId);
    }

    /**
     * Clears all subrenders.
     */
    void Clear();

private:
    using StageIndex = std::pair<CommandBuffer::Stage, std::size_t>;

    void RemoveSubRenderStage(const TypeId &id);

    /**
     * Iterates through all Subrenders.
     * @param stage The SubRender stage.
     * @param commandBuffer The command buffer to record render command into.
     */
    void RenderStage(const CommandBuffer::Stage &stage, const CommandBuffer &commandBuffer);

    /// List of all Subrenders.
    std::unordered_map<TypeId, std::unique_ptr<SubRender>> subRenders;
    /// List of subrender stages.
    std::multimap<StageIndex, TypeId> stages;
};

NS_STITCHES_END


