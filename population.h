#pragma once
#include <fstream>
#include <iomanip>
#include "helpers.h"
#include "options.h"
#include "individual.h"
#include "evaluate.h"
#define TRANSFORM_DATA_SIZE 1000

class Population
{
    private:
        Options options;
        Individual* members = nullptr;
        int transform_data[TRANSFORM_DATA_SIZE][TRANSFORM_DATA_SIZE];
        int transform_data_count = 0;
        int child_transform_data[TRANSFORM_DATA_SIZE][TRANSFORM_DATA_SIZE];
        int child_transform_data_count = 0;
        double average, max, min, sum_fitness, convergence;
        double average_objective, max_objective, min_objective, sum_objective;
        int super_individuals = 0;
        int semi_super_individuals = 0;

        //FLOORPLANNING
        double* max_fitness_dimensions = nullptr;
        int max_fitness_member_index = -1;

        //MEMBERS FOR TESTING PROBABILITY ACCURACY
        double proportional_fitnesses[4];
        double member_chosen_count[4];

    public:
        Population();
        Population(Options);
        Population(Options, int);
        Population(Population& copy_population);
        ~Population();

        void init_transform_data(int row);
        void set_options(Options);
        void set_members();
        void set_members(int);
        void copy_members(const Population& population_copy);
        void copy_population(const Population& population_copy);
        void set_transform_data_by_row(int* transform_data_row, int row);
        void set_child_transform_data_by_row(int* child_transform_data, int row);
        void reset_super_individual_count();
        int find_max_fitness_member();

        Individual* get_members();
        int* get_transform_data(int row);
        int* get_child_transform_data(int row);
        double get_average();
        double get_max();
        double get_min();
        double get_sum_fitness();
        double get_convergence();
        Options get_options();
        bool get_is_parent();

        //FUNCTIONS FOR TESTING PROBABILITY ACCURACY
        // void set_proportional_fitnesses();
        // void set_member_chosen_count();
        void get_member_chosen_stats();

        void evaluate(int choice, int choice_2, int random_seed, int srand_offset);
        void evaluate_o(int choice, int choice_2, int random_seed, int srand_offset);
        void stats(int& total_super_individuals, int& total_semi_super_individuals);
        void stats_o();
        void report(int generation, int option, int total_super_individuals, int total_semi_super_individuals, bool extinction_event);
        void report_o(int generation, int option); // HASN'T BEEN UPDATED FOR FLOORPLANNING WHATSOEVER
        void generation(Population*& child, int srand_offset);
        void CHC_generation(Population* child, Population *temp);
        int proportional_selection(int srand_offset);
        void xover_mutate(Individual*,Individual*,Individual*,Individual*, int);
        int one_point_xover(Individual*&,Individual*&,Individual*&,Individual*&, int);

        //TEST
        void print_pop();
        void print_xover_mut_data();
};