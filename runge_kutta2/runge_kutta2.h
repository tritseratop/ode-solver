#ifndef RK4_H
#define RK4_H

#include "../solver/headers/solver_interface.h"

// Класс решателя
class RK2 : public ISolver {
public:
    RK2() {}
    double solve(const double& x,
                 const double& y,
                 calcDerivative calcDer,
                 SolverParams params);
    std::string getName();
    void release();
};

#endif // RK4_H
