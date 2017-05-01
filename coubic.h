#pragma once
#include <cmath>
#include <vector>
#include <complex>

//Решение кубического уравнения
//На вход подаются коэффицинты (от большей степени к меньшей)
//Возвращается вектор неповторяющихся комплексных корней
std::vector<std::complex<double>> Coubic(double a1, double b1, double c1, double d1);
