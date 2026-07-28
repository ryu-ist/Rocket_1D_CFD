#define _USE_MATH_DEFINES
#include "cfd/components/Pipe.hpp"
#include <cmath>

namespace cfd {

Pipe::Pipe(int num_cells, double length, double inner_diameter, double wall_thickness, double initial_wall_temp)
    : num_cells_(num_cells), length_(length), inner_diameter_(inner_diameter),
      wall_thickness_(wall_thickness), cells_(num_cells),
      wall_temps_(num_cells, initial_wall_temp) {}

void Pipe::setExternalBoundaryIsothermal(double air_temp_k) {
    ext_bc_type_ = ExternalBcType::Isothermal;
    ext_air_temp_ = air_temp_k;
}

void Pipe::setExternalBoundaryFixedHeatFlux(double flux_w_per_m2) {
    ext_bc_type_ = ExternalBcType::FixedHeatFlux;
    ext_heat_flux_ = flux_w_per_m2;
}

void Pipe::setExternalBoundaryAdiabatic() {
    ext_bc_type_ = ExternalBcType::Adiabatic;
}

void Pipe::update(double dt) {
    double dx = length_ / num_cells_;
    double inner_area = M_PI * inner_diameter_ * dx;
    double outer_area = M_PI * (inner_diameter_ + 2.0 * wall_thickness_) * dx;

    for (int i = 0; i < num_cells_; ++i) {
        // 内壁 <-> 流体 熱伝達
        double h_inner = 1000.0; // 簡易熱伝達率 [W/(m^2·K)]
        double q_inner = h_inner * inner_area * (cells_[i].T - wall_temps_[i]);

        // 外壁 <-> 空気 熱伝達
        double q_outer = 0.0;
        switch (ext_bc_type_) {
            case ExternalBcType::Isothermal: {
                double h_air = 15.0;
                q_outer = h_air * outer_area * (ext_air_temp_ - wall_temps_[i]);
                break;
            }
            case ExternalBcType::FixedHeatFlux: {
                q_outer = ext_heat_flux_ * outer_area;
                break;
            }
            case ExternalBcType::Adiabatic: {
                q_outer = 0.0;
                break;
            }
        }

        // 壁温更新
        double net_heat_power = q_inner + q_outer;
        wall_temps_[i] += (net_heat_power / (wall_heat_capacity_ * dx)) * dt;
    }
}

} // namespace cfd