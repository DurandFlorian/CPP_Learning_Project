#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject
{
protected:
    bool dead = false;

public:
    DynamicObject() {}

    virtual ~DynamicObject() {}

    virtual void move(const float dt) = 0;

    bool is_dead() const { return dead; }
};

inline std::unordered_set<DynamicObject*> move_queue;

} // namespace GL
