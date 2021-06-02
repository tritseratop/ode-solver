#ifndef EULER_H
#define EULER_H

#include "../solver/headers/solver_interface.h"
#include <vector>

// Класс решателя
class Euler : public ISolver {
public:
    Euler() {}
    int solve(const std::vector<double>& input,
              const std::vector<double>& output,
              std::vector<double>& newout,
              std::vector<calcDerivative> funcs,
              SolverParams params);
    std::string getName();
    void release();
};

#endif // EULER_H
