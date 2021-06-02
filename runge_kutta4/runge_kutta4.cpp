#include "runge_kutta4.h"

using namespace std;

extern "C" __declspec(dllexport) ISolver * CreateSolver() {
    return new RK4();
}

int RK4::solve(const vector<double>& input,
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
        vector<double> k1(n), k2(n), k3(n), k4(n);
        for(size_t i = 0; i < n; ++i)
        {
            k1[i] = params.h / 2 * funcs[i](prev_input[i], output[i]);
            k2[i] = params.h / 2 * funcs[i]((prev_input[i] + input[i])/2, output[i] + k1[i]);
            k3[i] = params.h     * funcs[i]((prev_input[i] + input[i])/2, output[i] + k2[i]);
            k4[i] = params.h / 2 * funcs[i](input[i], output[i] + k3[i]);

            newout[i] = output[i] + (k1[i] + 2 * k2[i] + k3[i] + k4[i]) / 3;
        }
        prev_input = input;
        return 1;
    }
}

std::string RK4::getName() {
    return "RK4";
}

void RK4::release() {
    delete this;
}
