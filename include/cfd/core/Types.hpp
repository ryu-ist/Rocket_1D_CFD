#pragma once

namespace cfd {

// 配管の外気側（空気側）熱境界条件の種別
enum class ExternalBcType {
    Isothermal,    // 1. 空気側温度固定
    FixedHeatFlux, // 2. 空気側熱流束指定
    Adiabatic      // 3. 空気側断熱
};

} // namespace cfd