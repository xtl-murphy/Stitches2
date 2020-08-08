
/**
 * ShaderCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#include "ShaderCache.hpp"

USING_STITCHES_VK

std::unordered_map<ShaderType, Shader*> ShaderCache::mCachedShaders;
ShaderCache* ShaderCache::mSharedProgramCache = nullptr;

ShaderCache::~ShaderCache()
{
    for(auto& program : mCachedShaders)
    {
        delete program.second;
    }
//    CCLOGINFO("deallocing ProgramCache: %p", this);
    ShaderCache::destroyInstance();
}

ShaderCache *ShaderCache::getInstance()
{
    if (!mSharedProgramCache)
    {
        mSharedProgramCache = new (std::nothrow) ShaderCache();
        if(!mSharedProgramCache->init())
        {
            delete mSharedProgramCache;
        }
    }
    return mSharedProgramCache;
}

void ShaderCache::destroyInstance()
{
    if (mSharedProgramCache != nullptr)
    {
        delete mSharedProgramCache;
    }
}

Shader *ShaderCache::getBuiltinShader(ShaderType type) const
{
    const auto& iter = ShaderCache::mCachedShaders.find(type);
    if (ShaderCache::mCachedShaders.end() != iter)
    {
        return iter->second;
    }
    return nullptr;
}

void ShaderCache::removeShader(Shader *shader)
{
    if (!shader)
    {
        return;
    }

    for (auto it = mCachedShaders.cbegin(); it != mCachedShaders.cend();)
    {
        if (it->second == shader)
        {
            delete it->second;
            it = mCachedShaders.erase(it);
            break;
        }
        else
            ++it;
    }
}

void ShaderCache::removeUnusedShader()
{
//    for (auto iter = mCachedShaders.cbegin(); iter != mCachedShaders.cend();)
//    {
//        auto program = iter->second;
//        if (program->getReferenceCount() == 1)
//        {
////            CCLOG("cocos2d: TextureCache: removing unused program");
//            program->release();
//            iter = mCachedShaders.erase(iter);
//        }
//        else
//        {
//            ++iter;
//        }
//    }
}

void ShaderCache::removeAllShaders()
{
    for (auto& shader : mCachedShaders)
    {
        delete shader.second;
    }
    mCachedShaders.clear();
}

bool ShaderCache::init()
{
    return false;
}

void ShaderCache::addShader(ShaderType type)
{

}
