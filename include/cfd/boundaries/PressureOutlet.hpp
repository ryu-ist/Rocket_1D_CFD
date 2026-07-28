#pragma once
#include "cfd/boundaries/Boundary.hpp"

namespace cfd {

class PressureOutlet : public Boundary {
private:
    FluidState state_;

public:
    PressureOutlet(double p_pa, double T_k = 300.0) {
        state_.p = p_pa;
        state_.T = T_k;
        state_.rho = 1.2;
        state_.u = 0.0;
    }

    FluidState getState() const override { return state_; }
    void setPressure(double p_pa) { state_.p = p_pa; }
};

} // namespace cfd