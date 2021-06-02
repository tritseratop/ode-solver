#include "runge_kutta4.h"

extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new RK4();
}

double RK4::solve(const double& x,
                  const double& y,
                  calcDerivative calcDer,
                  SolverParams params) {

    static double prev_x;
    static bool isFirst = 1;

    if(isFirst) {
        prev_x = x;
        isFirst = 0;
        return y + params.h * calcDer(x, y);
    } else {
        double k1, k2, k3, k4;
        k1 = params.h / 2 * calcDer(prev_x, y);
        k2 = params.h / 2 * calcDer((prev_x + x)/2, y + k1);
        k3 = params.h     * calcDer((prev_x + x)/2, y + k2);
        k4 = params.h / 2 * calcDer(x, y + k3);

        prev_x = x;
        return y + (k1 + 2 * k2 + k3 + k4) / 3;
    }

}

std::string RK4::getName() {
    return "RK4";
}

void RK4::release() {
    delete this;
}
