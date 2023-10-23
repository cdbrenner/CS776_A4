#pragma once
#include <fstream>
#include <iomanip>
#include <memory>
#include "helpers.h"
#include "options.h"
#include "individual.h"
#include "evaluate.h"
// #include "partition/partition_debug.cpp"
#include "partition/partition.cpp"
#define TRANSFORM_DATA_SIZE 1000

class Population
{
    private:
        Options options;
        Eval_results m_results;
        Individual* members = nullptr;
        int transform_data[TRANSFORM_DATA_SIZE][TRANSFORM_DATA_SIZE];
        int transform_data_count = 0;
        int child_transform_data[TRANSFORM_DATA_SIZE][TRANSFORM_DATA_SIZE];
        int child_transform_data_count = 0;
        double average, max, min, sum_fitness, convergence;
        double average_objective, max_objective, min_objective, sum_objective;
        int super_individuals = 0;
        int semi_super_individuals = 0;
        int max_fitness_member_index = -1;

        // TSP
            //PMX
            int pmx_indices[2] = {-1,-1};
            //RANK
            double** member_ids = nullptr; // DOESN'T HAVE A DELETE[] YET
            double sum_rank = 0;

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
        void set_members_ptr(Individual*);
        void copy_members_and_update_id(const Population& population_copy);
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
        int* get_pmx_indices();

        //FUNCTIONS FOR TESTING PROBABILITY ACCURACY
        // void set_proportional_fitnesses();
        // void set_member_chosen_count();
        void get_member_chosen_stats();

        void evaluate(int choice, int random_seed, int srand_offset);
        void stats(int& total_super_individuals, int& total_semi_super_individuals);
        void report(int generation, int option, int total_super_individuals, int total_semi_super_individuals, bool extinction_event);
        void generation(Population*& child, int srand_offset);
        void CHC_generation(Population* child, Population *temp, int srand_offset);
        int proportional_selection(int srand_offset);
        
        // TSP
        void set_member_ids();
        double** get_member_ids();
        void rank_selection_sort(int random_seed, int srand_offset);
        int rank_selection(int srand_offset); // IMPLEMENTED SO THAT EQUAL FITNESS MEMBERS HAVE THE SAME RANK. THEREFORE, EXPECT SLOW CONVERGENCE.
        
        void xover_mutate(Individual*,Individual*,Individual*,Individual*, int);
        int one_point_xover(Individual*&,Individual*&,Individual*&,Individual*&, int);
        void pmx(Individual*,Individual*,Individual*,Individual*, int);


        //TEST
        void print_pop();
        void print_member_ids();
        void print_xover_mut_data();
};