#include "bezcoord.h"

using namespace std;

DecCoords2D * FindPoint(double alpha, double t, int sizeX, int sizeZ, double xt, double zt)
{
    //dlx - нормаль к плоскости, примыкающей к телу, dlz - к руке
    double dlx = NORM_COEF*xt, dlz = NORM_COEF*zt;
    double x1 = alpha*sizeX,
            x2 = alpha*sizeX,
            x3 = dlx,
            x4 = 0;
    double z1 = 0,
            z2 = dlz,
            z3 = alpha*sizeZ,
            z4 = alpha*sizeZ;
    DecCoords2D * point = new DecCoords2D(x1*(1-t)*(1-t)*(1-t) + 3*x2*(1-t)*(1-t)*t + 3*x3*(1-t)*t*t + x4*t*t*t,
                                          z1*(1-t)*(1-t)*(1-t) + 3*z2*(1-t)*(1-t)*t + 3*z3*(1-t)*t*t + z4*t*t*t);
    return point;
}

void f1(float * x, int n, float * fvec, float ** fjac, float xt, float zt, float sizeX, float sizeZ)
{
    double dlx = NORM_COEF*xt, dlz = NORM_COEF*zt;
    float a = x[0];
    float t = x[1];
    fvec[0] = t*t*t*(2*a*sizeX - 3*dlx) + t*t*(-3*a*sizeX + 3*dlx) + a*sizeX - xt;
    fvec[1] = t*t*t*(3*dlz - 2*a*sizeZ) + t*t*(-6*dlz + 3*a*sizeZ) +3*t*dlz - zt;
    fjac[0][0] = 2*t*t*t*sizeX -3*t*t*sizeX + sizeX;
    fjac[0][1] = 3*t*t*(2*a*sizeX - 3*dlx) + 2*t*(-3*a*sizeX + 3*dlx);
    fjac[1][0] = -2*t*t*t*sizeZ + 3*t*t*sizeZ;
    fjac[1][1] = 3*t*t*(3*dlz - 2*a*sizeZ) + 2*t*(-6*dlz + 3*a*sizeZ) +3*dlz;
}

BezierCoords2D * BezierCoords2D::FindAlpha(int sizeX, int sizeZ, double xt, double zt)
{
    float amax = (sizeX*zt/sizeZ + xt)/sizeX;
    float amin = xt/sizeX > zt/sizeZ ? xt/sizeX : zt/sizeZ;
    float a = (amin+amax)/2;
    float t = (zt/sizeZ)/(xt/sizeX+zt/sizeZ);
    float * x = new float[2];
    std::function<void(float * , int , float * , float ** )> func = [xt,zt,sizeX,sizeZ](float * x, int n, float * fvec, float ** fjac){ f1(x,n,fvec,fjac,xt,zt, sizeX, sizeZ); };
    x[0] = a;
    x[1] = t;
    mnewt(func, x, 100, 2);
    BezierCoords2D * result = new BezierCoords2D(x[0], x[1], x[1]);
    return result;
}
