#ifndef SOLVER_INTERFACE
#define SOLVER_INTERFACE

#include <functional>
#include <vector>
#include <string>

/**
 * Тип для указателя на функцию, которая возвращает значение производной
 */
using calcDerivative = std::function<double(const double&, const double&)>;


// Сделать дефайны для расширения решателей
//template<class T>
struct SolverParams
{
    double h;
    double e;
    std::vector<double> otherParams;
    //std::vector<T> otherParams;
};

/**
 * @brief The ISolver class
 * Предоставляет интерфейс для решателей
 */
class ISolver
{
public:
    virtual ~ISolver() { ; }
    /**
     * @brief solve Решает дифференциальное уравнение
     * @param x Входной параметр
     * @param y Значение функции
     * @param calcDer Функция, вычисляющая dy/dt (диф. уравнение)
     * @param params Параметры решателя
     * @return Возвращает решение диф. уравнения calcDer
     */
    virtual int solve(const std::vector<double>& input,
                      const std::vector<double>& output,
                      std::vector<double>& newout,
                      std::vector<calcDerivative> funcs,
                      SolverParams params) = 0;
    /**
     * @brief getName
     * @return Имя решателя
     */
    virtual std::string getName() = 0;
    /**
     * @brief release Вызывает деструктор
     */
    virtual void release() = 0;
};

// Factory function that will return the new object instance
// (ONLY FUNCTION SHOULD BE DECLARED WITH DLLCALL)
extern "C" __declspec(dllexport) ISolver * CreateSolver();

typedef ISolver* (*SOLVER) ();

#endif // SOLVER_INTERFACE
