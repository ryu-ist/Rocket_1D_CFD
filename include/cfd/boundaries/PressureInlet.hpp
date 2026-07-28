#pragma once
#include "cfd/boundaries/Boundary.hpp"

namespace cfd {

class PressureInlet : public Boundary {
private:
    FluidState state_;

public:
    PressureInlet(double p_pa, double T_k, double rho_kg_m3, double Y_vapor = 0.0) {
        state_.p = p_pa;
        state_.T = T_k;
        state_.rho = rho_kg_m3;
        state_.Y = Y_vapor;
        state_.u = 0.0;
    }

    FluidState getState() const override { return state_; }
    void setPressure(double p_pa) { state_.p = p_pa; }
    void setTemperature(double T_k) { state_.T = T_k; }
};

} // namespace cfd