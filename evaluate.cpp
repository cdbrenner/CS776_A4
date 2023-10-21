#include "evaluate.h"

void deleter(double* variables)
{
    if(variables != nullptr)
        delete[] variables;
}

double eval(Individual& individual, int choice, int choice_2, int random_seed, int srand_offset,
                     int variable_count, int bit_length[], double scaler[], double max_variable_value[], int weight_normal, int weight_special)
{
    double fitness;

    switch(choice)
    {
        case 1:
            try
                {fitness = floorPlanning(individual, variable_count, bit_length, scaler, max_variable_value, weight_normal, weight_special, choice_2);}
            catch(double variable_value[])
                {throw variable_value;}
            break;
    }

    return fitness;
}

double eval_o(Individual& individual, int choice, int choice_2, int random_seed, int srand_offset,
                        int variable_count, int bit_length[], double scaler[], double max_variable_value[], int weight_normal, int weight_special)
{
    double objective;

    switch(choice)
    {
        case 1:
            try
                {objective = floorPlanning(individual, variable_count, bit_length, scaler, max_variable_value, weight_normal, weight_special, choice_2);}
            catch(double variable_value[])
                {throw variable_value;}
            break;
    }

    return objective;
}

double* decode(Individual& individual, int bit_length, double scaler)
{
    int variable_count = individual.get_chromosome_length()/bit_length;

    double* variables = new double[variable_count];

    for(int j = 0; j < variable_count; j++)
    {
        double variable_sum = 0;
        double variable_sign = 0;
        for(int i = 0; i < bit_length; i++)
        {
            if(i == 0)
            {
                individual.get_chromosome()[(j*bit_length) + i] == 1 ? variable_sign = 1 : variable_sign = -1;
            }
            else
            {
                individual.get_chromosome()[(j*bit_length) + i] == 1 ? variable_sum += pow(2,bit_length - (i+1)) : 0;
            }
        }
        variable_sum /= scaler;
        variable_sum *= variable_sign;
        variables[j] = variable_sum;
    }
    
    return variables;
}

double* decode_withVarsOfDiffBitLength_onlyPositive(Individual& individual, int variable_count, int bit_length[], double scaler[])
{
    double* variables = new double[variable_count];

    int chromosome_position = 0;
    for(int j = 0; j < variable_count; j++)
    {

        double variable_sum = 0;
        for(int i = 0; i < bit_length[j]; i++)
            individual.get_chromosome()[chromosome_position + i] == 1 ? variable_sum += pow(2,bit_length[j] - (i+1)) : 0;
        
        chromosome_position += bit_length[j];

        variable_sum /= scaler[j];
        variables[j] = variable_sum;
    }
    
    return variables;
}

double floorPlanning(Individual& individual, int variable_count, int bit_length[], double scaler[], double max_variable_value[], int weight_normal, int weight_special, int choice)
{
    double fitness = -1;
    double *variables = decode_withVarsOfDiffBitLength_onlyPositive(individual, variable_count, bit_length, scaler);
    
    //SETTING DIMENSIONS OF THE INDIVIDUAL IS DONE SO THAT THE DIMENSIONS CAN BE PULLED LATER IN void Population::report(int generation, int option) FOR LOGGING
    individual.set_dimensions(variables, variable_count);

    double *catch_block_data = new double[2];

    try
    {
        for(int i = 0; i < variable_count; i++)
        {
            variables[i] > max_variable_value[i] ? catch_block_data[0] = i : 0;
            variables[i] > max_variable_value[i] ? catch_block_data[1] = variables[i] : 0;
            variables[i] > max_variable_value[i] ? throw(catch_block_data) : 0;
        }
    }
    catch(double variable_value)
        {throw variable_value;}

    double living = 1.5*pow((8 + variables[0]),2);
    living < 120 ? living = 300 + weight_normal*(120 - living) : 0;
    living > 300 ? living = 300 + weight_normal*(living - 300) : 0;

    double kitchen = (6 + variables[1])*(6 + variables[2]);

    if(kitchen < 50)
    {
        kitchen = 120 + weight_special*(50 - kitchen);
    }
    else if(kitchen > 120)
    {
        kitchen = 120 + weight_special*(kitchen - 120);
    }

    double hall = 5.5*(3.5 + variables[3]);
    hall < 19 ? hall = 72 + weight_normal*(19 - hall) : 0;
    hall > 72 ? hall = 72 + weight_normal*(hall - 72) : 0;

    double bed_1 = 1.5*pow((10 + variables[4]),2);
    bed_1 < 100 ? bed_1 = 180 + weight_normal*(100 - bed_1) : 0;
    bed_1 > 180 ? bed_1 = 180 + weight_normal*(bed_1 - 180) : 0;

    double bed_2 = 1.5*pow((9 + variables[5]),2);
    bed_2 < 100 ? bed_2 = 180 + weight_normal*(100 - bed_2) : 0;
    bed_2 > 180 ? bed_2 = 180 + weight_normal*(bed_2 - 180) : 0;

    double bed_3 = 1.5*pow((8 + variables[6]),2);
    bed_3 < 100 ? bed_3 = 180 + weight_normal*(100 - bed_3) : 0;
    bed_3 > 180 ? bed_3 = 180 + weight_normal*(bed_3 - 180) : 0;

    double objective_function = living + 2*kitchen + hall + bed_1 + bed_2 + bed_3;
    
    fitness = 50000 - objective_function;

    deleter(variables);
    deleter(catch_block_data);

    if(choice != 2)
        return fitness;
    else
        return objective_function;
}