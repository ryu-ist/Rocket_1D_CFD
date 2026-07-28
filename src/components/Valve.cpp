#include "cfd/components/Valve.hpp"
#include <algorithm>
#include <cmath>

namespace cfd {

Valve::Valve(double area_max) : area_max_(area_max) {}

void Valve::setOpening(double opening) {
    opening_ = std::clamp(opening, 0.0, 1.0);
}

double Valve::calculateMassFlow(const FluidState& upstream, const FluidState& downstream) const {
    if (opening_ <= 1e-5) return 0.0;

    double dp = upstream.p - downstream.p;
    if (dp <= 0.0) return 0.0; // 逆流防止（簡易）

    double eff_area = getEffectiveArea();
    return eff_area * std::sqrt(2.0 * upstream.rho * dp);
}

} // namespace cfd