#pragma once

#include <cmath>
#include <vector>
#include <complex>
#include <functional>
#include "newt.h"
#include "coubic.h"

double constexpr ALPHA_MIN = -0.1;
double constexpr ALPHA_MAX = 3.0;
double constexpr ALPHA_STEP = 0.001;
double constexpr NORM_COEF = 2.0/3.0;

class BezierCoords2D
{
public:
    BezierCoords2D(): m_alpha{ALPHA_MIN}, m_tx{-1.0}, m_tz{-1.0}
    {}

    BezierCoords2D(double a,double x,double z): m_alpha{a}, m_tx{x}, m_tz{z}
    {}

    ~BezierCoords2D()
    {}

    static BezierCoords2D * FindAlpha(int sizeX, int sizeZ, double xt, double zt);

    double const & alpha() const { return m_alpha; }
    double const & tx() const { return m_tx; }
    double const & tz() const { return m_tz; }
    double t() const { return (m_tx + m_tz)/2; }

private:
    double m_alpha;
    double m_tx;
    double m_tz;
};

class DecCoords2D
{
public:
    DecCoords2D(double x, double z): m_x{x}, m_z{z}
    {}

    ~DecCoords2D()
    {}

    double x() { return m_x; }
    double z() { return m_z; }

private:
    double m_x;
    double m_z;
};

DecCoords2D * FindPoint(double alpha, double t, int sizeX, int sizeZ);
