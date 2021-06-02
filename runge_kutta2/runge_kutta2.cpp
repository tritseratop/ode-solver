#include "runge_kutta2.h"

using namespace std;

extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new RK2();
}

int RK2::solve(const vector<double>& input,
               const vector<double>& output,
               vector<double>& newout,
               vector<calcDerivative> funcs,
               SolverParams params) {

    size_t n = newout.size();
    static vector<double> prev_input(n);
    static bool isFirst = 1;

    if(isFirst) {
        prev_input = input;
        isFirst = 0;
        for(size_t i = 0; i < n; ++i)
        {
            newout[i] = output[i] + params.h * funcs[i](input[i], output[i]);
        }
        return 1;
    } else {
        vector<double> dy;
        for(size_t i = 0; i < n; ++i) {
            dy[i] = funcs[i]((prev_input[i] + input[i]) / 2, output[i] + params.h / 2 * funcs[i](input[i], output[i]));
            newout[i] = output[i] + params.h * dy[i];
        }
        prev_input = input;
        return 1;
    }
}

std::string RK2::getName() {
    return "Runge-Kutta 2";
}

void RK2::release() {
    delete this;
}
