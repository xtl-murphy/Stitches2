
/**
 * ProgramCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#include <Graphics/OpenGLES/ProgramGL.hpp>
#include "ProgramCache.hpp"
#include "Graphics/Shader/Shader.hpp"
USING_STITCHES_VK

std::unordered_map<ProgramType, Program*> ProgramCache::mCachedPrograms;
ProgramCache* ProgramCache::mSharedProgramCache = nullptr;

ProgramCache::~ProgramCache()
{
    for(auto& program : mCachedPrograms)
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
    const auto& iter = ProgramCache::mCachedPrograms.find(type);
    if (ProgramCache::mCachedPrograms.end() != iter)
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

    for (auto it = mCachedPrograms.cbegin(); it != mCachedPrograms.cend();)
    {
        if (it->second == shader)
        {
            delete it->second;
            it = mCachedPrograms.erase(it);
            break;
        }
        else
            ++it;
    }
}

void ProgramCache::removeUnusedShader()
{
//    for (auto iter = mCachedPrograms.cbegin(); iter != mCachedPrograms.cend();)
//    {
//        auto program = iter->second;
//        if (program->getReferenceCount() == 1)
//        {
////            CCLOG("cocos2d: TextureCache: removing unused program");
//            program->release();
//            iter = mCachedPrograms.erase(iter);
//        }
//        else
//        {
//            ++iter;
//        }
//    }
}

void ProgramCache::removeAllShaders()
{
    for (auto& shader : mCachedPrograms)
    {
        delete shader.second;
    }
    mCachedPrograms.clear();
}

bool ProgramCache::init()
{
    addProgram(ProgramType::Normal_Image);
    return true;
}

void ProgramCache::addProgram(ProgramType type)
{
    Program* program = nullptr;
    switch (type)
    {
        case ProgramType::Normal_Image:
            program = new ProgramGL(ImageNormalVert, ImageNormalVertFrag);
            break;
    }
    program->setProgramType(type);
    ProgramCache::mCachedPrograms.emplace(type, program);
}

