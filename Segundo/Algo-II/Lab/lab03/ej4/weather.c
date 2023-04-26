/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include "weather.h"
#include <stdio.h>
#include <stdlib.h>

static const int AMOUNT_OF_WEATHER_VARS = 6;

Weather weather_from_file(FILE *file) {
  Weather weather;
  int res = fscanf(file, EXPECTED_WEATHER_FILE_FORMAT, &weather._average_temp,
                   &weather._max_temp, &weather._min_temp, &weather._pressure,
                   &weather._moisture, &weather._rainfall);
  if (res != AMOUNT_OF_WEATHER_VARS) {
    fprintf(stderr, "Invalid array");
    exit(EXIT_FAILURE);
  }
  // if (weather._average_temp > 1000) {
  //   fprintf(stderr, "Invalid array");
  //   exit(EXIT_FAILURE);
  //
  // }
  /* Completar aqui */

  return weather;
}

void weather_to_file(FILE *file, Weather weather) {
  fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp,
          weather._max_temp, weather._min_temp, weather._pressure,
          weather._moisture, weather._rainfall);
}
