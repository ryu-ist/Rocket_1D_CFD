#pragma once

namespace cfd {

class Component {
public:
    virtual ~Component() = default;
    virtual void update(double dt) = 0;
};

} // namespace cfd