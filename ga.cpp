//TESTS IN SETUP_OPTIONS(), EXTNCTION_CHECK(), EXTINCTION_EVENT()
#include "ga.h"

GA::GA(int argc, char *argv[], int iterator, int ga_variant, double prob_m, double prob_x)
{
    m_ga_variant = ga_variant;
    m_mutation_probability = prob_m;
    m_xover_probability = prob_x;
    setup_options(argc, argv, iterator);
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

void GA::setup_options(int argc, char *argv[], int iterator)
{
    options.GA_iteration = iterator;
    options.random_seed = time(NULL) + iterator;
    options.extinction_delay = 1;
    options.convergence_resolution_threshold = 0.00001;
    options.super_individual_threshold = 2;
    options.semi_super_individual_threshold = 1.2;
    
    options.population_size = 350; //POPULATION SIZE CANNOT EQUAL ODD NUMBER OR SEGMENT FAULT!!!
    options.max_generations = 1000;

    if(argc >= 2)
    {
        options.m_tour_data = new double*[options.population_size];
        options.TSP_filename = argv[1];

        std::ifstream in(options.TSP_filename);

        if(in.fail())
        {
            std::string error_message = "\nGA::SETUP_OPTIONS: TSP file does not exist.";
            throw(error_message);
        }

        std::string temp("");
        while(temp != "NODE_COORD_SECTION")
        {
            getline(in,temp);
        }
        while(temp != "EOF")
        {
            getline(in, temp);
            std::stringstream ss;
            std::string temp_1 = "";
            std::string temp_2 = "";
            std::string temp_3= "";
            ss << temp;

            ss >> temp_1;
            ss >> temp_2;
            ss >> temp_3;

            options.m_tour_data[options.tour_data_count] = new double[3];

            if(temp_1 != "EOF")
            {
                options.m_tour_data[options.tour_data_count][0] = std::strtod(temp_1.c_str(), NULL);
                options.m_tour_data[options.tour_data_count][1] = std::strtod(temp_2.c_str(), NULL);
                options.m_tour_data[options.tour_data_count++][2] = std::strtod(temp_3.c_str(), NULL);
            }
        }
        options.chromosome_length = options.tour_data_count;
        in.close();
    }
    else
    {
        std::string error_message = "\nGA::SETUP_OPTIONS: Need TSP filename as argv[1]. Aborting.";
        throw(error_message);
    }

    options.ave_file = "output_TSP_AVE.txt";
    options.ave_file_o = "output_TSP_AVE_ObjFnc.txt";
    options.print_precision = 4;
    options.print_precision_o = 2;
    
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
    options.input_file = "output_TSP_" + options.ga_variant_name + "_" + run_number  + ".txt";
}

void GA::set_option_input_file_o(std::string run_number)
{
    options.input_file_o = "output_TSP_" + options.ga_variant_name + "_" + run_number  + "_ObjFnc.txt";
}

void GA::set_option_output_file(std::string run_number)
{
    options.output_file = "output_TSP_" + options.ga_variant_name + "_" + run_number  + ".txt";
}

void GA::set_option_output_file_o(std::string run_number)
{
    options.output_file_o = "output_TSP_" + options.ga_variant_name + "_" + run_number  + "_ObjFnc.txt";
}

void GA::set_eval_option(int option)
{
    options.eval_option = option;
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
    char temp_c;
    std::cout << "GA::INIT" << std::endl;
    std::cout << "TSP_filename = " << options.TSP_filename << std::endl;
    std::cout << "prob M = " << options.probability_mutation << std::endl;
    std::cout << "prob X = " << options.probability_x << std::endl;
    std::cout << "chromosome_length = " << options.chromosome_length << std::endl;
    std::cout << "convergence_threshold = " << std::fixed << std::setprecision(5) << options.convergence_resolution_threshold << std::endl;
    std::cout << std::endl;

    if(report_option == 1)
    {
        std::ofstream out(options.output_file);
        out << "RANDOM SEED, " << options.random_seed << std::endl;
        out << "GEN,\tMIN,\t\t\t\tAVE,\t\t\t\tMAX,\t\t\t\tEXTINCT,\t\tCONV,\t\t\tSEMI,\t\tSUPER,\t\tT_SEMI,\t\tT_SUPER,\t\t\tTOUR\n";
        out.close();
    
        std::ofstream out_2(options.output_file_o);
        out_2 << "RANDOM SEED, " << options.random_seed << std::endl;
        out_2 << "GEN,\tMIN,\t\t\tAVE,\t\t\tMAX,\t\t\tEXTINCT,\t\tCONV,\t\t\tSEMI,\t\tSUPER,\t\tT_SEMI,\t\tT_SUPER,\t\t\tTOUR\n";
        out_2.close();
    }

    extinction_counter = 0;
    parent = new Population(options);
    child = new Population(options);
    m_temp = new Population(options);

    try
    {
        parent->evaluate(eval_option, options.random_seed, 0);
    }
    catch(double variable_value[])
    {
        throw(variable_value);
    }
    catch(std::string error_message)
    {
        throw(error_message);
    }

    parent->stats(total_super_individuals, total_semi_super_individuals);

    if(report_option == 1)
        parent->report(0, 1, total_super_individuals, total_semi_super_individuals, false);
}

void GA::run(int eval_option, int report_option)
{
    bool extinction = false;

    for(int i = 1; i < options.max_generations; i++)
    {
        int srand_offset = i*options.population_size;
        parent->generation(child, i);
        
        try
        {
            child->evaluate(eval_option, options.random_seed, srand_offset);
        }
        catch(double variable_value[])
        {
            throw(variable_value);
        }
        catch(std::string error_message)
        {
            throw(error_message);
        }

        if(m_ga_variant == 3 || m_ga_variant == 4)
            parent->CHC_generation(child, m_temp, srand_offset);

        child->stats(total_super_individuals, total_semi_super_individuals);

        if(report_option == 1)
        {
            child->report(i, 1, total_super_individuals, total_semi_super_individuals, extinction);
            extinction ? extinction = false : 0;
        }
        
        Population *temp = parent;
        parent = child;
        child = temp;

        parent->reset_super_individual_count();
        child->reset_super_individual_count();

        if(m_ga_variant == 2 || m_ga_variant == 4)
            extinction = extinction_check(eval_option, options.random_seed, srand_offset);

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
        parent->get_members()[i].init_TSP(random_seed, srand_offset + i);
    }

    try
    {
        parent->evaluate(eval_option, options.random_seed, srand_offset);
    }
    catch(double variable_value[])
    {
        throw(variable_value);
    }

    parent->stats(total_super_individuals, total_semi_super_individuals);

    return true;
}

void GA::report_averager(int total_run_count)
{
    double temp_fitness_data[options.max_generations][4];
    double temp_objective_data[options.max_generations][4];
    for(int i = 0; i < options.max_generations; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            temp_fitness_data[i][0] = i;
            temp_fitness_data[i][j] = 0;
            
            temp_objective_data[i][0] = i;
            temp_objective_data[i][j] = 0;
        }
    }
    
    for(int i = 0; i < total_run_count; i++)
    {
        std::string filename = "output_TSP_" + options.ga_variant_name + "_" + std::to_string(i) + ".txt";
        std::string filename_o = "output_TSP_" + options.ga_variant_name + "_" + std::to_string(i) + "_ObjFnc.txt";
        std::ifstream in(filename);
        std::ifstream in_o(filename_o);

        for(int k = 0; k < options.max_generations + 2; k++)
        {
            std::string temp_1;
            std::string temp_2;
            if(k == 0 || k == 1) // GETS RID OF 1ST LINE (RANDOM SEED) AND 2nd LINE (HEADERS)
            {
                getline(in, temp_1);
                getline(in_o, temp_2);
            }
            else
            {
                getline(in,temp_1,',');
                getline(in_o,temp_2,',');
                for(int j = 1; j < 4; j++)
                {
                    getline(in,temp_1,',');
                    getline(in_o,temp_2,',');
                    temp_fitness_data[k-2][j] += std::strtod(temp_1.c_str(), NULL);
                    temp_objective_data[k-2][j] += std::strtod(temp_2.c_str(), NULL);
                }
             
                getline(in,temp_1);
                getline(in_o,temp_1);
            }
        }

        in.close();
        in_o.close();
    }
    
    for(int i = 0; i < options.max_generations; i++)
    {
        for(int j = 1; j < 4; j++)
        {
            temp_fitness_data[i][j] /= total_run_count;
            temp_objective_data[i][j] /= total_run_count;
        }
    }

    std::string out_filename = "output_TSP_" + options.ga_variant_name + "_AVE.txt";
    std::string out_filename_o = "output_TSP_" + options.ga_variant_name + "_AVE_ObjFnc.txt";
    std::ofstream out(out_filename);
    std::ofstream out_o(out_filename_o);

    out << "RANDOM SEED, " << options.random_seed << std::endl;
    out << "GEN,\tMIN,\t\t\tAVE,\t\t\tMAX,\n";
    out_o << "RANDOM SEED, " << options.random_seed << std::endl;
    out_o << "GEN,\tMIN,\t\t\tAVE,\t\t\tMAX,\n";
    for(int i = 0; i < options.max_generations; i++)
    {
        out << std::scientific << std::setprecision(options.print_precision) << add_whitespace(i, options.max_generations, true)
                << (int)temp_fitness_data[i][0] << ",\t\t" << temp_fitness_data[i][1] << ",\t\t" << temp_fitness_data[i][2] << ",\t\t" << temp_fitness_data[i][3] << std::endl;

        out_o << std::fixed << std::setprecision(options.print_precision_o) << add_whitespace(i, options.max_generations, true)
                << (int)temp_objective_data[i][0] << ",\t\t" << temp_objective_data[i][1] << ",\t\t" << temp_objective_data[i][2] << ",\t\t" << temp_objective_data[i][3] << std::endl;
    }
    out.close();
    out_o.close();
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