
/**
 * RenderQueue
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:46
 **/
#pragma once

#include "Stitches.hpp"
#include "RenderCommand.hpp"

NS_STITCHES_BEGIN

class RenderQueue
{
public:
    /**
    RenderCommand will be divided into Queue Groups.
    */
    enum QUEUE_GROUP
    {
        /**Objects with globalZ smaller than 0.*/
        GLOBALZ_NEG = 0,
        /**Opaque 3D objects with 0 globalZ.*/
        OPAQUE_3D = 1,
        /**Transparent 3D objects with 0 globalZ.*/
        TRANSPARENT_3D = 2,
        /**2D objects with 0 globalZ.*/
        GLOBALZ_ZERO = 3,
        /**Objects with globalZ bigger than 0.*/
        GLOBALZ_POS = 4,
        QUEUE_COUNT = 5,
    };

public:
    /**Constructor.*/
    RenderQueue();
    /**Push a renderCommand into current renderqueue.*/
    void push_back(RenderCommand* command);
    /**Return the number of render commands.*/
    ssize_t size() const;
    /**Sort the render commands.*/
    void sort();
    /**Treat sorted commands as an array, access them one by one.*/
    RenderCommand* operator[](ssize_t index) const;
    /**Clear all rendered commands.*/
    void clear();
    /**Realloc command queues and reserve with given size. Note: this clears any existing commands.*/
    void realloc(size_t reserveSize);
    /**Get a sub group of the render queue.*/
    std::vector<RenderCommand*>& getSubQueue(QUEUE_GROUP group) { return _commands[group]; }
    /**Get the number of render commands contained in a subqueue.*/
    ssize_t getSubQueueSize(QUEUE_GROUP group) const { return _commands[group].size(); }

    static bool compareRenderCommand(RenderCommand* a, RenderCommand* b);
    static bool compare3DCommand(RenderCommand* a, RenderCommand* b);

protected:
    /**The commands in the render queue.*/
    std::vector<RenderCommand*> _commands[QUEUE_COUNT];

    /**Cull state.*/
    bool _isCullEnabled;
    /**Depth test enable state.*/
    bool _isDepthEnabled;
    /**Depth buffer write state.*/
    bool _isDepthWrite;
};

NS_STITCHES_END

