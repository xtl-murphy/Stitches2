
/**
 * TrianglesCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/12 22:53
 **/
#include "TrianglesCommand.hpp"

NS_STITCHES_BEGIN

TrianglesCommand::TrianglesCommand()
{
    _type = RenderCommand::Type::TRIANGLES_COMMAND;
}

void TrianglesCommand::init(float globalOrder, Texture2D* texture, const BlendFunc& blendType, const Triangles& triangles, const Matrix4& mv, uint32_t flags)
{
    RenderCommand::init(globalOrder, mv, flags);

    _triangles = triangles;
    if(_triangles.indexCount % 3 != 0)
    {
        unsigned int count = _triangles.indexCount;
        _triangles.indexCount = count / 3 * 3;
        LOGE("TrianglesCommand", "Resize indexCount from %d to %d, size must be multiple times of 3", count, _triangles.indexCount);
    }
    _mv = mv;

    if (_programType != _pipelineDescriptor.programState->getProgram()->getProgramType() ||
        _texture != texture->getBackendTexture() ||
        _blendType != blendType)
    {
        _programType = _pipelineDescriptor.programState->getProgram()->getProgramType();
        _texture = texture->getBackendTexture();
        _blendType = blendType;

        //since it would be too expensive to check the uniforms, simplify enable batching for built-in program.
        if(_programType == ProgramType::CUSTOM_PROGRAM)
            setSkipBatching(true);

        //TODO: minggo set it in Node?
        auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
        blendDescriptor.blendEnabled = true;
        blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendType.src;
        blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendType.dst;

        if(!isSkipBatching())
            generateMaterialID();
    }
}

void TrianglesCommand::updateMaterialID()
{
    setSkipBatching(false);
    generateMaterialID();
}

TrianglesCommand::~TrianglesCommand()
{
}

void TrianglesCommand::generateMaterialID()
{
    struct
    {
        void* texture;
        ProgramType programType;
        BlendFactor src;
        BlendFactor dst;
    }hashMe;

    // NOTE: Initialize hashMe struct to make the value of padding bytes be filled with zero.
    // It's important since XXH32 below will also consider the padding bytes which probably
    // are set to random values by different compilers.
    memset(&hashMe, 0, sizeof(hashMe));

    hashMe.texture = _texture;
    hashMe.src = _blendType.src;
    hashMe.dst = _blendType.dst;
    hashMe.programType = _programType;
//    _materialID = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
}

NS_STITCHES_END