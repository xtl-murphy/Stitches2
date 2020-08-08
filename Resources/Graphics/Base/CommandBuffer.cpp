//
// Created by Murphy on 2020/8/1.
//

/**
 * CommandBuffer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:01
 **/
#include "CommandBuffer.hpp"

USING_STITCHES_VK

void CommandBuffer::setStencilReferenceValue(uint32_t value)
{
    stencilReferenceValueBack = stencilReferenceValueFront = value;
}

void CommandBuffer::setStencilReferenceValue(unsigned int frontRef, unsigned int backRef)
{
    stencilReferenceValueFront = frontRef;
    stencilReferenceValueBack = backRef;
}