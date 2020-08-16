
/**
 * Program
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:11
 **/

#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
#include "ProgramCache.hpp"
#include "Utils/Ref.hpp"
NS_STITCHES_BEGIN

class Program : public Ref
{

public:
    Program(const String& vs, const String& fs);

    /**
     * Get engine built-in program.
     * @param type Specifies the built-in program type.
     */
    static Program* getBuiltinProgram(ProgramType type);

    virtual UniformLocation getUniformLocation(const String& uniform) const = 0;

    virtual UniformLocation getUniformLocation(Uniform name) const = 0;

    virtual int getAttributeLocation(const String& name) const =  0;

    virtual int getAttributeLocation(Attribute name) const =  0;

    virtual int getMaxVertexLocation() const = 0;

    virtual int getMaxFragmentLocation() const = 0;

    virtual const std::unordered_map<String, AttributeBindInfo> getActiveAttributes() const = 0;

    const String& getVertexShader() const { return mVertexShader; }

    const String& getFragmentShader() const { return mFragmentShader; }

    ProgramType getProgramType() const { return mProgramType; }

    virtual std::size_t getUniformBufferSize(ShaderStage stage) const =0;

    virtual const UniformInfo& getActiveUniformInfo(ShaderStage stage, int location) const = 0;

protected:
    void setProgramType(ProgramType type);

    friend class ProgramCache;

    String mVertexShader;
    String mFragmentShader;
    ProgramType mProgramType = ProgramType::Normal_Image;
};

NS_STITCHES_END