//TESTS IN SETUP_OPTIONS(), EXTNCTION_CHECK(), EXTINCTION_EVENT()
#include "ga.h"

GA::GA(int argc, char *argv[], int eval_option, int iterator, int ga_variant, double prob_m, double prob_x)
{
    m_ga_variant = ga_variant;
    m_mutation_probability = prob_m;
    m_xover_probability = prob_x;
    setup_options(argc, argv, eval_option, iterator);
}

GA::~GA()
{
    if(options.bit_length != nullptr)
        delete options.bit_length;

    if(options.scaler != nullptr)
        delete options.scaler;

    if(options.max_variable_value != nullptr)
        delete options.max_variable_value;
}

void GA::setup_options(int argc, char *argv[], int eval_option, int iterator)
{
    options.GA_iteration = iterator;
    options.random_seed = time(NULL) + iterator;
    options.extinction_delay = 1;
    options.convergence_resolution_threshold = 0.00015;
    options.super_individual_threshold = 2;
    options.semi_super_individual_threshold = 1.2;
    
    //FLOORPLANNING
    options.penalty_weight_1 = 10;
    options.penalty_weight_2 = 10;
    options.variable_count = 7;

    options.living_width_bit_length = 6;
    options.kitchen_length_bit_length = 7;
    options.kitchen_width_bit_length = 7;
    options.hall_width_bit_length = 5;
    options.bed_1_width_bit_length = 4;
    options.bed_2_width_bit_length = 6;
    options.bed_3_width_bit_length = 6;
                                            //RESOLUTION:
    options.living_width_scaler = 11.81255; // 0.08
    options.kitchen_length_scaler = 11.62053376; // 0.09
    options.kitchen_width_scaler = 11.62053376;  // 0.09
    options.hall_width_scaler = 12.4;       // 0.08
    options.bed_1_width_scaler = 11.3;      // 0.09
    options.bed_2_width_scaler = 14.5385;   // 0.07
    options.bed_3_width_scaler = 15.75;     // 0.06

    options.living_width_max_value = 5.33333;
    options.kitchen_length_max_value = 10.92893;
    options.kitchen_width_max_value = 10.92893;
    options.hall_width_max_value = 2.5;
    options.bed_1_width_max_value = 1.33;
    options.bed_2_width_max_value = 4.33333;
    options.bed_3_width_max_value = 4.0;

    options.living_width_offset = 8;
    options.kitchen_length_offset = 7.07;
    options.kitchen_width_offset = 7.07;
    options.hall_width_offset = 3.5;
    options.bed_1_width_offset = 10;
    options.bed_2_width_offset = 9;
    options.bed_3_width_offset = 8;


    options.bit_length = new int[7]{options.living_width_bit_length, options.kitchen_length_bit_length, options.kitchen_width_bit_length,
                                        options.hall_width_bit_length, options.bed_1_width_bit_length, options.bed_2_width_bit_length,
                                            options.bed_3_width_bit_length};

    options.scaler = new double[7]{options.living_width_scaler, options.kitchen_length_scaler, options.kitchen_width_scaler,
                                        options.hall_width_scaler, options.bed_1_width_scaler, options.bed_2_width_scaler,
                                            options.bed_3_width_scaler};

    options.max_variable_value = new double[7]{options.living_width_max_value, options.kitchen_length_max_value, options.kitchen_width_max_value,
                                                options.hall_width_max_value, options.bed_1_width_max_value, options.bed_2_width_max_value,
                                                    options.bed_3_width_max_value};

    switch(eval_option)
    {
        case 1:
            options.chromosome_length = 0;
            for(int i = 0; i < options.variable_count; i++)
            {
                options.chromosome_length += options.bit_length[i];
            }

            options.population_size = 50; //POPULATION SIZE CANNOT EQUAL ODD NUMBER OR SEGMENT FAULT!!!
            options.max_generations = 1500;

            //TEST
            options.probability_x = m_xover_probability;
            options.probability_mutation = m_mutation_probability;

            options.ave_file = "output_floorPlanning_AVE.txt";
            options.ave_file_o = "output_floorPlanning_AVE_ObjFnc.txt";
            options.print_precision = 2;
            options.print_precision_o = 2;
            break;
    }
}

