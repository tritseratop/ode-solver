#ifndef RUNGE_KUTTA4_H
#define RUNGE_KUTTA4_H

#include "../solver/headers/solver_interface.h"
#include <vector>

// Класс решателя
class RK4 : public ISolver {
public:
    RK4() {}
    int solve(const std::vector<double>& input,
              const std::vector<double>& output,
              std::vector<double>& newout,
              std::vector<calcDerivative> funcs,
              SolverParams params);
    std::string getName();
    void release();
};


#endif // RUNGE_KUTTA4_H
