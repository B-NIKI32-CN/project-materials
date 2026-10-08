#include "Headers/forse.h"
#include <cmath>




// double E1 = -10; // кучкование
// double E2 = 10;
// double r1 = 20;
// double r2 = 60;
// double r3 = 90;


// double E1 = -10; // кучкование
// double E2 = 20;
// double r1 = 20;
// double r2 = 60;
// double r3 = 120;

// double E1 = -20; // кучкование
// double E2 = 10;
// double r1 = 20;
// double r2 = 60;
// double r3 = 75;


// double E1 = -10; // кучкование
// double E2 = 10;
// double r1 = 20;
// double r2 = 40;
// double r3 = 55;

// double E1 = -12; // кучкование
// double E2 = 8;
// double r1 = 20;
// double r2 = 60;
// double r3 = 55;

// double E1 = -12; // классика  -  гексагональная решетка
// double E2 = 8;
// double r1 = 30;
// double r2 = 50;
// double r3 = 60;

// double E1 = -50; // гексагональная решетка
// double E2 = 50;
// double r1 = 50;
// double r2 = 70;
// double r3 = 85;


double E1 = -100; // гексагональная решетка -сокращаю радиусы
double E2 = 100;
double r1 = 10;
double r2 = 15;
double r3 = 19;

double bondRange {(r1+r2) / 2};

double a1 = 4*E1*r1 / (r2 - r1);
double b1 = -4*E1*std::pow(r1, 2) / (r2 - r1);

double a2 = -4*E1 / std::pow((r2 - r1), 2);
double b2 = 4*E1*(r1+r2) / std::pow((r2 - r1), 2);
double c2 = -4*E1*r1*r2 / std::pow((r2 - r1), 2);

double a3 = -4*std::pow(E1, 2) / E2 / std::pow((r2 - r1), 2);
double b3 = 8*std::pow(E1, 2)*r2 / E2 / std::pow((r2 - r1), 2) - 4*E1 / (r2 - r1);
double c3 = -( (4 * std::pow(E1, 2) * std::pow(r2, 2)) / (E2 * std::pow((r2 - r1), 2)) ) + ( (4 * E1 * r2) / (r2 - r1) );

double A = a3 * std::pow(r3, 2) + b3 * r3 + c3;
double B = 2 * a3 * r3 + b3;

double a4 = A / B + r3;
double b4 = A * (r3 - a4);


double SimpleForse(double r)
{
    if(r < r1)
    {
        return -b1 / std::pow(r, 2);
    }
    else if(r < r2)
    {
        return 2 * a2 * r + b2;
    }
    else if(r < r3)
    {
        return 2 * a3 * r  + b3;
    }
    else
    {
        return -b4 / std::pow((r - a4), 2);
    }
}