void GA::set_option_xover_prob(double xover_probability)
{
    options.probability_x = xover_probability;
}

void GA::set_option_mutation_prob(double mutation_probability)
{
    options.probability_mutation = mutation_probability;
}

void GA::set_option_extinction_delay(double count)
{
    options.extinction_delay = count;
}

void GA::set_option_convergence_resolution_threshold(double threshold)
{
    options.convergence_resolution_threshold = threshold;
}

void GA::set_option_ga_variant_name(std::string name)
{
    options.ga_variant_name = name;
}

void GA::set_option_input_file(std::string run_number)
{
    options.input_file = "output_floorPlanning_" + options.ga_variant_name + "_" + run_number  + ".txt";
}

void GA::set_option_input_file_o(std::string run_number)
{
    options.input_file_o = "output_floorPlanning_" + options.ga_variant_name + "_" + run_number  + "_ObjFnc.txt";
}

void GA::set_option_output_file(std::string run_number)
{
    options.output_file = "output_floorPlanning_" + options.ga_variant_name + "_" + run_number  + ".txt";
}

void GA::set_option_output_file_o(std::string run_number)
{
    options.output_file_o = "output_floorPlanning_" + options.ga_variant_name + "_" + run_number  + "_ObjFnc.txt";
}

void GA::set_file_names(int iterator)
{
    std::stringstream ss1;
    std::stringstream ss2;
    std::string temp1;
    std::string temp2;
    int previous_iterator = iterator - 1;
    ss1 << iterator;
    ss1 >> temp1;
    ss2 << previous_iterator;
    ss2 >> temp2;
    
    set_option_input_file(temp2);
    set_option_input_file_o(temp2);
    set_option_output_file(temp1);
    set_option_output_file_o(temp1);
}

void GA::init(int eval_option, int report_option)
{
    //TEST
    std::cout << "GA::INIT" << std::endl;
    std::cout << "prob M = " << options.probability_mutation << std::endl;
    std::cout << "prob X = " << options.probability_x << std::endl;
    std::cout << std::endl;

    if(report_option == 1)
    {
        std::ofstream out(options.output_file);
        out << "GEN,\t\tMIN,\t\t\t\tAVE,\t\t\t\tMAX,\t\t\t\tEXTINCT,\t\tCONV,\t\t\t\tSEMI,\t\tSUPER,\tT_SEMI,\tT_SUPER,\tL_L,\t\t\tL_W,\t\tL_a,\t\tK_L,\t\tK_W,\t\tK_A,\t\tH_L,\t\tH_W,\t\tH_A,\t\tB1_L,\t\tB1_W,\t\tB1_A,\t\tB2_L,\t\tB2_W,\t\tB2_A,\t\tB3_L,\t\tB3_W,\t\tB3_A,\n";
        out.close();
    }
    
    //NOTE THAT OBJECTIVE LOGGING HAS BEEN COMMENTED OUT FOR FLOORPLANNING EVALUATIONS FOR THE TIME BEING
    // std::ofstream out_2(options.output_file_o);
    // out_2 << "GEN,\t\tMIN,\t\t\tAVE,\t\t\tMAX,\t\t\tCONV,\t\tSEMI,\t\tSUPER,\t\tL_L,\t\tL_W,\t\tL_a,\t\tK_L,\t\tK_W,\t\tK_A,\t\tH_L,\t\tH_W,\t\tH_A,\t\tB1_L,\t\tB1_W,\t\tB1_A,\t\tB2_L,\t\tB2_W,\t\tB2_A,\t\tB3_L,\t\tB3_W,\t\tB3_A,\n";
    // out_2.close();

    extinction_counter = 0;
    parent = new Population(options);
    child = new Population(options);
    m_temp = new Population(options);

    // TEST
    // std::cout << "GA::INIT::below parent child initialization\n\n";
    // std::cout << "parent member 0:\n";
    // parent->get_members()[0].print_ind();
    

    for(int i = 0; i < options.population_size; i++)
        parent->init_transform_data(i);

    // TEST
    // std::cout << "GA::INIT::below parent init_transform_data\n\n";

    try
    {
        parent->evaluate(eval_option, 1, options.random_seed, 0);
        parent->evaluate_o(eval_option, 2, options.random_seed, 0);
    }
    catch(double variable_value[])
    {
        throw(variable_value);
    }

    // TEST
    // std::cout << "GA::INIT::below parent evaluations\n\n";

    parent->stats(total_super_individuals, total_semi_super_individuals);

    // TEST
    // std::cout << "GA::INIT::below stats\n\n";

    if(report_option == 1)
        parent->report(0, 1, total_super_individuals, total_semi_super_individuals, false);
    
    //OBJECTIVE OPERATIONS REPORT COMMENTED OUT
    // parent->stats_o();
    // parent->report_o(0, 1);

    // TEST
    // std::cout << "GA::INIT::bottom\n\n";
}

