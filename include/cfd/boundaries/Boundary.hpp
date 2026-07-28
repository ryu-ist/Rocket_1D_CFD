#pragma once
#include "cfd/core/FluidState.hpp"

namespace cfd {

class Boundary {
public:
    virtual ~Boundary() = default;
    virtual FluidState getState() const = 0;
};

} // namespace cfd