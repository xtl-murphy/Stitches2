
/**
 * ProgramState
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:45
 **/
#pragma once

#include "Stitches.hpp"
#include "Texture.hpp"
#include "VertexLayout.hpp"
#include "Program.hpp"

NS_STITCHES_BEGIN

struct TextureInfo
{
    TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<TextureBackend*> _textures);
    TextureInfo() = default;
    TextureInfo(const TextureInfo &);
    ~TextureInfo();
    TextureInfo& operator=(TextureInfo&& rhs);
    TextureInfo& operator=(const TextureInfo& rhs);

    void retainTextures();
    void releaseTextures();

    std::vector<uint32_t> slot;
    std::vector<TextureBackend*> textures;

};

class ProgramState : public Ref
{
public:
    using UniformCallback = std::function<void(ProgramState*, const UniformLocation &)>;

    /**
     * @param program Specifies the program.
     */
    ProgramState(Program* program);

    ///destructor
    virtual ~ProgramState();

    /**
     * Deep clone ProgramState
     */
    ProgramState *clone() const;

    /**
     * Get the program object.
     */
    Program* getProgram() const { return mProgram; }

    /**
     * Specify the value of a uniform variable for the current program state object.
     * @param uniformLocation Specifies the uniform location.
     * @param data Specifies the new values to be used for the specified uniform variable.
     * @param size Specifies the uniform data size.
     */
    void setUniform(const UniformLocation& uniformLocation, const void* data, std::size_t size);

    /**
     * Get uniform location in given uniform name.
     * @param uniform Specifies the uniform name.
     * @return Uniform location.
     * @see `backend::UniformLocation getUniformLocation(backend::Uniform name) const`
     */
    UniformLocation getUniformLocation(const std::string& uniform) const;

    /**
     * Get uniform location in a more efficient way by the given built-in uniform name.
     * @param uniform Specifies the engin built-in uniform name.
     * @return Uniform location.
     * @see `backend::UniformLocation getUniformLocation(backend::Uniform name) const`
     */
    UniformLocation getUniformLocation(Uniform name) const;

    /**
     * Get an attribute location by the actual attribute name.
     * @param name Specifies the attribute name.
     * @return Attribute location.
     * @see `int getAttributeLocation(const std::string& name) const`
     */
    inline int getAttributeLocation(const String& name) const { return mProgram->getAttributeLocation(name); }

    /**
     * Get an attribute location by the engine built-in attribute name.
     * @param name Specifies the built-in attribute name.
     * @return Attribute location.
     * @see `int getAttributeLocation(const std::string& name) const`
     */
    inline int getAttributeLocation(Attribute name) const { return mProgram->getAttributeLocation(name); }

    /**
     * A callback to update unifrom.
     * @param uniformLocation Specifies the uniform location.
     * @param unifromCallback Specifies a callback function to update the uniform.
     */
    void setCallbackUniform(const UniformLocation&, const UniformCallback &);

    /**
     * Set texture.
     * @param uniformLocation Specifies texture location.
     * @param slot Specifies texture slot selector.
     * @param texture Specifies a pointer to backend texture.
     */
    void setTexture(const UniformLocation& uniformLocation, uint32_t slot, TextureBackend* texture);

    /**
     * Set textures in array.
     * @param uniformLocation Specifies texture location.
     * @param slots Specifies texture slot selector.
     * @param textures Specifies a vector of backend texture object.
     */
    void setTextureArray(const UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<TextureBackend*> textures);

    /**
     * Get vertex texture informations
     * @return Vertex texture informations. Key is the texture location, Value store the texture informations
     */
    inline const std::unordered_map<int, TextureInfo>& getVertexTextureInfos() const { return mVertexTextureInfos; }

    /**
     * Get fragment texture informations
     * @return Fragment texture informations. Key is the texture location, Value store the texture informations
     */
    inline const std::unordered_map<int, TextureInfo>& getFragmentTextureInfos() const { return mFragmentTextureInfos; }

    /**
     * Get the uniform callback function.
     * @return Uniform callback funciton.
     */
    inline const std::unordered_map<UniformLocation, UniformCallback, UniformLocation>& getCallbackUniforms() const { return mCallbackUniforms; }

    /**
     * Get vertex uniform buffer. The buffer store all the vertex uniform's data.
     * @param[out] buffer Specifies the pointer points to a vertex uniform storage.
     * @param[out] size Specifies the size of the buffer in bytes.
     */
    void getVertexUniformBuffer(char** buffer, std::size_t& size) const;

