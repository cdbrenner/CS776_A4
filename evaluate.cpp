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
            fitness = deJong_F1(individual);
            break;
        case 2:
            fitness = deJong_F2(individual);
            break;
        case 3:
            fitness = deJong_F3(individual);
            break;
        case 4:
            fitness = deJong_F4(individual, random_seed, srand_offset);
            break;
        case 5:
            fitness = deJong_F5(individual);
            break;
        case 6:
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
            objective = deJong_F1_o(individual);
            break;
        case 2:
            objective = deJong_F2_o(individual);
            break;
        case 3:
            objective = deJong_F3_o(individual);
            break;
        case 4:
            objective = deJong_F4_o(individual, random_seed, srand_offset);
            break;
        case 5:
            objective = deJong_F5_o(individual);
            break;
        case 6:
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

    //TEST
    // char temp;
    // std::cout << "variables[0] = " << variables[0] << std::endl;
    // std::cout << "dimensions[0] = " << individual.get_dimensions()[0] << std::endl;
    // std::cin >> temp;

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

    //VARIABLES[0] = LIVING_WIDTH
    //VARIABLES[1] = KITCHEN_LENGTH
    //VARIABLES[2] = KITCHEN_WIDTH
    //VARIABLES[3] = HALL_WIDTH
    //VARIABLES[4] = BED1_WIDTH
    //VARIABLES[5] = BED2_WIDTH
    //VARIABLES[6] = BED3_WIDTH

    //TEST
    // std::cout << "EVALUATE::FLOORPLANNING" << std::endl;
    // std::cout << "weight normal = " << weight_normal << std::endl;
    // std::cout << "weight_special = " << weight_special << std::endl;
    // std::cout << std::endl;

    double living = 1.5*pow((8 + variables[0]),2);
    living < 120 ? living = 300 + weight_normal*(120 - living) : 0;
    living > 300 ? living = 300 + weight_normal*(living - 300) : 0;

    double kitchen = (6 + variables[1])*(6 + variables[2]);

    //TEST
    // std::cout << "kitchen(pre) = " << kitchen << std::endl;

    if(kitchen < 50)
    {
        kitchen = 120 + weight_special*(50 - kitchen);
    }
    else if(kitchen > 120)
    {
        kitchen = 120 + weight_special*(kitchen - 120);
    }
    // kitchen < 50 ? kitchen = 120 + weight_special*(50 - kitchen) : 0;
    // kitchen > 120 ? kitchen = 120 + weight_special*(kitchen - 120) : 0;

    //TEST
    // std::cout << "kitchen(post) = " << kitchen << std::endl;

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
    
    //TEST
    // if(objective_function >= 412463)
    // {
    //     std::cout << "EVAL::FP" << std::endl;
    //     std::cout << "obj func = " << objective_function << std::endl;
    //     std::cout << "kitchen length = " << 6 + variables[1] << std::endl;
    //     std::cout << "kitchen width = " << 6 + variables[2]<< std::endl;
    //     std::cout << "kitchen area = " << (6 + variables[1])*(6 + variables[2]) << std::endl;
    //     std::cout << "kitchen = " << kitchen << std::endl;
    //     char t;
    //     std::cin >> t;
    // }
    //     fitness = 412463 - objective_function;

    deleter(variables);
    deleter(catch_block_data);

    if(choice != 2)
        return fitness;
    else
        return objective_function;
}

//MAXIMUM FITNESS SHOULD BE ~78.64
double deJong_F1(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = pow(variables[0],2) + pow(variables[1],2) + pow(variables[2],2);

    fitness = (double)78.6432 - objective_function;

    deleter(variables);

    return fitness;
}

//MAXIMUM FITNESS SHOULD BE 3905.93
double deJong_F2(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 11, 999.51171875);

    double objective_function = 100*pow(pow(variables[0],2)-variables[1], 2) + pow(1 - variables[0], 2);

    fitness = (double)3905.9262268416 - objective_function;
    // fitness = (double)1/(objective_function + 1);

    deleter(variables);

    return fitness;
}

//MAXIMUM FITNESS SHOULD BE 55.6
double deJong_F3(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = floor(variables[0]) + floor(variables[1]) + floor(variables[2]) + floor(variables[3]) + floor(variables[4]);

    fitness = (double)25.6 - objective_function;

    deleter(variables);

    return fitness;
}

