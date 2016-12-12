/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      problem_interface.h                                         //
//                                                                         //
//  Purpose:   Header file for ExaMin problem interface                    //
//                                                                         //
//                                                                         //
//  Author(s): Sovrasov V.                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
\file problem_interface.h

\authors Соврасов В.
\date 2016
\copyright ННГУ им. Н.И. Лобачевского

\brief Объявление абстрактного класса #TIProblem

\details Объявление абстрактного класса #TIProblem и сопутствующих типов данных
*/

#ifndef __PROBLEMINTERFACE_H__
#define __PROBLEMINTERFACE_H__

#include <vector>
#include <string>

/**
Базовый класс-интерфейс, от которого наследуются классы, описывающие задачи оптимизации.

В классе #TIProblem описаны прототипы методов, которые должны быть реализованы в подключамых модулях с задачами.
*/
class IProblem
{
  public:

	  /// Код ошибки, возвращаемый, если операция завершена успешно
    static const int OK = 0;
    /** Код ошибки, возвращаемый методами #GetOptimumValue и #GetOptimumPoint,
    если соответствующие параметры задачи не определены,
    */
    static const int UNDEFINED = -1;
    /// Код ошибки, возвращаемый, если операция не выполнена
    static const int ERROR = -2;

    /** Задание пути до конфигурационного файла

    Данный метод должн вызываться перед #Initialize
    \param[in] configPath строка, содержащая путь к конфигурационному файлу задачи
    \return Код ошибки
    */
    virtual int SetConfigPath(const std::string& configPath) = 0;

    /** Метод задаёт размерность задачи

    Данный метод должен вызываться перед #Initialize. Размерность должна быть в
    списке поддерживаемых.
    \param[in] dimension размерность задачи
    \return Код ошибки
    */
    virtual int SetDimension(int dimension) = 0;
    ///Возвращает размерность задачи, можно вызывать после #Initialize
    virtual int GetDimension() const = 0;
    ///Инициализация задачи
    virtual int Initialize() = 0;

    /** Метод возвращает границы области поиска
    */
    virtual void GetBounds(double* lower, double *upper) = 0;
    /** Метод возвращает значение целевой функции в точке глобального минимума
    \param[out] value оптимальное значение
    \return Код ошибки (#OK или #UNDEFINED)
    */
    virtual int GetOptimumValue(double& value) const = 0;
    /** Метод возвращает значение функции с номером index в точке глобального минимума
    \param[out] value оптимальное значение
    \return Код ошибки (#OK или #UNDEFINED)
    */
    virtual int GetOptimumValue(double& value, int index) const 
    {
      return IProblem::UNDEFINED;
    }
    /** Метод возвращает координаты точки глобального минимума целевой функции
    \param[out] y точка, в которой достигается оптимальное значение
    \return Код ошибки (#OK или #UNDEFINED)
    */
    virtual int GetOptimumPoint(double* y) const  = 0;

    /** Метод возвращает число общее функций в задаче (оно равно число ограничений + число критериев)
    \return Число функций
    */
    virtual int GetNumberOfFunctions() const = 0;
    /** Метод возвращает число ограничений в задаче
    \return Число ограничений
    */
    virtual int GetNumberOfConstraints() const = 0;
    /** Метод возвращает число критериев в задаче
    \return Число критериев
    */
    virtual int GetNumberOfCriterions() const = 0;

    /** Метод, вычисляющий функции задачи

    \param[in] y Точка, в которой необходимо вычислить значение
    \param[in] fNumber Номер вычисляемой функции. 0 соответствует первому ограничению,
    #GetNumberOfFunctions() - 1 -- последнему критерию
    \return Значение функции с указанным номером
    */
    virtual double CalculateFunctionals(const double* y, int fNumber) = 0;
    
    ///Деструктор
    virtual ~IProblem() = 0;
};

inline IProblem::~IProblem() {}

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с задачей
typedef IProblem* create_t();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой с задачей
typedef void destroy_t(IProblem*);

///Префикс для фуккций, экспортируемых подключаемой библиотекой с задачей
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif

#endif
// - end of file ----------------------------------------------------------------------------------
