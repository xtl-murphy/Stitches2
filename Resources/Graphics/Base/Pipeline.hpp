//
// Created by Murphy on 2020/8/6.
//

/**
 * Pipeline
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/6 23:05
 **/
#pragma once

#include "Stitches.hpp"
#include "RenderPassDescriptor.hpp"

NS_STITCHES_BEGIN

class Pipeline
{
public:
    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderPassDescriptor) = 0;

protected:
    virtual ~Pipeline() = default;
};

NS_STITCHES_END

