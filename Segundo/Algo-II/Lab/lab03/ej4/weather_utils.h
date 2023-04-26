#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

int get_hist_min_temp(WeatherTable a);

void get_max_temp_per_year(WeatherTable a, int output[YEARS]);

void max_month_rain_per_year(WeatherTable a, month_t output[YEARS]);
