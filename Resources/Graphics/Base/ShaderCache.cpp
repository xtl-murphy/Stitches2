
/**
 * ShaderCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#include "ShaderCache.hpp"

USING_STITCHES_VK


ShaderCache::~ShaderCache()
{
    for(auto& program : cachedShaders)
    {
//        CC_SAFE_RELEASE(program.second);
    }
//    CCLOGINFO("deallocing ProgramCache: %p", this);
    ShaderCache::destroyInstance();
}

ShaderCache *ShaderCache::getInstance()
{
    if (!sharedProgramCache)
    {

    }
    return sharedProgramCache;
}

void ShaderCache::destroyInstance()
{

}

ShaderModule *ShaderCache::newShaderModule(ShaderStage stage, const String &shaderSource)
{
    std::size_t key = std::hash<std::string>{}(shaderSource);
    auto iter = cachedShaders.find(key);
    if (cachedShaders.end() != iter)
        return iter->second;
    return nullptr;
}
