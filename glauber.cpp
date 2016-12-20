#include "glauber.h"


QVector < QVector <double> > Glauber::Cross_section_calculation (Energy energy, int points)
{
    QVector <double> Theta(0);
    QVector <double> Coulomb(0);
    QVector <double> Cross_section1(0);
    QVector <double> Cross_section2(0);

    double theta, d_scattering, beta, eta, p, d_k, ksi, a = 0.00001, dT;

    int b = 10;
    int n = 1000;

    int const A=12;
    double alfa = sqrt(0.025);
    double Ampl_F1, Ampl_F2;
    int j, i, k;

    switch (energy)
    {
    case Energy_1://47 Mev
        d_scattering = 0.22;
        beta = sqrt(0.014);
        dT = 47./19.7;
        p = 0.0;
        d_k = 14.464;
        ksi = -0.142576;
        eta = 0.081148;
        break;

    case Energy_2://180 Mev
        d_scattering = 0.1465;
        p = 0.2;
        beta = sqrt(0.0086);
        dT = 180/19.7;
        d_k = 29.467;
        ksi = -0.070843;
        eta = 0.0407496;
        break;

    default:
        break;
    }
    //END

    complex<double>  sumII2 = (0.0,0.0);
    complex<double>  sumII1 = (0.0,0.0);
    complex<double>  sumI1  = (0.0,0.0);
    complex<double>  sumI2  = (0.0,0.0);

    double h_b = (b-a)/(float)n;

    for (int j = 1; j < points + 1; j++)
    {
        theta = j*M_PI/180;

        for (i = 1; i < n-1; i++)
        {
            //Xi_N
            double R = sqrt(2*beta*beta + alfa*alfa);
            double XiN_Real = ((d_scattering*p)/(2*M_PI*R*R))*(A - (2/3.)*(A-4)*(1-h_b*h_b*i*i/pow(R,2))*pow(alfa,2)/pow(R,2))*exp((-1)*h_b*h_b*i*i/pow(R,2));
            double XiN_Imaginary = (d_scattering/(2*M_PI*R*R))*(A - (2/3.)*(A-4)*(1-h_b*h_b*i*i/pow(R,2))*pow(alfa,2)/pow(R,2))*exp((-1)*h_b*h_b*i*i/pow(R,2));

            //Xi_1
            double D;
            double Sum_r = 0;
            double x;
            double Xi1;

            for (k = 1; k < n; k++)
            {
                x = k*(h_b+a);

                if ( x >= ( (h_b+a)*i ) )
                {
                    D = log((1+sqrt(1-pow((h_b*i),2)/pow(x,2)))/(i*h_b/x))-sqrt(1-pow((h_b*i),2)/pow(x,2));
                    Xi1 =8*M_PI*ksi*pow(x,2)*exp(-pow((x/alfa),2))*(4+(2/3.)*(A-4)*pow((x/alfa),2))/(A*pow(M_PI,1.5)*pow(alfa,3))*D;
                }
                else
                    Xi1 = 0;

                Sum_r = Sum_r + Xi1*(h_b+a);
            }

            //I1 integral
            complex<double> funcI1 = Bessel_function(i,d_k,theta,h_b)*exp(complex<double>(0.0,2*ksi*log(d_k*i*h_b)));
            sumI1 = funcI1+sumI1;

            //I2 integral
            complex<double> funcI2 = Bessel_function(i,d_k,theta,h_b)*exp(complex<double>(0.0,Sum_r))*exp(complex<double>(-XiN_Imaginary,XiN_Real))*exp(complex<double>(0.0,2*ksi*log(d_k*i*h_b)));
            sumI2 = funcI2+sumI2;

            //II1 integral
            complex<double> funcII1 = Bessel_function(i,d_k,theta,h_b)*exp(complex<double>(0.0,0.0));
            sumII1 = funcII1+sumII1;

            //II2 integral
            complex<double>  funcII2 = exp(complex<double>(-XiN_Imaginary,XiN_Real))*Bessel_function(i,d_k,theta,h_b);
            sumII2 =funcII2+sumII2;
            //II2 integral END
        }

        sumI1  = sumI1*h_b;
        sumI2  = sumI2*h_b;
        sumII1 = sumII1*h_b;
        sumII2 = sumII2*h_b;

        double pow_H = 2*d_k*d_k*(sin(theta/2))*(sin(theta/2))*0.025/A;
        double Xi_s = -2*ksi*log(2*d_k*alfa/0.577215664901532);
        double fi_1 = (-2)*ksi*log(sin(theta/2))+2*eta;

        complex<double> coulomb = (-2)*ksi*exp(complex<double>(0.0, fi_1))/(4*d_k*pow(sin(theta/2),2));
        double Ampl_Coul = (real(coulomb)*real(coulomb)+imag(coulomb)*imag(coulomb))*1000;

        complex<double> F1 = (coulomb+d_k*(sumI1-sumI2)*(complex<double>(0.0,1)))*exp(complex<double>(0.0, Xi_s));
        Ampl_F1 = (real(F1)*real(F1)+imag(F1)*imag(F1))*exp(pow_H)*1000;

        complex<double> F2 = (sumII1-sumII2)*d_k*exp(complex<double>(0.0, Xi_s))*(complex<double>(0.0,1.0));
        Ampl_F2 = (real(F2)*real(F2)+imag(F2)*imag(F2))*exp(pow_H)*1000;


        Theta.push_back(theta*(180/M_PI));
        Cross_section1.push_back(Ampl_F1);
        Cross_section2.push_back(Ampl_F2);
        Coulomb.push_back(Ampl_Coul);
    }

    QVector < QVector <double> > Result(0);

    Result.push_back(Theta);
    Result.push_back(Coulomb);
    Result.push_back(Cross_section1);
    Result.push_back(Cross_section2);

    return Result;
}
