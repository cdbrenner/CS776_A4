#pragma once
#include <sstream>
#include "population.h"
#include "test.h"

class GA
{
    private:
        int m_ga_variant = 0;
        double m_mutation_probability = -1;
        double m_xover_probability = -1;
        Population *parent = nullptr;
        Population *child = nullptr;
        Population *m_temp = nullptr;
        Options options;
        int extinction_counter;
        int total_super_individuals = 0;
        int total_semi_super_individuals = 0;

        //IN ORDER TO RUN XOVER_MUTATION MECHANISM TEST IN CHC MODEL, A GRANDPARENT IS REQUIRED
        Population *grandparent = nullptr;

    public:
        GA(int argc, char *argv[], int eval_option, int iterator, int ga_variant, double mutation_probability, double xover_probability);
        ~GA();

        void setup_options(int argc, char *argv[], int eval_option, int iterator);
        void set_option_xover_prob(double xover_probability);
        void set_option_mutation_prob(double mutation_probability);
        void set_option_extinction_delay(double extinction_delay_count);
        void set_option_convergence_resolution_threshold(double convergence_resolution_threshold);
        void set_option_ga_variant_name(std::string ga_variant_name);
        void set_option_input_file(std::string iteration);
        void set_option_input_file_o(std::string iteration);
        void set_option_output_file(std::string iteration);
        void set_option_output_file_o(std::string iteration);
        void set_file_names(int iteration);

        void init(int eval_option, int report_option);
        void run(int eval_option, int report_option);
        bool extinction_check(int eval_option, int random_seed, int srand_offset);
        bool extinction_event(int eval_option, int random_seed, int srand_offset);
        void report_averager(int total_generation_count);
        void report_cleanup();

        const Options get_options();

        void print_population_data();
};