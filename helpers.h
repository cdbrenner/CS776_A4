#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unistd.h>

//PRINT HELPERS
std::string add_whitespace(int current_line_number, int total_line_count, bool delimeter);

//PROBABILITY HELPERS
int flip(float probability, int random_seed, int offset);
int random_index_in_range(int low, int high, int random_seed, int offset);
void report_averager(int iterations, std::string filename, std::string output_name, int precision, int population_size);