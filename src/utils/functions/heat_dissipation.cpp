#include "Headers/heat_dissipation.h"

// коэффициент потери скорости 
// название выбрано по аналогии затухающего колебательного движения 
double betta {0.5};    // размерность 1/с 
                    // имеет физический смысл - какая доля скорости потеряется за 1/e секунд времени (могу ошибаться в точном времени)

double heat_dissipation(double velocity, double delta_time)
{
    return velocity * (1 - betta * delta_time);
}

