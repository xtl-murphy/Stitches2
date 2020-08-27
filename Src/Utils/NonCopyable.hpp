
/**
 * NonCopyable
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/6/22 23:05
 **/

#pragma once

#include "Stitches.hpp"

NS_STITCHES_BEGIN
class NonCopyable
{
protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

public:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable(NonCopyable &&) noexcept = default;
    NonCopyable &operator=(const NonCopyable &) = delete;
    NonCopyable &operator=(NonCopyable &&) noexcept = default;
};
NS_STITCHES_END