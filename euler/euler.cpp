#include "euler.h"

using namespace std;

extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new Euler();
}

int Euler::solve(const vector<double>& input,
               const vector<double>& output,
               vector<double>& newout,
               vector<calcDerivative> funcs,
               SolverParams params) {
    for(size_t i = 0; i < newout.size(); ++i)
    {
         newout[i] = output[i] + params.h * funcs[i](input[i], output[i]);
    }
    return 1;
}

std::string Euler::getName() {
    return "Euler";
}

void Euler::release() {
    delete this;
}
