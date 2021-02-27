#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject;

inline std::unordered_set<DynamicObject*> move_queue;

class DynamicObject
{
protected :
    bool _dead = false;

public:
    DynamicObject() { move_queue.emplace(this); }

    virtual ~DynamicObject() { move_queue.erase(this); }

    virtual void move(int64_t dt) = 0;

    bool is_dead() 
    {
        return _dead;
    }
};



} // namespace GL
