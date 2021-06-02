#include "solver_connector.h"

#include <boost/filesystem/operations.hpp>
#include <iostream>

using namespace std;
namespace fs = boost::filesystem;

ISolver* SolverConnector::getUserSolver(const std::string& solver_name) {
    if (user_solvers.count(solver_name) == 0) {
        cout << "There are no " + solver_name + " solver in base/n";
        return nullptr;
    } else {
        return user_solvers.at(solver_name);
    }
}

vector<string> SolverConnector::getUserSolversNames() {
    vector<string> names;
    for (const auto& name : user_solvers) {
        names.push_back(name.first);
    }
    return names;
}

LPCWSTR str2pwchar_t(string str) {
    return std::wstring(str.begin(), str.end()).c_str();
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

string SolverConnector::addNewSolver(const string& dll_name)
{
    HMODULE hlib = LoadLibrary(s2ws(dll_name).c_str());
    string solver_name;
    if (hlib == NULL)
    {
     cout << "Library loading error\n";
     return nullptr;
    }
    else
    {
     cout << "Library loaded successfully\n";
     SOLVER CreateSolver = (SOLVER)GetProcAddress(hlib, "CreateSolver");
     if (CreateSolver == NULL)
     {
         cout << "Function loading error\n";
         return nullptr;
     }
     else
     {
         ISolver* pSolver = CreateSolver();
         solver_name = pSolver->getName();
         cout << solver_name << " function loaded successfully\n";
         user_solvers[solver_name] = pSolver;
     }
    }
    FreeLibrary(hlib);
    return solver_name;
 }

vector<string> SolverConnector::getAvailableDllNames() {
    vector<fs::path> file_names;
    fs::directory_iterator begin(solvers_dir);
    fs::directory_iterator end;
    for (; begin != end; ++begin) {
        file_names.emplace_back(*begin);
    }
    vector<string> dll_names;
    for (const auto& name : file_names) {
        if (name.extension().string() == ".dll") {
            dll_names.push_back(name.filename().string());
        }
    }
    return dll_names;
}

vector<string> SolverConnector::addAllAvailableSolvers()
{
    fs::directory_iterator begin(solvers_dir);
    fs::directory_iterator end;
    vector<string> dll_names;
    for (; begin != end; ++ begin)
    {
        if ((*begin).path().extension().string() == ".dll")
        {
            //string k = "G:/knowledge/UIRS/TESTS/target/RK4.dll";
            //HMODULE hlib = LoadLibrary(str2pwchar_t((*begin).path().string()));
            HMODULE hlib = LoadLibrary(s2ws((*begin).path().string()).c_str());
            //DWORD x = GetLastError();
            if (hlib == NULL)
            {
                cout << "Failed to load " + (*begin).path().string() + "\n";
            }
            else
            {
                SOLVER CreateSolver = (SOLVER)GetProcAddress(hlib, "CreateSolver");
                if (CreateSolver == NULL) {
                    cout << "Failed to load function CreateSolver() from " + (*begin).path().string() + "\n";
                } else {
                    cout << "Function from " + (*begin).path().string() + " loaded successfully\n";
                    ISolver* pSolver = CreateSolver();
                    user_solvers[pSolver->getName()] = pSolver;
                    dll_names.push_back(pSolver->getName());
                }
                //FreeLibrary(hlib);
            }
        }
    }
    return dll_names;
}

SolverConnector::SolverConnector() {}

SolverConnector::SolverConnector(const std::string& dir) {
    solvers_dir = dir;
}

SolverConnector::~SolverConnector() {
    for(auto& s : user_solvers) {
        s.second->release();
    }
}

void SolverConnector::connectTestFunction() {
    using func =  void (*)();
    HMODULE hlib = LoadLibrary(L"G:/knowledge/UIRS/TESTS/Euler/build-client-Desktop_Qt_5_5_1_MinGW_32bit-Debug/debug/libshared_lib.dll");
    if (hlib != NULL) {
        func testFunc = (func)GetProcAddress(hlib, "func");
        if (testFunc != NULL) {
            testFunc();
        }
    } else {
        std::cout << "no :( \n";
    }
}
