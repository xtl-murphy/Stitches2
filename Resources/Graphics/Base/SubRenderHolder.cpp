
/**
 * SubRenderHolder
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:24
 **/
#include "SubRenderHolder.hpp"

NS_STITCHES_BEGIN

void SubRenderHolder::Clear()
{
    stages.clear();
}

void SubRenderHolder::RemoveSubRenderStage(const TypeId &id)
{
    for (auto it = stages.begin(); it != stages.end();)
    {
        if (it->second == id)
        {
            it = stages.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SubRenderHolder::RenderStage(const CommandBuffer::Stage &stage, const CommandBuffer &commandBuffer)
{
    for (const auto &[stageIndex, typeId] : stages)
    {
        if (stageIndex.first != stage)
        {
            continue;
        }

        if (auto &subrender = subrenders[typeId])
        {
            if (subrender->IsEnabled()) {
                subrender->Render(commandBuffer);
            }
        }
    }
}

NS_STITCHES_END