
/**
 * VertexLayout
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:57
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"

NS_STITCHES_BEGIN

class VertexLayout
{
public:
    struct Attribute
    {
        Attribute() = default;
        Attribute(const std::string& _name, std::size_t _index, VertexFormat _format, std::size_t _offset, bool needToBeNormallized)
                : name(_name)
                , format(_format)
                , offset(_offset)
                , index(_index)
                , needToBeNormallized(needToBeNormallized)
        {}

        std::string name; ///< name is used in opengl
        VertexFormat format = VertexFormat::INT3;
        std::size_t offset = 0;
        std::size_t index = 0; ///< index is used in metal
        bool needToBeNormallized = false;
    };

    VertexLayout() = default;

    /**
     * Set attribute values to name.
     * @param name Specifies the attribute name.
     * @param index Specifies the index of the generic vertex attribute to be modified.
     * @param format Specifies how the vertex attribute data is laid out in memory.
     * @param offset Specifies the byte offset to the first component of the first generic vertex attribute.
     * @param needToBeNormallized Specifies whether fixed-point data values should be normalized (true) or converted directly as fixed-point values (false) when they are accessed.
     */
    void setAttribute(const String& name, std::size_t index, VertexFormat format, std::size_t offset, bool needToBeNormallized);

    /**
     * Set stride of vertices.
     * @param stride Specifies the distance between the data of two vertices, in bytes.
     */
    void setLayout(std::size_t stride);

    /**
     * Get the distance between the data of two vertices, in bytes.
     * @return The distance between the data of two vertices, in bytes.
     */
    inline std::size_t getStride() const { return mStride; }

    /**
     * Get vertex step function. Default value is VERTEX.
     * @return Vertex step function.
     * @note Used in metal.
     */
    inline VertexStepMode getVertexStepMode() const { return mStepMode; }

    /**
     * Get attribute informations
     * @return Atrribute informations.
     */
    inline const std::unordered_map<std::string, Attribute>& getAttributes() const { return mAttributes; }

    /**
     * Check if vertex layout has been set.
     */
    inline bool isValid() const { return mStride != 0; }

private:
    std::unordered_map<std::string, Attribute> mAttributes;
    std::size_t mStride = 0;
    VertexStepMode mStepMode = VertexStepMode::VERTEX;
};

NS_STITCHES_END

