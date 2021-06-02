#ifndef EULER_H
#define EULER_H

#include "../solver/headers/solver_interface.h"

// Класс решателя
class Euler : public ISolver {
public:
    Euler() {}
    double solve(const double& x,
                 const double& y,
                 calcDerivative calcDer,
                 SolverParams params);
    std::string getName();
    void release();
};

#endif // EULER_H
