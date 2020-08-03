//
// Created by Murphy on 2020/8/2.
//

/**
 * Graphics
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 16:41
 **/
#pragma once

#include "Stitches.hpp"
#include "Utils/Module.hpp"

NS_STITCHES_BEGIN

class Graphics : public Module::Registrar<Graphics, Module::Stage::Render>
{
public:
    Graphics();
    ~Graphics();

    void Update() override;
};

NS_STITCHES_END

