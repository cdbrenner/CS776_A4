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

//RETURN FITNESS OF FITNESS FUNCTION
double deJong_F1(Individual&);
double deJong_F2(Individual&);
double deJong_F3(Individual&);
double deJong_F4(Individual&, int random_seed, int srand_offset);
double deJong_F5(Individual&);

//RETURN OBJECTIVE_VALUE OF OBJECTIVE FUNCTION
double deJong_F1_o(Individual&);
double deJong_F2_o(Individual&);
double deJong_F3_o(Individual&);
double deJong_F4_o(Individual&, int random_seed, int srand_offset);
double deJong_F5_o(Individual&);

//FLOOR PLANNING
double floorPlanning(Individual& individual, int variable_count, int bit_length[], double scaler[], double max_variable_value[],
                                    int weight_normal, int weight_special, int option);