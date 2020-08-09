
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
#include "ProgramGL.hpp"
NS_STITCHES_BEGIN

class RenderPipelineGL : public RenderPipeline
{
public:
    RenderPipelineGL() = default;
    ~RenderPipelineGL();

    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderpassDescriptor) override;

    inline ProgramGL* getShader() const { return mProgram; }

private:
    void updateBlendState(const BlendDescriptor& descriptor);

    ProgramGL* mProgram = nullptr;
};

NS_STITCHES_END
