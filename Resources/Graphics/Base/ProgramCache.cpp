
/**
 * ProgramCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#include "ProgramCache.hpp"

USING_STITCHES_VK

std::unordered_map<ProgramType, Program*> ProgramCache::mCachedShaders;
ProgramCache* ProgramCache::mSharedProgramCache = nullptr;

ProgramCache::~ProgramCache()
{
    for(auto& program : mCachedShaders)
    {
        delete program.second;
    }
//    CCLOGINFO("deallocing ProgramCache: %p", this);
    ProgramCache::destroyInstance();
}

ProgramCache *ProgramCache::getInstance()
{
    if (!mSharedProgramCache)
    {
        mSharedProgramCache = new (std::nothrow) ProgramCache();
        if(!mSharedProgramCache->init())
        {
            delete mSharedProgramCache;
        }
    }
    return mSharedProgramCache;
}

void ProgramCache::destroyInstance()
{
    if (mSharedProgramCache != nullptr)
    {
        delete mSharedProgramCache;
    }
}

Program *ProgramCache::getBuiltinShader(ProgramType type) const
{
    const auto& iter = ProgramCache::mCachedShaders.find(type);
    if (ProgramCache::mCachedShaders.end() != iter)
    {
        return iter->second;
    }
    return nullptr;
}

void ProgramCache::removeShader(Program *shader)
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

void ProgramCache::removeUnusedShader()
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

void ProgramCache::removeAllShaders()
{
    for (auto& shader : mCachedShaders)
    {
        delete shader.second;
    }
    mCachedShaders.clear();
}

bool ProgramCache::init()
{
    return false;
}

void ProgramCache::addShader(ProgramType type)
{

}

