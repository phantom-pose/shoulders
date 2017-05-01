#include "coubic.h"

using namespace std;

int sgn(double val) { return (val < 0 ? -1 : !!val); }

vector<complex<double>> Coubic(double a1, double b1, double c1, double d1)
{
    double a = b1/a1;
    double b = c1/a1;
    double c = d1/a1;
    double q = (a*a-3*b)/9;
    double r=(2*a*a*a-9*a*b+27*c)/54;
    double s = q*q*q - r*r;
    vector<complex<double>> x;
    x.reserve(3);
    if (s > 0)
    {
        double phi = acos(r/sqrt(q*q*q))/3;
        x.push_back( -2*sqrt(q)*cos(phi) - a/3 );
        x.push_back( -2*sqrt(q)*cos(phi+2./3*M_PI) - a/3 );
        x.push_back( -2*sqrt(q)*cos(phi-2./3*M_PI) - a/3 );
    }
    else if (s == 0)
    {
        x.push_back( -2*cbrt(r) - a/3 );
        if (cbrt(r) - a/3 != x[0]) {
            x.push_back( cbrt(r) - a/3 );
        }
    }
    else if (q > 0)
    {
        double phi = 1/3.0 * acosh(fabs(r)/sqrt(q*q*q));
        x.push_back( -2*sgn(r)*sqrt(q)*cosh(phi)-a/3 );
        x.push_back( sgn(r)*sqrt(q) - a/3 + sqrt(3*q)*sinh(phi)*1i );
        x.push_back( sgn(r)*sqrt(q) - a/3 - sqrt(3*q)*sinh(phi)*1i );
    }
    else if (q == 0) {
        double re = -cbrt(c-a*a*a/27) - a/3;
        x.push_back( re );
        x.push_back( -(a+re)/2 + sqrt(fabs( (a-3*re)*(a+re) - 4*b ))/2 * 1i );
        x.push_back( -(a+re)/2 - sqrt(fabs( (a-3*re)*(a+re) - 4*b ))/2 * 1i );
    }
    else
    {
        double phi = 1/3.0 * asinh(fabs(r)/sqrt(fabs(q*q*q)));
        x.push_back( -2*sgn(r)*sqrt(fabs(q))*sinh(phi)-a/3 );
        x.push_back( sgn(r)*sqrt(fabs(q)) - a/3 + sqrt(3*fabs(q))*cosh(phi)*1i );
        x.push_back( sgn(r)*sqrt(fabs(q)) - a/3 - sqrt(3*fabs(q))*cosh(phi)*1i );
    }
    return x;
}
