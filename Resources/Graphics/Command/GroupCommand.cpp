
/**
 * GroupCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/12 23:16
 **/
#include "GroupCommand.hpp"

NS_STITCHES_BEGIN

GroupCommandManager::GroupCommandManager()
{

}

GroupCommandManager::~GroupCommandManager()
{

}

bool GroupCommandManager::init()
{
    //0 is the default render group
    _groupMapping[0] = true;
    return true;
}

int GroupCommandManager::getGroupID()
{
    //Reuse old id
    if (!_unusedIDs.empty())
    {
        int groupID = *_unusedIDs.rbegin();
        _unusedIDs.pop_back();
        _groupMapping[groupID] = true;
        return groupID;
    }

    //Create new ID
//    int newID = _groupMapping.size();
//    int newID = Director::getInstance()->getRenderer()->createRenderQueue();
//    _groupMapping[newID] = true;

    return 0;
}

void GroupCommandManager::releaseGroupID(int groupID)
{
    _groupMapping[groupID] = false;
    _unusedIDs.push_back(groupID);
}

GroupCommand::GroupCommand()
{
    _type = RenderCommand::Type::GROUP_COMMAND;
//    _renderQueueID = Director::getInstance()->getRenderer()->getGroupCommandManager()->getGroupID();
}

void GroupCommand::init(float globalOrder)
{
    _globalOrder = globalOrder;
//    auto manager = Director::getInstance()->getRenderer()->getGroupCommandManager();
//    manager->releaseGroupID(_renderQueueID);
//    _renderQueueID = manager->getGroupID();
}

GroupCommand::~GroupCommand()
{
//    Director::getInstance()->getRenderer()->getGroupCommandManager()->releaseGroupID(_renderQueueID);
}

NS_STITCHES_END