#include "euler.h"

extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new Euler();
}

double Euler::solve(const double& x,
                  const double& y,
                  calcDerivative calcDer,
                  SolverParams params) {
    return y + params.h * calcDer(x, y);
}

std::string Euler::getName() {
    return "Euler";
}

void Euler::release() {
    delete this;
}
