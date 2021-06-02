#include "solver_module.h"
#include "solver_connector.h"
#include "print_tools.h"
#include "schema.h"

#include <math.h>

using namespace std;

double DerFun1(const double& x, const double& y){
    return 3 * sin(2 * y) + x;
}

void GenerateX(SolverParams params, vector<double>& X, double init_v) {
    X[0] = init_v;
    for (int i = 1; i < static_cast<int>(X.size()); ++i) {
        X[i] = X[0] + params.h * i;
    }
}

int main()
{
    const int n = 15;
    vector<double> X(n);
    SolverParams param;
    GenerateX(param, X, 0);

    SolverConnector sc;
    sc.connectTestFunction();
    vector<string> dll_names = sc.addAllAvailableSolvers();

    SolverModule sm;
    sm.setSolver(sc.getUserSolver(dll_names[0]));
    vector<double> source = ConstSource(1, 0.1, 10);
    vector<double> output(source.size()), newout(source.size());
    output[0] = 0;
    SolverParams params;
    params.h = 0.1;
    for(size_t i = 0; i < source.size(); ++i) {
        sm.solve(source[i], output[i], newout[i], Inertial, params);
        if (i != source.size() - 1) {
            output[i+1] = newout[i];
        }
    }

    cout << newout << endl;

//    bool end = 0;
//    while(!end) {
//        cout << "Existed DLL:\n";
//        vector<string> dll_names = sc.getAvailableSolverDllNames();
//        PrintNames(dll_names);
//        cout << "Enter the solver dll-module number you need: ";
//        int dll_number;
//        cin >> dll_number;

//        sc.addNewSolver(dll_names[dll_number - 1]);
//        vector<string> user_solver_names = sc.getUserSolversNames();
//        PrintNames(user_solver_names);
//        cout << "Enter the solver number you need: ";
//        int solv_number;
//        cin >> solv_number;

//        vector<DER_VALUES> Y1 = sm.solveSchema(sc.getUserSolver(user_solver_names[solv_number - 1]), X, DerFun1, param.h);
//        cout << "X:  " << X << endl;
//        cout << "Y1: " << Y1 << endl;

//        cout << "Enter 1 to complete: ";
//        cin >> end;
//    }

    return 0;
}