    /**
     * Get fragment uniform buffer. The buffer store all the fragment uniform's data for metal.
     * @param[out] buffer Specifies the pointer points to a fragment uniform storage.
     * @param[out] size Specifies the size of the buffer in bytes.
     */
    void getFragmentUniformBuffer(char** buffer, std::size_t& size) const;
    class AutoBindingResolver {
            public:
            AutoBindingResolver();
            virtual ~AutoBindingResolver();
            /**
            * Called when an unrecognized uniform variable is encountered
            * during material loading.
            *
            * Implementations of this method should do a string comparison on the passed
            * in name parameter and decide whether or not they should handle the
            * parameter. If the parameter is not handled, false should be returned so
            * that other auto binding resolvers get a chance to handle the parameter.
            * Otherwise, the parameter should be set or bound and true should be returned.
            *
            * @param programState The ProgramState
            * @param uniformName Name of the uniform
            * @param autoBinding Name of the auto binding to be resolved.
            *
            * @return True if the auto binding is handled and the associated parameter is
            *      bound, false otherwise.
            */
            virtual bool resolveAutoBinding(ProgramState *, const std::string &uniformName, const std::string &autoBinding) = 0;
    };

    /**
    * Sets a uniform auto-binding.
    *
    * This method parses the passed in autoBinding string and attempts to convert it
    * to an enumeration value. If it matches to one of the predefined strings, it will create a
    * callback to get the correct value at runtime.
    *
    * @param uniformName The name of the material parameter to store an auto-binding for.
    * @param autoBinding A string matching one of the built-in AutoBinding enum constants.
    */
    void setParameterAutoBinding(const std::string &uniformName, const std::string &autoBinding);

    inline std::shared_ptr<VertexLayout> getVertexLayout() const { return mVertexLayout; }

protected:

    ProgramState();

    /**
     * Set the vertex uniform data.
     * @param location Specifies the uniform location.
     * @param data Specifies the new values to be used for the specified uniform variable.
     * @param size Specifies the uniform data size.
     */
    void setVertexUniform(int location, const void* data, std::size_t size, std::size_t offset);

    /**
     * Set the fargment uniform data.
     * @param location Specifies the uniform location.
     * @param data Specifies the new values to be used for the specified uniform variable.
     * @param size Specifies the uniform data size.
     */
    void setFragmentUniform(int location, const void* data, std::size_t size);

    /**
     * Set texture.
     * @param location Specifies the location of texture.
     * @param slot Specifies slot selector of texture.
     * @param texture Specifies the texture to set in given location.
     * @param textureInfo Specifies the texture information to update.
     */
    void setTexture(int location, uint32_t slot, TextureBackend* texture, std::unordered_map<int, TextureInfo>& textureInfo);

    /**
     * Set textures in array.
     * @param location Specifies the location of texture.
     * @param slots Specifies slot selector of texture.
     * @param textures Specifies the texture to set in given location.
     * @param textureInfo Specifies the texture information to update.
     */
    void setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<TextureBackend*> textures, std::unordered_map<int, TextureInfo>& textureInfo);

    /**
     * Reset uniform informations when EGL context lost
     */
    void resetUniforms();

    ///Initialize.
    bool init(Program* program);

#ifdef CC_USE_METAL
        /**
     * float3 etc in Metal has both sizeof and alignment same as float4, convert it before fill into uniform buffer
     * @param uniformInfo Specifies the uniform information.
     * @param srcData Specifies the new values to be used for the specified uniform variable.
     * @param srcSize Specifies the uniform data size.
     * @param uniformBuffer Specifies the uniform buffer to update.
     */
    void convertAndCopyUniformData(const backend::UniformInfo& uniformInfo, const void* srcData, std::size_t srcSize, void* buffer);
#endif
    /**
    * Applies the specified custom auto-binding.
    *
    * @param uniformName Name of the shader uniform.
    * @param autoBinding Name of the auto binding.
    */
    void applyAutoBinding(const std::string &, const std::string &);

    Program* mProgram = nullptr;
    std::unordered_map<UniformLocation, UniformCallback, UniformLocation>   mCallbackUniforms;
    char* mVertexUniformBuffer = nullptr;
    char* mFragmentUniformBuffer = nullptr;
    std::size_t mVertexUniformBufferSize = 0;
    std::size_t mFragmentUniformBufferSize = 0;

    std::unordered_map<int, TextureInfo>                    mVertexTextureInfos;
    std::unordered_map<int, TextureInfo>                    mFragmentTextureInfos;

    std::unordered_map<std::string, std::string>            mAutoBindings;

    static std::vector<AutoBindingResolver*>                mCustomAutoBindingResolvers;
    std::shared_ptr<VertexLayout> mVertexLayout = std::make_shared<VertexLayout>();

};

NS_STITCHES_END

