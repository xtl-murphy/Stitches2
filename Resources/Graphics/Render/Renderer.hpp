
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:51
 **/
#pragma once

#include "Graphics/Command/RenderCommand.hpp"
#include "Stitches.hpp"

NS_STITCHES_BEGIN

class Renderer
{
public:

    /**The max number of vertices in a vertex buffer object.*/
    static const int VBO_SIZE = 65536;
    /**The max number of indices in a index buffer.*/
    static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4;
    /**The rendercommands which can be batched will be saved into a list, this is the reserved size of this list.*/
    static const int BATCH_TRIAGCOMMAND_RESERVED_SIZE = 64;
    /**Reserved for material id, which means that the command could not be batched.*/
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;
    /**Constructor.*/
    Renderer();
    /**Destructor.*/
    ~Renderer();

    //TODO: manage GLView inside Render itself
    void init();

    /** Adds a `RenderComamnd` into the renderer */
    void addCommand(RenderCommand* command);

    /** Adds a `RenderComamnd` into the renderer specifying a particular render queue ID */
    void addCommand(RenderCommand* command, int renderQueueID);

    /** Pushes a group into the render queue */
    void pushGroup(int renderQueueID);

    /** Pops a group from the render queue */
    void popGroup();

    /** Creates a render queue and returns its Id */
    int createRenderQueue();

    /** Renders into the GLView all the queued `RenderCommand` objects */
    void render();

    /** Cleans all `RenderCommand`s in the queue */
    void clean();

