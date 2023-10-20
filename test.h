#pragma once
#include <iostream>
#include <string>
#include "evaluate.h"
#include "population.h"

void max_floorplanning_objective_value(int, int, int);

void test_nine_variables_in_random_choice(int, int);

void verify_xover_mutation_mechanism(Population* parent, Population* child);

void verify_string_equivalence(Individual* one, Individual* two, std::string function_location);