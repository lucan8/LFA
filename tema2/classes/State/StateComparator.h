#pragma once
#include "State.h"
#include <memory>
struct StateComparator{
    bool operator()(const shared_ptr<State>& s1, const shared_ptr<State>& s2) const{
        return s1->getName() < s2->getName();
    }
};