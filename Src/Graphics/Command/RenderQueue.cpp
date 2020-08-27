
/**
 * RenderQueue
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:46
 **/
#include "RenderQueue.hpp"

NS_STITCHES_BEGIN


bool RenderQueue::compareRenderCommand(RenderCommand *a, RenderCommand *b)
{
    return a->getGlobalOrder() < b->getGlobalOrder();
}

bool RenderQueue::compare3DCommand(RenderCommand *a, RenderCommand *b)
{
    return  a->getDepth() > b->getDepth();
}

RenderQueue::RenderQueue()
{
}

void RenderQueue::push_back(RenderCommand* command)
{
    float z = command->getGlobalOrder();
    if(z < 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_NEG].push_back(command);
    }
    else if(z > 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_POS].push_back(command);
    }
    else
    {
        if(command->is3D())
        {
            if(command->isTransparent())
            {
                _commands[QUEUE_GROUP::TRANSPARENT_3D].push_back(command);
            }
            else
            {
                _commands[QUEUE_GROUP::OPAQUE_3D].push_back(command);
            }
        }
        else
        {
            _commands[QUEUE_GROUP::GLOBALZ_ZERO].push_back(command);
        }
    }
}

ssize_t RenderQueue::size() const
{
    ssize_t result(0);
    for(int index = 0; index < QUEUE_GROUP::QUEUE_COUNT; ++index)
    {
        result += _commands[index].size();
    }

    return result;
}

void RenderQueue::sort()
{
    // Don't sort _queue0, it already comes sorted
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::TRANSPARENT_3D]), std::end(_commands[QUEUE_GROUP::TRANSPARENT_3D]), RenderQueue::compare3DCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_NEG]), std::end(_commands[QUEUE_GROUP::GLOBALZ_NEG]), RenderQueue::compareRenderCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_POS]), std::end(_commands[QUEUE_GROUP::GLOBALZ_POS]), RenderQueue::compareRenderCommand);
}

RenderCommand* RenderQueue::operator[](ssize_t index) const
{
    for(int queIndex = 0; queIndex < QUEUE_GROUP::QUEUE_COUNT; ++queIndex)
    {
        if(index < static_cast<ssize_t>(_commands[queIndex].size()))
            return _commands[queIndex][index];
        else
        {
            index -= _commands[queIndex].size();
        }
    }

//    CCASSERT(false, "invalid index");
    return nullptr;
}

void RenderQueue::clear()
{
    for(int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
    {
        _commands[i].clear();
    }
}

void RenderQueue::realloc(size_t reserveSize)
{
    for(int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
    {
        _commands[i] = std::vector<RenderCommand*>();
        _commands[i].reserve(reserveSize);
    }
}



NS_STITCHES_END