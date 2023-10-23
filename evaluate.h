#pragma once
#include <cmath>
#include <random>
#include "individual.h"
#include "eval_results.h"

void eval(Individual&, Eval_results& results, double** tour_data, int tour_count, int choice, int random_seed, int srand_offset);

double* decode(Individual&, int bit_length, double scaler);
double* decode_withVarsOfDiffBitLength_onlyPositive(Individual&, int variable_count, int bit_length[], double scaler[]);

// TSP
void TSP(Individual& individual, double** tour_data, int tour_count, int choice, Eval_results& results);
double distance(double x1, double y1, double x2, double y2);
double distance_geo(double x1, double y1, double x2, double y2);