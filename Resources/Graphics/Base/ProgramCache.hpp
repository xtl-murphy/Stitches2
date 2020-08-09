
/**
 * ProgramCache
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:12
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
#include "ShaderModule.hpp"
#include "Program.hpp"

NS_STITCHES_BEGIN
class Program;
class ProgramCache
{
public:
    static ProgramCache* getInstance();

    static void destroyInstance();

    Program* getBuiltinShader(ProgramType type) const;

    void removeShader(Program* shader);

    void removeUnusedShader();

    void removeAllShaders();

protected:
    ProgramCache() = default;
    virtual ~ProgramCache();

    /**
     * Pre-load programs into cache.
     */
    bool init();

    /// Add built-in program
    void addShader(ProgramType type);

    static std::unordered_map<ProgramType, Program*> mCachedShaders;
    static ProgramCache *mSharedProgramCache;
};

NS_STITCHES_END
