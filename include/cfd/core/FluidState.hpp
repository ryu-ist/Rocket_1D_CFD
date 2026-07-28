#pragma once

namespace cfd {

struct FluidState {
    double p = 101325.0;  // 圧力 [Pa]
    double T = 300.0;     // 温度 [K]
    double u = 0.0;       // 流速 [m/s]
    double rho = 1.2;     // 密度 [kg/m^3]
    double Y = 0.0;       // 気相質量分率 (0.0:完全液体 〜 1.0:完全気体)
};

} // namespace cfd