#include <cmath>

float E1 = -12;
float E2 = 8;
float r1 = 30;
float r2 = 50;
float r3 = 60;

float a1 = 4*E1*r1 / (r2 - r1);
float b1 = -4*E1*std::pow(r1, 2) / (r2 - r1);

float a2 = -4*E1 / std::pow((r2 - r1), 2);
float b2 = 4*E1*(r1+r2) / std::pow((r2 - r1), 2);
float c2 = -4*E1*r1*r2 / std::pow((r2 - r1), 2);

float a3 = -4*std::pow(E1, 2) / E2 / std::pow((r2 - r1), 2);
float b3 = 8*std::pow(E1, 2)*r2 / E2 / std::pow((r2 - r1), 2) - 4*E1 / (r2 - r1);
float c3 = -( (4 * std::pow(E1, 2) * std::pow(r2, 2)) / (E2 * std::pow((r2 - r1), 2)) ) + ( (4 * E1 * r2) / (r2 - r1) );

float A = a3 * r3 ** 2 + b3 * r3 + c3;
float B = 2 * a3 * r3 + b3;

float a4 = A / B + r3;
float b4 = A * (r3 - a4);


float SimpleForse(float r)
{
    if(r < r1)
    {
        return -b1 / std::pow(r, 2);
    }
    else if(r < r2)
    {
        return 2 * a2 * r + b2;
    }
    else if(r<r3)
    {
        return 2 * a3 * r  + b3;
    }
    else
    {
        return -b4 / std::pow((r - a4), 2);
    }
}