//
// Created by Murphy on 2020/8/9.
//

/**
 * ShaderCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 13:38
 **/
#pragma once

#include "Stitches.hpp"
#include "Utils/Ref.hpp"
#include "ShaderModule.hpp"

NS_STITCHES_BEGIN

class ShaderCache : public Ref
{
public:
    /** returns the shared instance */
    static ShaderCache* getInstance();

    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();

    /**
     * Create a vertex shader module and add it to cache.
     * If it is created before, then just return the cached shader module.
     * @param shaderSource The source code of the shader.
     */
    static ShaderModule* newVertexShaderModule(const std::string& shaderSource);

    /**
     * Create a fragment shader module.
     * If it is created before, then just return the cached shader module.
     * @param shaderSource The source code of the shader.
     */
    static ShaderModule* newFragmentShaderModule(const std::string& shaderSource);

    /**
     * Remove all unused shaders.
     */
    void removeUnusedShader();

protected:
    virtual ~ShaderCache();

    /**
     * Initial shader cache.
     * @return true if initial successful, otherwise false.
     */
    bool init();

    /**
     * New a shaderModule.
     * If it was created before, then just return the cached shader module.
     * Otherwise add it to cache and return the object.
     * @param stage Specifies whether is vertex shader or fragment shader.
     * @param source Specifies shader source.
     * @return A ShaderModule object.
     */
    static ShaderModule* newShaderModule(ShaderStage stage, const std::string& shaderSource);

    static std::unordered_map<std::size_t, ShaderModule*> _cachedShaders;
    static ShaderCache* _sharedShaderCache;
};

NS_STITCHES_END
