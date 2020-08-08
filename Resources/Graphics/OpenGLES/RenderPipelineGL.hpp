
/**
 * RenderPipelineGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/6 23:16
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/RenderPipeline.hpp"
#include "ShaderGL.hpp"
NS_STITCHES_BEGIN

class RenderPipelineGL : public RenderPipeline
{
public:
    RenderPipelineGL() = default;
    ~RenderPipelineGL();

    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderpassDescriptor) override;

    inline ShaderGL* getShader() const { return mShader; }

private:
    void updateBlendState(const BlendDescriptor& descriptor);

    ShaderGL* mShader = nullptr;
};

NS_STITCHES_END
