
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
#include "ShaderModule.hpp"
#include "Shader.hpp"

NS_STITCHES_BEGIN
class Shader;
class ShaderCache
{
public:
    static ShaderCache* getInstance();

    static void destroyInstance();

    Shader* getBuiltinShader(ShaderType type) const;

    void removeShader(Shader* shader);

    void removeUnusedShader();

    void removeAllShaders();

protected:
    ShaderCache() = default;
    virtual ~ShaderCache();

    /**
     * Pre-load programs into cache.
     */
    bool init();

    /// Add built-in program
    void addShader(ShaderType type);

    static std::unordered_map<ShaderType, Shader*> mCachedShaders;
    static ShaderCache *mSharedProgramCache;
};

NS_STITCHES_END
