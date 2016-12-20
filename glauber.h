#ifndef GLAUBER_H
#define GLAUBER_H

#include <iostream>
#include <complex>

#include <QVector>

enum Energy {Energy_1, Energy_2};

using namespace std;

class Glauber
{

public:

    Glauber (void)
    {

    }

    QVector < QVector <double> > Cross_section_calculation (Energy energy, int points);

private:

    double Coulomb(double ksi, double eta,double d_k, double teta)
    {
        double fi_1 = (-2)*ksi*log(sin(teta/2))+2*eta;
        double fi_2_Re = (-2)*ksi*(cos(fi_1))/(4*d_k*pow(sin(teta/2),2));
        double fi_2_Im = (-2)*ksi*(sin(fi_1))/(4*d_k*pow(sin(teta/2),2));
        double Res = (pow(fi_2_Re,2)+pow(fi_2_Im,2))*1000;

        return Res;
    }

    complex<double> Bessel_function(int i,double d_k,double teta, double h_b)
    {
        double var = 2*d_k*(sin(teta/2))*i*h_b;
        double func = _j0(var)*i*h_b;

        return func;
    }
};


#endif // GLAUBER_H
