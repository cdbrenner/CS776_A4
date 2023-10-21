#pragma once
#include <cmath>
#include <random>
#include "individual.h"

void deleter(double*);
double eval(Individual&, int choice_1, int choice_2, int random_seed, int srand_offset,
                    int variable_count, int bit_length[], double scaler[], double max_variable_value[], int weight_normal, int weight_special);
double eval_o(Individual&, int choice_1, int choice_2, int random_seed, int srand_offset,
                    int variable_count, int bit_length[], double scaler[], double max_variable_value[], int weight_normal, int weight_special);
double* decode(Individual&, int bit_length, double scaler);
double* decode_withVarsOfDiffBitLength_onlyPositive(Individual&, int variable_count, int bit_length[], double scaler[]);

//FLOOR PLANNING
double floorPlanning(Individual& individual, int variable_count, int bit_length[], double scaler[], double max_variable_value[],
                                    int weight_normal, int weight_special, int option);