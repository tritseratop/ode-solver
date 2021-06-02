#ifndef RK4_H
#define RK4_H

#include "../solver/headers/solver_interface.h"
#include <vector>

// Класс решателя
class RK2 : public ISolver {
public:
    RK2() {}
    int solve(const std::vector<double>& input,
              const std::vector<double>& output,
              std::vector<double>& newout,
              std::vector<calcDerivative> funcs,
              SolverParams params);
    std::string getName();
    void release();
};

#endif // RK4_H
