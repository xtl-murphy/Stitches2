
/**
 * Program
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:11
 **/

#include "Program.hpp"

NS_STITCHES_BEGIN

Program::Program(const String& vs, const String& fs)
        : mVertexShader(vs)
        , mFragmentShader(fs)
{
}

void Program::setProgramType(ProgramType type)
{
    mProgramType = type;
}

Program* Program::getBuiltinProgram(ProgramType type)
{
    return ProgramCache::getInstance()->getBuiltinShader(type);
}

NS_STITCHES_END