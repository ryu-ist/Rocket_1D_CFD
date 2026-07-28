#pragma once
#include "cfd/components/Component.hpp"
#include "cfd/core/FluidState.hpp"

namespace cfd {

class Valve : public Component {
private:
    double area_max_;
    double opening_ = 0.0; // 0.0(全閉) ~ 1.0(全開)

public:
    explicit Valve(double area_max);

    void setOpening(double opening);
    double getOpening() const { return opening_; }
    double getEffectiveArea() const { return area_max_ * opening_; }

    // 前後の流体状態から質量流量 [kg/s] を計算
    double calculateMassFlow(const FluidState& upstream, const FluidState& downstream) const;

    void update(double dt) override {}
};

} // namespace cfd