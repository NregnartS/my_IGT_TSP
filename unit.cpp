#include "unit.h"

Unit::Unit()
    :path(0)
{
}

Unit::Unit(const std::vector<int>& tp)
    :path(0)
{
    this->path=tp;
}