void GA::run(int eval_option, int report_option)
{
    bool extinction = false;

    for(int i = 1; i < options.max_generations; i++)
    {
        //TEST: PRINTS GENERATION FOR CLARITY
        // std::cout << "\n\nGENERATION = " << i << std::endl << std::endl;

        int srand_offset = i*options.population_size;

        // UNIT TEST OBJECTS
        Individual *test = new Individual[options.population_size];
        for(int i = 0; i < options.population_size; i++)
            test[i].copy_individual_data(parent->get_members()[i]);
    
        parent->generation(child, i);
        
        try
        {
            child->evaluate(eval_option, 1, options.random_seed, srand_offset);
            child->evaluate_o(eval_option, 2, options.random_seed, srand_offset);
        }
        catch(double variable_value[])
        {
            throw(variable_value);
        }

        //SET THE CHILD'S TRANSFORM_DATA WITH THE PARENTS CHILD_TRANSFORM_DATA
        for(int j = 0; j < options.population_size; j++)
        {
            for(int k = 0; k < parent->get_child_transform_data(j)[0]; k++)
            {
                child->get_transform_data(j)[k] = parent->get_child_transform_data(j)[k];
            }
        }

        if(m_ga_variant == 3 || m_ga_variant == 4)
            parent->CHC_generation(child, m_temp);

        // UNIT TESTS: STRING EQUIVALENCE
        for(int j = 0; j < options.population_size; j++)
        {
            verify_string_equivalence(&parent->get_members()[j],&test[j],"GA::RUN, AFTER CHC GENERATION");
        }

        // UNIT TEST: XOVER MUTATE MECHANISM
        verify_xover_mutation_mechanism(parent, child);

        child->stats(total_super_individuals, total_semi_super_individuals);

        //TEST: PRINT POPULATION AND TRANSFORM DATA
        // if(extinction)
        // {
        //     std::cout << "\nPOP::RUN(BELOW REPORT)" << std::endl;
        //     print_population_data();

        //     char temp;
        //     std::cin >> temp;
        // }

        if(report_option == 1)
        {
            child->report(i, 1, total_super_individuals, total_semi_super_individuals, extinction);
            extinction ? extinction = false : 0;
        }

        //OBJECTIVE OPERATIONS REPORT COMMENTED OUT
        // child->stats_o();
        // child->report_o(i, 1);
        
        Population *temp = parent;
        parent = child;
        child = temp;

        parent->reset_super_individual_count();
        child->reset_super_individual_count();

        if(m_ga_variant == 2 || m_ga_variant == 4)
            extinction = extinction_check(eval_option, options.random_seed, srand_offset);

        delete[] test;

        if(i == options.max_generations - 1)
        {
            int index = parent->find_max_fitness_member();
            std::cout << "MAX MEM: "; parent->get_members()[index].print_ind();
            std::cout << std::fixed << std::setprecision(2) << "FITNESS: " << parent->get_members()[index].get_fitness() << std::endl;
        }
    }

    // report_cleanup();
}

