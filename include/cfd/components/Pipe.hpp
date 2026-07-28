#pragma once
#include "cfd/components/Component.hpp"
#include "cfd/core/FluidState.hpp"
#include "cfd/core/Types.hpp"
#include <vector>

namespace cfd {

class Pipe : public Component {
private:
    int num_cells_;
    double length_;
    double inner_diameter_;
    double wall_thickness_;

    std::vector<FluidState> cells_;
    std::vector<double> wall_temps_;
    double wall_heat_capacity_ = 500.0; // [J/(kg·K)]

    // 外気境界条件設定
    ExternalBcType ext_bc_type_ = ExternalBcType::Adiabatic;
    double ext_air_temp_ = 300.0;
    double ext_heat_flux_ = 0.0;

public:
    Pipe(int num_cells, double length, double inner_diameter, double wall_thickness, double initial_wall_temp);

    void setExternalBoundaryIsothermal(double air_temp_k);
    void setExternalBoundaryFixedHeatFlux(double flux_w_per_m2);
    void setExternalBoundaryAdiabatic();

    void update(double dt) override;

    int getNumCells() const { return num_cells_; }
    FluidState& getCell(int idx) { return cells_[idx]; }
    const FluidState& getCell(int idx) const { return cells_[idx]; }
    double getWallTemp(int idx) const { return wall_temps_[idx]; }
};

} // namespace cfd