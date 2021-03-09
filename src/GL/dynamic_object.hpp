#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject
{
protected :
    bool _dead = false;

public:
    DynamicObject() { }

    virtual ~DynamicObject() { }

    virtual void move(int64_t dt) = 0;

    bool is_dead() 
    {
        return _dead;
    }
};

inline std::unordered_set<DynamicObject*> move_queue;

} // namespace GL
