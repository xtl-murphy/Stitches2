
/**
 * VertexLayout
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:57
 **/
#include "VertexLayout.hpp"

NS_STITCHES_BEGIN

void VertexLayout::setAttribute(const String &name, std::size_t index, VertexFormat format, std::size_t offset, bool needToBeNormallized)
{
    if(index == -1)
        return;

    mAttributes[name] = { name, index, format, offset, needToBeNormallized };
}

void VertexLayout::setLayout(std::size_t stride)
{
    mStride = stride;
}

NS_STITCHES_END