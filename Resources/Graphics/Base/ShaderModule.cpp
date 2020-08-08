
/**
 * ShaderModule
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:35
 **/
#include "ShaderModule.hpp"

USING_STITCHES_VK

ShaderModule::ShaderModule(ShaderStage stage) : stage(stage)
{

}

ShaderModule::~ShaderModule()
{

}

ShaderStage Stitches::ShaderModule::getShaderStage() const
{
    return this->stage;
}
