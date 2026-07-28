#include "cfd/boundaries/PressureInlet.hpp"
#include "cfd/boundaries/PressureOutlet.hpp"
#include "cfd/components/Pipe.hpp"
#include "cfd/components/Valve.hpp"
#include <iostream>
#include <iomanip>

int main() {
    using namespace cfd;

    std::cout << "=== Case 01: Pipe Transient Cooldown Test ===\n\n";

    // 1. 入口・出口境界条件の初期化 (5.0 MPa 液体酸素 / 0.1 MPa 大気解放)
    PressureInlet inlet(5.0e6, 90.0, 1141.0);
    PressureOutlet outlet(0.1e6, 300.0);

    // 2. コンポーネントの生成
    Valve valve(0.005);
    Pipe pipe(10, 2.0, 0.05, 0.003, 300.0); // 10分割, 長さ2m, 内径50mm, 初期壁温300K

    // 3. 配管外気境界条件の選択 (1:空気側温度固定 / 2:指定熱流束 / 3:断熱)
    pipe.setExternalBoundaryIsothermal(300.0);
    // pipe.setExternalBoundaryFixedHeatFlux(500.0);
    // pipe.setExternalBoundaryAdiabatic();

    double dt = 0.001;
    double total_time = 0.5;

    std::cout << "Time [s] | Valve [%] | Mass Flow [kg/s] | Inlet Wall Temp [K]\n";
    std::cout << "---------------------------------------------------------------\n";

    for (double t = 0.0; t <= total_time; t += dt) {
        // バルブ開度制御 (0.1秒で全開)
        double opening = std::min(1.0, t / 0.1);
        valve.setOpening(opening);

        // 各コンポーネントの時間進行
        double m_dot = valve.calculateMassFlow(inlet.getState(), pipe.getCell(0));
        pipe.update(dt);

        if (static_cast<int>(t / dt) % 50 == 0) {
            std::cout << std::fixed << std::setprecision(3)
                    << t << "    | "
                    << std::setprecision(1) << valve.getOpening() * 100.0 << " %   | "
                    << std::setprecision(3) << m_dot << " kg/s    | "
                    << pipe.getWallTemp(0) << " K\n";
        }
    }

    std::cout << "\nSimulation Complete.\n";
    return 0;
}