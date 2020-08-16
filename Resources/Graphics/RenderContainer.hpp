
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:37
 **/

#pragma once

#include "Stitches.hpp"
#include "SubRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Base/Types.hpp"

NS_STITCHES_BEGIN


class SubRender;
enum class SubRenderType;
class RenderContainer
{
    friend class Graphics;
public:
    /**
     * Creates a new renderer, fill {@link renderStages} in your subclass of this.
     */
    RenderContainer();

    virtual ~RenderContainer() = default;

    virtual void Start() = 0;

    virtual void Update() = 0;

protected:
    template<typename T>
    T *AddSubRender(SubRenderType type)
    {
        auto subRender = new T(type);
        this->subRenders.push_back(subRender);
        return subRender;
    }
//
    void ClearSubRenders();
private:
    bool started = false;
    std::vector<SubRender *> subRenders;
};

NS_STITCHES_END