    /* returns the number of drawn batches in the last frame */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* RenderCommands (except) TrianglesCommand should update this value */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* returns the number of drawn triangles in the last frame */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* RenderCommands (except) TrianglesCommand should update this value */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };
    /* clear draw stats */
    void clearDrawStats() { _drawnBatches = _drawnVertices = 0; }

    /**
     Set render targets. If not set, will use default render targets. It will effect all commands.
     @flags Flags to indicate which attachment to be replaced.
     @colorAttachment The value to replace color attachment, only one color attachment supported now.
     @depthAttachment The value to repalce depth attachment.
     @stencilAttachment The value to replace stencil attachment. Depth attachment and stencil attachment
                        can be the same value.
     */
    void setRenderTarget(RenderTargetFlag flags, Texture2D* colorAttachment, Texture2D* depthAttachment, Texture2D* stencilAttachment);
    /**
    Set clear values for each attachment.
    @flags Flags to indicate which attachment clear value to be modified.
    @color The clear color value.
    @depth The clear depth value.
    @stencil The clear stencil value.
    */
    void clear(ClearFlag flags, const Color4F& color, float depth, unsigned int stencil, float globalOrder);

    /**
     * Get color attachment.
     * @return Color attachment.
     */
    Texture2D* getColorAttachment() const;

    /**
     * Get depth attachment.
     * @return Depth attachment.
     */
    Texture2D* getDepthAttachment() const;

    /**
     * Get stencil attachment.
     * @return Stencil attachment.
     */
    Texture2D* getStencilAttachment() const;

    /**
     * Get color clear value.
     * @return Color clear value.
     */
    const Color4F& getClearColor() const;

    /**
     * Get depth clear value.
     * @return Depth clear value.
     */
    float getClearDepth() const;

    /**
     * Get the index when the stencil buffer is cleared.
     * @return The index used when the stencil buffer is cleared.
     */
    unsigned int getClearStencil() const;

    /**
     * Get the clear flag.
     * @return The clear flag.
     */
    ClearFlag getClearFlag() const;

    /**
     * Get the render target flag.
     * @return The render target flag.
     */
    RenderTargetFlag getRenderTargetFlag() const;

    // depth/stencil state.

    /**
     * Enable/disable depth test.
     * @param value true means enable depth test, otherwise false.
     */
    void setDepthTest(bool value);

    /**
     *  Enable/disable to update depth buffer.
     * @param value true means enable writing into the depth buffer, otherwise false.
     */
    void setDepthWrite(bool value);

    /**
     * Set depth compare function.
     * @param func Specifies the value used for depth buffer comparisons.
     */
    void setDepthCompareFunction(CompareFunction func);

    /**
     * Get whether depth test state is enabled or disabled.
     * @return true if depth test is enabled, otherwise false.
     */
    bool getDepthTest() const;

    /**
     * Get whether writing to depth buffer is enabled or not.
     * @return true if enable writing into the depth buffer, false otherwise.
     */
    bool getDepthWrite() const;

    /**
     * Get depth compare function.
     * @return Depth compare function.
     */
    CompareFunction getDepthCompareFunction() const;

    /**
     * Enable/disable stencil test.
     * @param value true means enable stencil test, otherwise false.
     */
    void setStencilTest(bool value);

    /**
     * Set front and back function and reference value for stencil testing.
     * @param func Specifies the stencil test function.
     * @param ref Specifies the reference value for the stencil test.
     * @readMask Specifies a mask that is ANDed with both the reference value and the stored stencil value when the test is done.
     */
    void setStencilCompareFunction(CompareFunction func, unsigned int ref, unsigned int readMask);

    /**
     * Set front and back stencil test actions.
     * @param stencilFailureOp Specifies the action to take when the stencil test fails.
     * @param depthFailureOp Specifies the stencil action when the stencil test passes, but the depth test fails.
     * @param stencilDepthPassOp Specifies the stencil action when both the stencil test and the depth test pass, or when the stencil test passes and either there is no depth buffer or depth testing is not enabled.
     */
    void setStencilOperation(StencilOperation stencilFailureOp,
                             StencilOperation depthFailureOp,
                             StencilOperation stencilDepthPassOp);

    /**
     * Control the front and back writing of individual bits in the stencil planes.
     * @param mask Specifies a bit mask to enable and disable writing of individual bits in the stencil planes.
     */
    void setStencilWriteMask(unsigned int mask);

    /**
     * Get whether stencil test is enabled or not.
     * @return true if stencil test is enabled, false otherwise.
     */
    bool getStencilTest() const;

    /// Get the action to take when the stencil test fails.
    StencilOperation getStencilFailureOperation() const;

    /// Get the stencil action when the stencil test passes, but the depth test fails.
    StencilOperation getStencilPassDepthFailureOperation() const;

    /// Get the stencil action when both the stencil test and the depth test pass, or when the stencil test passes and either there is no depth buffer or depth testing is not enabled.
    StencilOperation getStencilDepthPassOperation() const;

    /// Get the stencil test function.
    CompareFunction getStencilCompareFunction() const;

    /**
     * Get the stencil readMask.
     * @return Stencil read mask.
     * @see `setStencilCompareFunction(CompareFunction func, unsigned int ref, unsigned int readMask)`
     */
    unsigned int getStencilReadMask() const;

    /**
     * Get the stencil write mask.
     * @return Stencil write mask.
     * @see `setStencilWriteMask(unsigned int mask)`
     */
    unsigned int getStencilWriteMask() const;

    /**
     * Get stencil reference value set by `setStencilCompareFunction`.
     * @return Stencil reference value.
     * @see `setStencilCompareFunction(CompareFunction func, unsigned int ref, unsigned int readMask)`
     */
    unsigned int getStencilReferenceValue() const;

    /**
     * Fixed-function state
     * @param mode Controls if primitives are culled when front facing, back facing, or not culled at all.
     */
    void setCullMode(CullMode mode) { _cullMode = mode; }

    /**
     * Get cull mode.
     * @return The cull mode.
     */
    CullMode getCullMode() const { return _cullMode; }

    /**
     * Fixed-function state
     * @param winding The winding order of front-facing primitives.
     */
    void setWinding(Winding winding) { _winding = winding; }

    /**
     * Get winding mode.
     * @return The winding mode.
     */
    Winding getWinding() const { return _winding; }

    /**
     * Fixed-function state
     * @param x The x coordinate of the upper-left corner of the viewport.
     * @param y The y coordinate of the upper-left corner of the viewport.
     * @param w The width of the viewport, in pixels.
     * @param h The height of the viewport, in pixels.
     */
    void setViewPort(int x, int y, unsigned int w, unsigned int h);

    /// Get viewport.
    const Viewport& getViewport() const { return _viewport; }

    /**
     * Enable/disable scissor test.
     * @param enabled true if enable scissor test, false otherwise.
     */
    void setScissorTest(bool enabled);

    /**
     * Fixed-function state
     * @param x, y Specifies the lower left corner of the scissor box
     * @param wdith Specifies the width of the scissor box
     * @param height Specifies the height of the scissor box
     */
    void setScissorRect(float x, float y, float width, float height);
    bool getScissorTest() const; ///< Get whether scissor test is enabled or not.
    const ScissorRect& getScissorRect() const; ///< Get scissor rectangle.

    /** returns whether or not a rectangle is visible or not */
    bool checkVisibility(const Mat4& transform, const Size& size);

