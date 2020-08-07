//
// Created by Murphy on 2020/8/6.
//

/**
 * RenderPipelineGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/6 23:16
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/Pipeline.hpp"
#include "ShaderGL.hpp"
NS_STITCHES_BEGIN

class RenderPipelineGL : public Pipeline
{
public:
    RenderPipelineGL() = default;
    ~RenderPipelineGL();

    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderpassDescriptor) override;

    inline ShaderGL* getProgram() const { return shader; }

private:
    void updateBlendState(const BlendDescriptor& descriptor);
private:
    ShaderGL* shader = nullptr;
};

NS_STITCHES_END

