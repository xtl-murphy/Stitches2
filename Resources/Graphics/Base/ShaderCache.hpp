
/**
 * ShaderCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
#include "Shader.hpp"

NS_STITCHES_BEGIN

class ShaderCache
{
private:
    ShaderCache() = default;
    virtual ~ShaderCache();

    /**
     * Pre-load programs into cache.
     */
    bool init();

    /// Add built-in program
    void addShader(ShaderType type);

    static std::unordered_map<ShaderType, Shader*> cachedShaders;
    static ShaderCache *sharedProgramCache;

public:
    /** returns the shared instance */
    static ShaderCache* getInstance();

    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();

    /// get built-in program
    Shader* getBuiltinShader(ShaderType type) const;

    /**
     * Remove a program object from cache.
     * @param program Specifies the program object to move.
     */
    void removeShader(Shader* shader);

    /**
     * Remove all unused program objects from cache.
     */
    void removeUnusedShader();

    /**
     * Remove all program objects from cache.
     */
    void removeAllShaders();
};

NS_STITCHES_END