protected:
    friend class Director;
    friend class GroupCommand;

    /**
     * Create and reuse vertex and index buffer for triangleCommand.
     * When queued vertex or index count exceed the limited value, a new vertex or index buffer will be created.
     */
    class TriangleCommandBufferManager
    {
    public:
        ~TriangleCommandBufferManager();

        /**
         * Create a new vertex buffer and a index buffer and push it to cache.
         * @note Should invoke firstly.
         */
        void init();

        /**
         * Reset avalable buffer index to zero.
         * That means when get vertex buffer or index buffer, the earliest created buffer object in the cache will be returned.
         */
        void putbackAllBuffers();

        /**
         * Buffer will be created If next buffer unavailable in the cache, otherwise set the buffer index in order to get the next available buffer.
         */
        void prepareNextBuffer();

        Buffer* getVertexBuffer() const; ///< Get the vertex buffer.
        Buffer* getIndexBuffer() const; ///< Get the index buffer.

    private:
        void createBuffer();

        int _currentBufferIndex = 0;
        std::vector<Buffer*> _vertexBufferPool;
        std::vector<Buffer*> _indexBufferPool;
    };

    inline GroupCommandManager * getGroupCommandManager() const { return _groupCommandManager; }
    void drawBatchedTriangles();
    void drawCustomCommand(RenderCommand* command);
    void drawMeshCommand(RenderCommand* command);
    void captureScreen(RenderCommand* command);

    void beginFrame(); /// Indicate the begining of a frame
    void endFrame(); /// Finish a frame.

    ///Draw the previews queued triangles and flush previous context
    void flush();

    void flush2D();

    void flush3D();

    void flushTriangles();

    void processRenderCommand(RenderCommand* command);
    void processGroupCommand(GroupCommand*);
    void visitRenderQueue(RenderQueue& queue);
    void doVisitRenderQueue(const std::vector<RenderCommand*>&);

    void fillVerticesAndIndices(const TrianglesCommand* cmd, unsigned int vertexBufferOffset);
    void beginRenderPass(RenderCommand*); /// Begin a render pass.

    /**
     * Building a programmable pipeline involves an expensive evaluation of GPU state.
     * So a new render pipeline object will be created only if it hasn't been created before.
     * @param pipelineDescriptor Specifies the pipeline descriptor.
     * @param renderPassDescriptor Specifies the render pass descriptor.
     */
    void setRenderPipeline(const PipelineDescriptor&, const RenderPassDescriptor&);

    void pushStateBlock();

    void popStateBlock();

    RenderPipeline* _renderPipeline = nullptr;

    Viewport _viewport;
    CullMode _cullMode  = CullMode::NONE;
    Winding _winding    = Winding::COUNTER_CLOCK_WISE; //default front face is CCW in GL

    std::stack<int> _commandGroupStack;

    std::vector<RenderQueue> _renderGroups;

    std::vector<TrianglesCommand*> _queuedTriangleCommands;

    //for TrianglesCommand
    V3F_C4B_T2F _verts[VBO_SIZE];
    unsigned short _indices[INDEX_VBO_SIZE];
    Buffer* _vertexBuffer = nullptr;
    Buffer* _indexBuffer = nullptr;
    TriangleCommandBufferManager _triangleCommandBufferManager;

    CommandBuffer* _commandBuffer = nullptr;
    RenderPassDescriptor _renderPassDescriptor;
    DepthStencilDescriptor _depthStencilDescriptor;

    // Internal structure that has the information for the batches
    struct TriBatchToDraw
    {
        TrianglesCommand* cmd = nullptr;  // needed for the Material
        unsigned int indicesToDraw = 0;
        unsigned int offset = 0;
    };
    // capacity of the array of TriBatches
    int _triBatchesToDrawCapacity = 500;
    // the TriBatches
    TriBatchToDraw* _triBatchesToDraw = nullptr;

    unsigned int _queuedTotalVertexCount = 0;
    unsigned int _queuedTotalIndexCount = 0;
    unsigned int _queuedVertexCount = 0;
    unsigned int _queuedIndexCount = 0;
    unsigned int _filledIndex = 0;
    unsigned int _filledVertex = 0;

    // stats
    unsigned int _drawnBatches = 0;
    unsigned int _drawnVertices = 0;
    //the flag for checking whether renderer is rendering
    bool _isRendering = false;
    bool _isDepthTestFor2D = false;

    GroupCommandManager* _groupCommandManager = nullptr;

    unsigned int _stencilRef = 0;

    // weak reference
    Texture2D* _colorAttachment = nullptr;
    Texture2D* _depthAttachment = nullptr;
    Texture2D* _stencilAttachment = nullptr;
    Color4F _clearColor = Color4F::BLACK;
    ClearFlag _clearFlag;
    RenderTargetFlag _renderTargetFlag = RenderTargetFlag::COLOR;

    struct ScissorState
    {
        ScissorRect rect;
        bool isEnabled = false;
    };
    ScissorState _scissorState;

    struct StateBlock{
        bool depthTest = false;
        bool depthWrite = false;
        CullMode  cullMode = CullMode::NONE;
    };

    std::deque<StateBlock> _stateBlockStack;
};

NS_STITCHES_END

