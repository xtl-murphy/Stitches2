
/**
 * DepthStencilState
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:16
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
NS_STITCHES_BEGIN

/**
 * Stencil descriptor.
 */

struct StencilDescriptor
{
    bool operator ==(const StencilDescriptor& rhs) const;

    StencilOperation stencilFailureOperation = StencilOperation::KEEP;
    StencilOperation depthFailureOperation = StencilOperation::KEEP;
    StencilOperation depthStencilPassOperation = StencilOperation::KEEP;
    CompareFunction stencilCompareFunction = CompareFunction::ALWAYS;
    unsigned int readMask = 0;
    unsigned int writeMask = 0;
};

/**
* Depth and stencil descriptor.
*/
struct DepthStencilDescriptor
{
    CompareFunction depthCompareFunction = CompareFunction::LESS;
    bool depthWriteEnabled = false;
    bool depthTestEnabled = false;

    bool stencilTestEnabled = false;
    StencilDescriptor backFaceStencil;
    StencilDescriptor frontFaceStencil;
};

class DepthStencilState
{
protected:
    /**
     * @param descriptor Specifies depth and stencil descriptor.
     */
    DepthStencilState(const DepthStencilDescriptor& descriptor);
    virtual ~DepthStencilState();

    DepthStencilDescriptor _depthStencilInfo; ///< depth and stencil descriptor.
    bool _isBackFrontStencilEqual = false; ///< Does front stencil status equals to back stencil's.
};

NS_STITCHES_END

