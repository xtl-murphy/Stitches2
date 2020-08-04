
/**
 * Shader
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:11
 **/

#include "Stitches.hpp"
#include "Types.hpp"
#include "ShaderModule.hpp"
NS_STITCHES_BEGIN

class Shader
{

public:
    Shader(const String& vs, const String& fs);

    /**
     * Get engine built-in program.
     * @param type Specifies the built-in program type.
     */
//    static Shader* getBuiltinProgram(ProgramType type);

    virtual UniformLocation getUniformLocation(const String& uniform) const = 0;

    virtual UniformLocation getUniformLocation(Uniform name) const = 0;

    virtual int getAttributeLocation(const String& name) const =  0;

    virtual int getAttributeLocation(Attribute name) const =  0;

    virtual int getMaxVertexLocation() const = 0;

    virtual int getMaxFragmentLocation() const = 0;

    virtual const std::unordered_map<String, AttributeBindInfo> getActiveAttributes() const = 0;

    const String& getVertexShader() const { return vertexShader; }

    const String& getFragmentShader() const { return fragmentShader; }
private:
    String vertexShader;
    String fragmentShader;
};

NS_STITCHES_END