

/**
 * GroupCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/12 23:16
 **/
#pragma once

#include "Stitches.hpp"
#include "RenderCommand.hpp"

NS_STITCHES_BEGIN

class GroupCommandManager : public Ref
{
public:
    int getGroupID();
    void releaseGroupID(int groupID);

protected:
    friend class Renderer;
    GroupCommandManager();
    ~GroupCommandManager();
    bool init();
    std::unordered_map<int, bool> _groupMapping;
    std::vector<int> _unusedIDs;
};

class GroupCommand : public RenderCommand
{
    public:
    /**@{
     Constructor and Destructor.
     */
    GroupCommand();
    ~GroupCommand();
    /**@}*/

    /**Init function for group command*/
    void init(float globalOrder);

    /**called by renderer, get the group ID.*/
    int getRenderQueueID() const { return _renderQueueID; }

    protected:
    int _renderQueueID;
};

NS_STITCHES_END

