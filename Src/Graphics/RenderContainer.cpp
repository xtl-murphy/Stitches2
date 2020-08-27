
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:37
 **/

#include "RenderContainer.hpp"

NS_STITCHES_BEGIN

RenderContainer::RenderContainer()
{

}

void RenderContainer::ClearSubRenders()
{
    for (auto sub : subRenders)
    {
        delete sub;
    }

    subRenders.clear();
}




NS_STITCHES_END