//MAXIMUM FITNESS SHOULD BE 1300
double deJong_F4(Individual& individual, int random_seed, int srand_offset)
{
    double fitness;
    double *variables = decode(individual, 7, 99.21875);

    std::default_random_engine generator(srand_offset);
    std::normal_distribution<double> gauss{0,1};

    double objective_function_pt1 = 0;
    for(int i = 0; i < 30; i++)
    {
        objective_function_pt1 += (i+1)*pow(variables[i],4);
    }

    double objective_function_pt2 = 0;
    for(int i = 0; i < 12; i++)
    {
        objective_function_pt2 += gauss(generator);
    }

    double objective_function = objective_function_pt1 + objective_function_pt2;

    if(objective_function < 0)
        objective_function = 0 - objective_function;

    fitness = 1300 - objective_function;

    deleter(variables);

    return fitness;
}

//MAX FITNESS SHOULD BE 1.0
double deJong_F5(Individual& individual)
{
    int a[2][25] = {{-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32},
                        {-32,-32,-32,-32,-32,-16,-16,-16,-16,-16,0,0,0,0,0,16,16,16,16,16,32,32,32,32,32}};

    double fitness;
    double *variables = decode(individual, 16, 999.9847412109375);

    double objective_function_pt1[2][25];
    for(int j = 0; j < 25; j++)
    {
        for(int i = 0; i < 2; i++)
            objective_function_pt1[i][j] = pow(variables[i] - a[i][j],6);
    }

    double objective_function_pt2 = 0;
    for(int j = 1; j <= 25; j++)
        objective_function_pt2 += 1/(j + objective_function_pt1[0][j-1] + objective_function_pt1[1][j-1]);

    double objective_function = 0.002 + objective_function_pt2;

    fitness = (double)1/objective_function;

    deleter(variables);

    return fitness;

}

//MAXIMUM FITNESS SHOULD BE ~78.64
double deJong_F1_o(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = pow(variables[0],2) + pow(variables[1],2) + pow(variables[2],2);

    fitness = (double)78.6432 - objective_function;

    deleter(variables);

    return objective_function;
}

//MAXIMUM FITNESS SHOULD BE 3905.93
double deJong_F2_o(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 11, 999.51171875);

    double objective_function = 100*pow(pow(variables[0],2)-variables[1], 2) + pow(1 - variables[0], 2);

    fitness = (double)3905.9262268416 - objective_function;
    // fitness = (double)1/(objective_function + 1);

    deleter(variables);

    return objective_function;
}

//MAXIMUM FITNESS SHOULD BE 55.6
double deJong_F3_o(Individual& individual)
{
    double fitness;
    double *variables = decode(individual, 9, 99.8046875);

    double objective_function = floor(variables[0]) + floor(variables[1]) + floor(variables[2]) + floor(variables[3]) + floor(variables[4]);

    fitness = (double)25.6 - objective_function;

    deleter(variables);

    return objective_function;
}

double deJong_F4_o(Individual& individual, int random_seed, int srand_offset)
{
    double fitness;
    double *variables = decode(individual, 7, 99.21875);

    std::default_random_engine generator(srand_offset);
    std::normal_distribution<double> gauss{0,1};

    double objective_function_pt1 = 0;
    for(int i = 0; i < 30; i++)
    {
        objective_function_pt1 += (i+1)*pow(variables[i],4);
    }

    double objective_function_pt2 = 0;
    for(int i = 0; i < 12; i++)
    {
        objective_function_pt2 += gauss(generator);
    }

    double objective_function = objective_function_pt1 + objective_function_pt2;

    if(objective_function < 0)
        objective_function = 0 - objective_function;

    fitness = 1300 - objective_function;

    deleter(variables);

    return objective_function;
}

double deJong_F5_o(Individual& individual)
{
    int a[2][25] = {{-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32},
                        {-32,-32,-32,-32,-32,-16,-16,-16,-16,-16,0,0,0,0,0,16,16,16,16,16,32,32,32,32,32}};

    double fitness;
    double *variables = decode(individual, 16, 999.9847412109375);

    double objective_function_pt1[2][25];
    for(int j = 0; j < 25; j++)
    {
        for(int i = 0; i < 2; i++)
            objective_function_pt1[i][j] = pow(variables[i] - a[i][j],6);
    }

    double objective_function_pt2 = 0;
    for(int j = 1; j <= 25; j++)
        objective_function_pt2 += 1/(j + objective_function_pt1[0][j-1] + objective_function_pt1[1][j-1]);

    double objective_function = 0.002 + objective_function_pt2;

    fitness = (double)1/objective_function;

    deleter(variables);

    return objective_function;

}