#pragma once
#include <iostream>

struct Options
{
    std::string input_file;
    std::string input_file_o;
    std::string output_file;
    std::string output_file_o;
    std::string ave_file;
    std::string ave_file_o;
    std::string ga_variant_name;
    int GA_iteration;
    int print_precision;
    int print_precision_o;
    int evaluation_mode;
    long int random_seed;
    int population_size;
    int chromosome_length;
    int max_generations;
    double probability_x;
    double probability_mutation;
    double convergence_resolution_threshold;
    int extinction_delay;
    double super_individual_threshold;
    double semi_super_individual_threshold;
    
    //INDIVIDUAL::TRANSFORM_DATA INDICES
    int m_isParent_index = 1; // USED IN CHC TO TELL WHETHER COMPARISON IS MADE TO GRANDPARENT (1) OR CHILD (0)
    int m_parent_1_index = 2;
    int m_parent_2_index = 3;
    int m_xover_index = 4;
    int m_meta_length = m_xover_index + 1; // NUMBER OF ELEMENTS BEFORE ATTACHING MUTATE DATA

    //FLOORPLANNING OPTIONS START HERE
        int variable_count;
    
        //BIT WIDTH REQUIRED FOR SPECIFIC VARIABLE RANGE
        int living_width_bit_length;
        int kitchen_length_bit_length;
        int kitchen_width_bit_length;
        int hall_width_bit_length;
        int bed_1_width_bit_length;
        int bed_2_width_bit_length;
        int bed_3_width_bit_length;
        
        //SCALER REQUIRED TO SCALE THE MAX BIT SUM VALUE TO SPECIFIED RANGE
        double living_width_scaler;
        double kitchen_length_scaler;
        double kitchen_width_scaler;
        double hall_width_scaler;
        double bed_1_width_scaler;
        double bed_2_width_scaler;
        double bed_3_width_scaler;
        
        //CONSTRAINTS
        double living_width_max_value;
        double kitchen_length_max_value;
        double kitchen_width_max_value;
        double hall_width_max_value;
        double bed_1_width_max_value;
        double bed_2_width_max_value;
        double bed_3_width_max_value;
        
        //THE VARIABLE RANGE DOESN'T START FROM ZERO, THEREBY REQUIRING AN OFFSET
        double living_width_offset;
        double kitchen_length_offset;
        double kitchen_width_offset;
        double hall_width_offset;
        double bed_1_width_offset;
        double bed_2_width_offset;
        double bed_3_width_offset;

        int* bit_length = nullptr;
        double* scaler = nullptr;
        double* max_variable_value = nullptr;
        int penalty_weight_1;
        int penalty_weight_2;

};