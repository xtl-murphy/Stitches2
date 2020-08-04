
/**
 * DepthStencilState
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:16
 **/
#include "DepthStencilState.hpp"

NS_STITCHES_BEGIN

bool StencilDescriptor::operator==(const StencilDescriptor &rhs) const
{
    return (stencilFailureOperation == rhs.stencilFailureOperation &&
            depthFailureOperation == rhs.depthFailureOperation &&
            depthStencilPassOperation == rhs.depthStencilPassOperation &&
            stencilCompareFunction == rhs.stencilCompareFunction &&
            readMask == rhs.readMask &&
            writeMask == rhs.writeMask);

}

DepthStencilState::DepthStencilState(const DepthStencilDescriptor& descriptor)
        : _depthStencilInfo(descriptor)
{
    _isBackFrontStencilEqual = descriptor.backFaceStencil == descriptor.frontFaceStencil;
}

DepthStencilState::~DepthStencilState()
{}

NS_STITCHES_END