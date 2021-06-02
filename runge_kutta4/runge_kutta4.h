#ifndef RUNGE_KUTTA4_H
#define RUNGE_KUTTA4_H

#include "../solver/headers/solver_interface.h"

// Класс решателя
class RK4 : public ISolver {
public:
    RK4() {}
    double solve(const double& x,
                 const double& y,
                 calcDerivative calcDer,
                 SolverParams params);
    std::string getName();
    void release();
};


#endif // RUNGE_KUTTA4_H
