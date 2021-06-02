#include "runge_kutta2.h"


extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new RK2();
}

double RK2::solve(const double& x,
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
        double dy;
        dy = calcDer((prev_x + x) / 2, y + params.h / 2 * calcDer(x, y));
        prev_x = x;
        return y + params.h * dy;
    }
}

std::string RK2::getName() {
    return "Runge-Kutta 2";
}

void RK2::release() {
    delete this;
}
