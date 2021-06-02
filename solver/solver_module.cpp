#include "solver_module.h"

#include <iostream>

using namespace std;

int SolverModule::solve(const double& x, const double& y, double& result, calcDerivative f, SolverParams p) {
    if (current_solver != nullptr) {
        result = current_solver->solve(x, y, f, p);
        return 1;
    }
    // Явный метод Эйлера
    else {
        result = y + p.h * f(x, y);
        return 1;
    }
}

int SolverModule::solveSystem(const vector<double>& input,
                              const vector<double>& output,
                              vector<double>& newout,
                              vector<calcDerivative> funcs,
                              SolverParams params) {
    if (current_solver != nullptr) {
        for (size_t i = 0; i < funcs.size(); ++i) {
            newout[i] = current_solver->solve(input[i], output[i], funcs[i], params);
        }
        return 1;
    }
    // Явный метод Эйлера
    else {
        for (size_t i = 0; i < funcs.size(); ++i) {
            newout[i] = output[i] + params.h * funcs[i](input[i], output[i]);
        }
        return 1;
    }
}

void SolverModule::setSolver(ISolver* solver) {
    current_solver = solver;
}

SolverModule::SolverModule(ISolver* solver) {
    current_solver = solver;
}

SolverModule::SolverModule() {}

SolverModule::~SolverModule() {}
