#ifndef SOLVER_MODULE
#define SOLVER_MODULE
#include "solver_interface.h"

#include <vector>
#include <map>
#include <set>
#include <windows.h>

using pDerFun = double (*)(const double&, const double&);
using DER_VALUES = std::vector<double>;

class SolverModule {
public:
    int solve(const double& x, const double& y, double& result, calcDerivative f, SolverParams p);
    int solveSystem(const std::vector<double>& input,
                    const std::vector<double>& output,
                    std::vector<double>& newout,
                    std::vector<calcDerivative> funcs,
                    SolverParams params);
    void setSolver(ISolver* solver);
    SolverModule();
    SolverModule(ISolver* solver);
    ~SolverModule();

private:
    ISolver* current_solver;
};

#endif // SOLVER_MODULE

