#include <iostream>
#include "bezcoord.h"

using namespace std;

BezierCoords2D * BezierCoords2D::FindAlpha(int sizeX, int sizeZ, double xt, double zt)
{
    //dlx - нормаль к плоскости, примыкающей к телу, dlz - к руке
    double dlx = NORM_COEF*xt, dlz = NORM_COEF*zt;
    double alphaResult = ALPHA_MIN;
    double minDelta = 100;
    double txRes = -1, tzRes = -1;
    for (double alpha = ALPHA_MIN; alpha <= ALPHA_MAX; alpha += ALPHA_STEP)
    {
        double ax = -3*dlx + 2*alpha*sizeX,
                bx = 3*dlx - 3*alpha*sizeX,
                cx = 0,
                dx = alpha*sizeX-xt;
        double az = -2*alpha*sizeZ +3*dlz,
                bz = 3*alpha*sizeZ-6*dlz,
                cz = 3*dlz,
                dz = -zt;
        auto tx = Coubic(ax,bx,cx,dx),
                tz = Coubic(az,bz,cz,dz);
        double min = 100;
        double txTemp=0, tzTemp=0;
        for (auto const valx : tx)
        {
            for (auto const valz : tz)
            {
                if (imag(valx) == 0 && imag(valz) == 0)
                {
                   double rtx = real(valx), rtz = real(valz);
                   if (rtx >= 0 && rtx <= 1 && rtz >= 0 && rtz <=1 &&
                           fabs(rtx-rtz) < min)
                   {
                       min = fabs(rtx-rtz);
                       txTemp = rtx;
                       tzTemp = rtz;
                   }
                }
            }
        }
        if (min < minDelta)
        {
            minDelta = min;
            txRes = txTemp;
            tzRes = tzTemp;
            alphaResult = alpha;
        }
    }
    BezierCoords2D * result = new BezierCoords2D(alphaResult, txRes, tzRes);
    return result;
}