bool GA::extinction_check(int eval_option, int random_seed, int srand_offset)
{
    double convergence = parent->get_convergence();
    double convergence_check = convergence - 1;

    convergence_check < options.convergence_resolution_threshold ? extinction_counter++ : extinction_counter = 0;

    return extinction_counter == options.extinction_delay ? extinction_event(eval_option, options.random_seed, srand_offset) : false;
}

bool GA::extinction_event(int eval_option, int random_seed, int srand_offset)
{
    extinction_counter = 0;
    if(options.ga_variant_name == "S-E")
    {
        int max_fitness_member = parent->find_max_fitness_member();
        parent->get_members()[0] = parent->get_members()[max_fitness_member];
    }

    for(int i = 1; i < options.population_size; i++)
    {
        parent->get_members()[i].init(random_seed, srand_offset + i);
        parent->init_transform_data(i);
    }

    try
    {
        parent->evaluate(eval_option, 1, options.random_seed, srand_offset);
        // parent->evaluate_o(eval_option, 2, options.random_seed, srand_offset);
    }
    catch(double variable_value[])
    {
        throw(variable_value);
    }

    parent->stats(total_super_individuals, total_semi_super_individuals);
    // parent->stats_o();

    return true;
}

void GA::report_averager(int total_run_count)
{
    double temp_data[options.max_generations][4];
    for(int i = 0; i < options.max_generations; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            temp_data[i][0] = i;
            temp_data[i][j] = 0;
        }
    }

    for(int i = 0; i < total_run_count; i++)
    {
        std::string filename = "output_floorPlanning_" + options.ga_variant_name + "_" + std::to_string(i) + ".txt";
        std::ifstream in(filename);

        for(int k = 0; k < options.max_generations + 1; k++)
        {
            std::string temp_1;
            if(k == 0)
                getline(in, temp_1);
            else
            {
                getline(in,temp_1,',');
                for(int j = 1; j < 4; j++)
                {
                    getline(in,temp_1,',');
                    temp_data[k-1][j] += std::strtod(temp_1.c_str(), NULL);
                }
             
                getline(in,temp_1);
            }
        }

        in.close();
    }

    
    for(int i = 0; i < options.max_generations; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            temp_data[i][j] /= total_run_count;
        }
    }

    //TEST
    // std::cout << "GA::AVERAGER RESULTS" << std::endl;
    // for(int i = 0; i < options.max_generations; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         std::cout << temp_data[i][j] << ", ";
    //     }
    //     std::cout << std::endl;
    // }

    std::string out_filename = "output_floorPlanning_" + options.ga_variant_name + "_AVE.txt";
    std::ofstream out(out_filename);

    out << "GEN,\tMIN,\t\t\tAVE,\t\t\tMAX,\n";
    for(int i = 0; i < options.max_generations; i++)
    {
        out << std::fixed << std::setprecision(options.print_precision) << add_whitespace(i, options.max_generations, true)
                << (int)temp_data[i][0] << ",\t\t" << temp_data[i][1] << ",\t\t" << temp_data[i][2] << ",\t\t" << temp_data[i][3] << std::endl;
    }
    out.close();
}

void GA::report_cleanup()
{
    if(options.GA_iteration != 0)
    {
        std::remove(options.input_file.c_str());
        std::remove(options.input_file_o.c_str());
    }
}

const Options GA::get_options()
{
    return options;
}

void GA::print_population_data()
{
        std::cout << "PARENT POPULATION" << std::endl;
        parent->print_pop();
        std::cout << "PARENT TRANSFORM DATA" << std::endl;
        parent->print_xover_mut_data();
        std::cout << "\nCHILD POPULATION" << std::endl;
        child->print_pop();
        std::cout << "CHILD TRANSFORM DATA" << std::endl;
        child->print_xover_mut_data();
        std::cout << std::endl;
}