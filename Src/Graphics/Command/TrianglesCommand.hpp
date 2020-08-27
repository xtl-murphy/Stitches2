
/**
 * TrianglesCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/12 22:53
 **/
#pragma once

#include <Graphics/Render/Texture2D.hpp>
#include <Graphics/OpenGLES/TextureGL.hpp>
#include "Stitches.hpp"
#include "RenderCommand.hpp"
NS_STITCHES_BEGIN



class TrianglesCommand : public RenderCommand
{
public:
    struct Triangles
    {
        Triangles(V3F_C4B_T2F* _verts, unsigned short* _indices, unsigned int _vertCount, unsigned int _indexCount)
                : verts(_verts)
                , indices(_indices)
                , vertCount(_vertCount)
                , indexCount(_indexCount)
        {}

        Triangles() {}

        /**Vertex data pointer.*/
        V3F_C4B_T2F* verts = nullptr;
        /**Index data pointer.*/
        unsigned short* indices = nullptr;
        /**The number of vertices.*/
        unsigned int vertCount = 0;
        /**The number of indices.*/
        unsigned int indexCount = 0;
    };

    /**Constructor.*/
    TrianglesCommand();
    /**Destructor.*/
    ~TrianglesCommand();

    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param texture The texture used in renderring.
     @param blendType Blend function for the command.
     @param triangles Rendered triangles for the command.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, Texture2DGL* texture, const BlendFunc& blendType,  const Triangles& triangles, const Matrix4& mv, uint32_t flags);
    /**Get the material id of command.*/
    uint32_t getMaterialID() const { return _materialID; }
    /**Get a const reference of triangles.*/
    const Triangles& getTriangles() const { return _triangles; }
    /**Get the vertex count in the triangles.*/
    size_t getVertexCount() const { return _triangles.vertCount; }
    /**Get the index count of the triangles.*/
    size_t getIndexCount() const { return _triangles.indexCount; }
    /**Get the vertex data pointer.*/
    const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**Get the index data pointer.*/
    const unsigned short* getIndices() const { return _triangles.indices; }
    /**Get the model view matrix.*/
    const Matrix4& getModelView() const { return _mv; }

    /** update material ID */
    void updateMaterialID();

protected:
    /**Generate the material ID by textureID, glProgramState, and blend function.*/
    void generateMaterialID();

    /**Generated material id.*/
    uint32_t _materialID = 0;

    /**Rendered triangles.*/
    Triangles _triangles;
    /**Model view matrix when rendering the triangles.*/
    Matrix4 _mv;

    uint8_t _alphaTextureID = 0; // ANDROID ETC1 ALPHA supports.

    // Cached value to determine to generate material id or not.
    BlendFunc _blendType = BlendFunc::DISABLE;
    ProgramType _programType = ProgramType::Normal_Image;
    TextureBackend* _texture = nullptr;
};

NS_STITCHES_END

