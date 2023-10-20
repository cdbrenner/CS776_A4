#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unistd.h>

//DYNAMIC HELPERS
// int add_dynamic_element_to_end(int **dynamic_array, int array_length, int new_element);
int add_dynamic_element_to_end(int *&dynamic_array, int array_length, int new_element);
int add_dynamic_element_to_beginning(int *&dynamic_array, int array_length, int new_element);
int combine_dynamic_arrays(int *&dynamic_array_begin, int *&dynamic_array_end, int array_length, int new_element);

//PRINT HELPERS
std::string add_whitespace(int current_line_number, int total_line_count, bool delimeter);

//PROBABILITY HELPERS
int flip(float probability, int random_seed, int offset);
int random_index_in_range(int low, int high, int random_seed, int offset);
void report_averager(int iterations, std::string filename, std::string output_name, int precision, int population_size);