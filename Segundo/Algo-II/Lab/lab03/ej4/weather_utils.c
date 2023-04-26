#include "weather_utils.h"
#include "array_helpers.h"
// #include "array_helpers.h"
#include <limits.h>

int get_hist_min_temp(WeatherTable a) {
  int min_t = INT_MAX;
  for (unsigned int year = 0u; year < YEARS; ++year) {
    for (month_t month = january; month <= december; ++month) {
      for (unsigned int day = 0u; day < DAYS; ++day) {
        if (a[year][month][day]._min_temp < min_t) {
          min_t = a[year][month][day]._min_temp;
        }
      }
    }
  }
  return min_t;
}

void get_max_temp_per_year(WeatherTable a, int output[YEARS]) {
  for (unsigned int year = 0u; year < YEARS; ++year) {
    int max_t = INT_MIN;
    for (month_t month = january; month <= december; ++month) {
      for (unsigned int day = 0u; day < DAYS; ++day) {
        if (a[year][month][day]._max_temp > max_t) {
          max_t = a[year][month][day]._max_temp;
        }
      }
    }
    output[year] = max_t;
  }
}

void max_month_rain_per_year(WeatherTable a, month_t output[YEARS]) {
  struct max_rain_month {
    unsigned int rain;
    month_t month;
  } max_rain_month;

  for (unsigned int year = 0u; year < YEARS; ++year) {
    max_rain_month.rain = INT_MIN;
    for (month_t month = january; month <= december; ++month) {
      unsigned int monthly_rain = 0;
      for (unsigned int day = 0u; day < DAYS; ++day) {
        monthly_rain += a[year][month][day]._rainfall;
      }
      monthly_rain = monthly_rain / DAYS;
      if (max_rain_month.rain > monthly_rain) {
        max_rain_month.rain = monthly_rain;
        max_rain_month.month = month;
      }
      output[year] = max_rain_month.month;
    }
  }
}
