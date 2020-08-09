

/**
 * Ref
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 2:05
 **/
#include "Ref.hpp"

NS_STITCHES_BEGIN

Ref::Ref() : _referenceCount(1) // when the Ref is created, the reference count of it is 1
{

}

Ref::~Ref()
{
}

void Ref::retain()
{

    ++_referenceCount;
}

void Ref::release()
{
    --_referenceCount;
    if (_referenceCount == 0)
    {
        delete this;
    }
}

Ref* Ref::autorelease()
{
//    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

NS_STITCHES_END