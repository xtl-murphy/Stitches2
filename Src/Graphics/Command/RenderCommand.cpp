
/**
 * RenderCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:42
 **/
#include "RenderCommand.hpp"

NS_STITCHES_BEGIN

RenderCommand::RenderCommand()
{
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::init(float globalZOrder, const Matrix4 &transform, unsigned int flags)
{
    _globalOrder = globalZOrder;
//    if (flags & Node::FLAGS_RENDER_AS_3D)
//    {
//        if (Camera::getVisitingCamera())
//            _depth = Camera::getVisitingCamera()->getDepthInView(transform);
//
//        set3D(true);
//    }
//    else
//    {
//        set3D(false);
//        _depth = 0;
//    }

    set3D(false);
    _depth = 0;
}

void RenderCommand::printID()
{
    printf("Command Depth: %f\n", _globalOrder);
}

NS_STITCHES_END