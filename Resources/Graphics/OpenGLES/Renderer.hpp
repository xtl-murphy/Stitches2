
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:37
 **/

#pragma once

#include "Stitches.hpp"
#include "Graphics/SubRenderHolder.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Base/Types.hpp"
NS_STITCHES_BEGIN

class SubRenderHolder;
class Renderer
{
    friend class Graphics;
public:
    /**
     * Creates a new renderer, fill {@link renderStages} in your subclass of this.
     */
    Renderer() = default;

    virtual ~Renderer() = default;

    /**
     * Run when switching to this scene from another, use this method to create {@link SubRender}'s.
     */
    virtual void Start() = 0;

    /**
     * Run when updating the renderer manager.
     */
    virtual void Update() = 0;

    /**
     * Checks whether a SubRender exists or not.
     * @tparam T The SubRender type.
     * @return If the SubRender has the System.
     */
    /*template<typename T>
    bool HasSubrender() const  {
        return subrenderHolder.Has<T>();
    }*/

    /**
     * Gets a SubRender.
     * @tparam T The SubRender type.
     * @return The SubRender.
     */
    template<typename T>
    T *GetSubRender() const
    {
        return subRenderHolder.Get<T>();
    }

//    RenderStage *GetRenderStage(uint32_t index) const
//    {
//        if (renderStages.empty() || renderStages.size() < index)
//        {
//            return nullptr;
//        }
//
//        return renderStages.at(index).get();
//    }

protected:
    /**
     * Adds a SubRender.
     * @tparam T The SubRender type.
     * @param pipelineStage The SubRender pipeline stage.
     * @tparam Args The constructor arg types.
     * @param args The constructor arguments.
     */
    template<typename T, typename... Args>
    T *AddSubRender(const CommandBuffer::Stage &Stage, Args &&...args)
    {
        return subRenderHolder.Add<T>(Stage, std::make_unique<T>(Stage, std::forward<Args>(args)...));
    }

    /**
     * Removes a SubRender.
     * @tparam T The SubRender type.
     */
    template<typename T>
    void RemoveSubRender()
    {
        subRenderHolder.Remove<T>();
    }

    /**
     * Clears all Subrenders.
     */
    void ClearSubRenders()
    {
        subRenderHolder.Clear();
    }

//    void AddRenderStage(std::unique_ptr<RenderStage> &&renderStage)
//    {
//        renderStages.emplace_back(std::move(renderStage));
//    }

private:
    bool started = false;
    SubRenderHolder subRenderHolder;
//    std::vector<std::unique_ptr<RenderStage>> renderStages;
};

NS_STITCHES_END
