

/**
 * RenderCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:42
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/RenderPassDescriptor.hpp"
#include "Math/Math.hpp"

NS_STITCHES_BEGIN

class RenderCommand
{
public:
    /**Enum the type of render command. */
    enum class Type
    {
        /** Reserved type.*/
        UNKNOWN_COMMAND,
        /** Quad command, used for draw quad.*/
        QUAD_COMMAND,
        /**Custom command, used to draw things other then TRIANGLES_COMMAND.*/
        CUSTOM_COMMAND,
        /**Group command, which can group command in a tree hierarchy.*/
        GROUP_COMMAND,
        /**Mesh command, used to draw 3D meshes.*/
        MESH_COMMAND,
        /**Triangles command, used to draw triangles.*/
        TRIANGLES_COMMAND,
        /**Callback command, used for calling callback for rendering.*/
        CALLBACK_COMMAND,
        CAPTURE_SCREEN_COMMAND
    };

    /**
     Init function, will be called by all the render commands.
     @param globalZOrder The global order of command, used for rendercommand sorting.
     @param modelViewTransform Modelview matrix when submitting the render command.
     @param flags Flag used to indicate whether the command should be draw at 3D mode or not.
     */
    void init(float globalZOrder, const Matrix4& modelViewTransform, unsigned int flags);

    /** Get global Z order. */
    float getGlobalOrder() const { return _globalOrder; }

    /** Returns the Command type. */
    Type getType() const { return _type; }

    /** Returns whether is transparent. */
    bool isTransparent() const { return _isTransparent; }

    /** Set transparent flag. */
    void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    /**
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     */
    bool isSkipBatching() const { return _skipBatching; }
    /**Set skip batching.*/
    void setSkipBatching(bool value) { _skipBatching = value; }
    /**Whether the command should be rendered at 3D mode.*/
    bool is3D() const { return _is3D; }
    /**Set the command rendered in 3D mode or not.*/
    void set3D(bool value) { _is3D = value; }
    /**Get the depth by current model view matrix.*/
    float getDepth() const { return _depth; }
    /// Can use the result to change the descriptor content.
    inline PipelineDescriptor& getPipelineDescriptor() { return _pipelineDescriptor; }

    const Matrix4& getMV() const { return _mv; }

protected:
    /**Constructor.*/
    RenderCommand();
    /**Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();

    /**Type used in order to avoid dynamic cast, faster. */
    Type _type = RenderCommand::Type::UNKNOWN_COMMAND;

    /** Commands are sort by global Z order. */
    float _globalOrder = 0.f;

    /** Transparent flag. */
    bool  _isTransparent = true;

    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _skipBatching = false;

    /** Is the command been rendered on 3D pass. */
    bool _is3D = false;

    /** Depth from the model view matrix.*/
    float _depth = 0.f;

    Matrix4 _mv;

    PipelineDescriptor _pipelineDescriptor;
};

NS_STITCHES_END

