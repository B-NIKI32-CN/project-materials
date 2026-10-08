#include "Headers/heat_dissipation.h"

// коэффициент потери скорости 
// название выбрано по аналогии затухающего колебательного движения 
double invBetta {2}; // имеет смысл за какое время скорость уменьшится в e раз

double betta {1/invBetta};   //коэффициент в дифференциальном уравнении скорости -- коэффициент зытухания в соответствующем колебании

void heat_dissipation(double* velocity, const double* delta_time)
{
    *velocity = *velocity * (1 - betta * *delta_time);
}

