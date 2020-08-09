
/**
 * ShaderCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 13:38
 **/
#include <Graphics/OpenGLES/ShaderModuleGL.hpp>
#include "ShaderCache.hpp"

NS_STITCHES_BEGIN

std::unordered_map<std::size_t, ShaderModule*> ShaderCache::_cachedShaders;
ShaderCache* ShaderCache::_sharedShaderCache = nullptr;

ShaderCache* ShaderCache::getInstance()
{
    if(!_sharedShaderCache)
    {
        _sharedShaderCache = new (std::nothrow) ShaderCache();
        if(!_sharedShaderCache->init())
        {
            SAFE_RELEASE(_sharedShaderCache);
        }
    }
    return _sharedShaderCache;
}

void ShaderCache::destroyInstance()
{
    SAFE_RELEASE_NULL(_sharedShaderCache);
}

ShaderCache::~ShaderCache()
{
    for(auto& shaderModule : _cachedShaders)
    {
        SAFE_RELEASE(shaderModule.second);
    }
//    CCLOGINFO("deallocing ProgramCache: %p", this);
}

bool ShaderCache::init()
{
    return true;
}

ShaderModule* ShaderCache::newVertexShaderModule(const std::string& shaderSource)
{
    auto vertexShaderModule = newShaderModule(ShaderStage::VERTEX, shaderSource);
    return vertexShaderModule;
}

ShaderModule* ShaderCache::newFragmentShaderModule(const std::string& shaderSource)
{
    auto fragmentShaderModule = newShaderModule(ShaderStage::FRAGMENT, shaderSource);
    return fragmentShaderModule;
}

ShaderModule* ShaderCache::newShaderModule(ShaderStage stage, const std::string& shaderSource)
{
    std::size_t key = std::hash<std::string>{}(shaderSource);
    auto iter = _cachedShaders.find(key);
    if (_cachedShaders.end() != iter)
        return iter->second;

    auto shader = new ShaderModuleGL(stage, shaderSource);
    shader->setHashValue(key);
    _cachedShaders.emplace(key, shader);

    return shader;
}

void ShaderCache::removeUnusedShader()
{
    for (auto iter = _cachedShaders.cbegin(); iter != _cachedShaders.cend();)
    {
        auto shaderModule = iter->second;
        if (shaderModule->getReferenceCount() == 1)
        {
            //            CCLOG("cocos2d: TextureCache: removing unused program");
            shaderModule->release();
            iter = _cachedShaders.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

NS_STITCHES_END