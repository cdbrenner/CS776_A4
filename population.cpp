//TESTS IN REPORT(), STATS()
// UNIT TESTS IN GENERATION(), XOVER_MUTATE(), CHC_GENERATION()
#include "population.h"
#include "test.h"

Population::Population()
{
    for(int i = 0; i < options.population_size; i++)
    {
        child_transform_data[i][0] = 2;
        child_transform_data[i][1] = 0;
    }
    
    for(int i = 0; i < options.population_size; i++)
    {
        transform_data[i][0] = 2;
        transform_data[i][1] = 1;
    }
 
    average = min = max = sum_fitness = convergence = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        member_chosen_count[i] = 0;
    }
}

//FOR PROGRAMS REQUIRING ONLY A SINGLE INITIAL POPULATION
Population::Population(Options options)
{
    this->options = options;
    
    for(int i = 0; i < options.population_size; i++)
    {
        child_transform_data[i][0] = 2;
        child_transform_data[i][1] = 0;
    }
    
    for(int i = 0; i < options.population_size; i++)
    {
        transform_data[i][0] = 2;
        transform_data[i][1] = 1;
    }
 
    average = min = max = sum_fitness = convergence = -1;
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, i);
    }
}

//FOR PROGRAMS REQUIRING MULTIPLE INITIAL POPULATIONS
Population::Population(Options options, int srand_offset)
{
    this->options = options;

    for(int i = 0; i < options.population_size; i++)
    {
        child_transform_data[i][0] = 2;
        child_transform_data[i][1] = 0;
    }
    
    for(int i = 0; i < options.population_size; i++)
    {
        transform_data[i][0] = 2;
        transform_data[i][1] = 1;
    }
 
    average = min = max = sum_fitness = convergence = -1;
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, srand_offset*options.population_size + i);
    }
}

Population::Population(Population& rhs)
{
    options = rhs.options;
    members = new Individual[options.population_size];
    for(int i = 0; i < options.population_size; i++)
    {
        // members[i].init_chromosome_array(options.chromosome_length);
        members[i].copy_individual_data(rhs.get_members()[i]);
    }
}

Population::~Population()
{
    if(members != nullptr)
        delete[] members;
    
    if(max_fitness_dimensions != nullptr)
        delete max_fitness_dimensions;
}

void Population::init_transform_data(int row)
{
    transform_data[row][0] = options.m_meta_length;
    transform_data[row][1] = 1;
    transform_data[row][2] = row;
    transform_data[row][3] = row;
    transform_data[row][4] = -1;
}

void Population::set_options(Options options)
{
    this->options = options;
}

//FOR PROGRAMS REQUIRING ONLY A SINGLE INITIAL POPULATION
void Population::set_members()
{
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, i);
    }
}

//FOR PROGRAMS REQUIRING MULTIPLE INITIAL POPULATIONS
void Population::set_members(int srand_offset)
{
    members = new Individual[this->options.population_size];
    for(int i = 0; i < this->options.population_size; i++)
    {
        members[i].set_chromosome_length(this->options.chromosome_length);
        members[i].init(options.random_seed, srand_offset*options.population_size + i);
    }
}

void Population::copy_members(const Population &copy)
{
    for(int i = 0; i < options.population_size; i++)
        members[i] = copy.members[i];
}

void Population::copy_population(const Population &copy)
{
    copy_members(copy);

    for(int i = 0; i < options.population_size; i++)
    {
        for(int j = 0; j < copy.transform_data[i][0]; j++)
        {
            transform_data[i][j] = copy.transform_data[i][j];
        }
    }

    for(int i = 0; i < options.population_size; i++)
    {
        for(int j = 0; j < copy.child_transform_data[i][0]; j++)
        {
            child_transform_data[i][j] = copy.child_transform_data[i][j];
        }
    }

}

void Population::set_transform_data_by_row(int* data, int row)
{
    for(int i = 0; i < data[0]; i++)
    {
        transform_data[row][i] = data[i];
    }
}

void Population::set_child_transform_data_by_row(int* data, int row)
{
    for(int i = 0; i < data[0]; i++)
    {
        child_transform_data[row][i] = data[i];
    }
}

void Population::reset_super_individual_count()
{
    super_individuals = 0;
    semi_super_individuals = 0;
}

int Population::find_max_fitness_member()
{
    double temp_fitness = -1;
    double temp_max = 0;
    int temp_max_member_index = 0;

    for(int i = 0; i < options.population_size; i++)
    {
        temp_fitness = members[i].get_fitness();

        if(temp_fitness > temp_max)
        {
            temp_max = temp_fitness;
            temp_max_member_index = i;
        }
    }

    return temp_max_member_index;
}

Individual* Population::get_members()
{
    return members;
}

int* Population::get_transform_data(int row)
{
    return transform_data[row];
}

int* Population::get_child_transform_data(int row)
{
    return child_transform_data[row];
}

double Population::get_min()
{
    return min;
}

double Population::get_max()
{
    return max;
}

double Population::get_average()
{
    return average;
}

double Population::get_sum_fitness()
{
    return sum_fitness;
}

double Population::get_convergence()
{
    return convergence;
}

void Population::get_member_chosen_stats()
{
    double total = 0;
    for(int i = 0; i < options.population_size; i++)
    {
        total += member_chosen_count[i];
    }

    std::cout << "total = " << total << std::endl;

    for(int i = 0; i < options.population_size; i++)
    {
        std::cout << "Member[" << i << "] fitness-frac = " << proportional_fitnesses[i] << std::endl;
        std::cout << "Member[" << i << "] occurence rate = " << member_chosen_count[i]/total << std::endl;
    }
}

Options Population::get_options()
{
    return options;
}

//CHOICE CHOOSES WHICH OBJECTIVE FUNCTION TO EVALUATE
void Population::evaluate(int choice, int choice_2, int random_seed, int srand_offset)
{
    double fitness = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        try
            {fitness = eval(members[i], choice, choice_2, random_seed, srand_offset + i,
                                    options.variable_count, options.bit_length, options.scaler, options.max_variable_value,
                                                                                    options.penalty_weight_1, options.penalty_weight_2);}
        catch(double variable_value[])
            {throw(variable_value);}
        
        members[i].set_fitness(fitness);
    }
}

//CHOICE CHOOSES WHICH OBJECTIVE FUNCTION TO EVALUATE
void Population::evaluate_o(int choice, int choice_2, int random_seed, int srand_offset)
{
    double objective_value = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        try
            {objective_value = eval_o(members[i], choice, choice_2, random_seed, srand_offset + i,
                                            options.variable_count, options.bit_length, options.scaler, options.max_variable_value,
                                                                                            options.penalty_weight_1, options.penalty_weight_2);}
        catch(double variable_value[])
            {throw(variable_value);}

        members[i].set_objective_value(objective_value);
    }
}

void Population::stats(int& total_super_individuals, int& total_semi_super_individuals)
{
    sum_fitness = convergence = 0;
    min = max = members[0].get_fitness();
    max_fitness_member_index = 0;
    double fitness = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        fitness = members[i].get_fitness();

        sum_fitness += fitness;

        if(fitness < min)
        {
            min = fitness;
        }
        if(fitness > max)
        {
            max = fitness;
            max_fitness_member_index = i;
        }
    }
    average = sum_fitness/options.population_size;

    //MAYBE THE NUMBER OF ITERATIONS IN THIS SEARCH FOR SUPER INDIVIDUALS COULD BE REDUCED HEURISTICALLY 
    for(int i = 0; i < options.population_size; i++)
    {
        double scale = members[i].get_fitness()/average;

        if(scale >= options.semi_super_individual_threshold && scale < options.super_individual_threshold)
            semi_super_individuals++;
        else if(scale >= options.super_individual_threshold)
            super_individuals++;

        if(convergence < scale)
        {
            convergence = scale;
        }
    }

    total_super_individuals += super_individuals;
    total_semi_super_individuals += semi_super_individuals;
}

//NEEDS TO BE UPDATED WITH IF STATEMENTS RATHER THAN ? STATEMENS, LIKE IN stats() ABOVE
void Population::stats_o()
{
    sum_objective = 0;
    min_objective = max_objective = members[0].get_objective_value();
    double objective_value = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        objective_value = members[i].get_objective_value();

        sum_objective += objective_value;
        objective_value < min_objective ? min_objective = objective_value : 0;
        objective_value > max_objective ? max_objective = objective_value : 0;

        //MAX_FITNESS_MEMBER_INDEX NEEDS TO BE CHANGED THROUGH PROGRAM MODIFICATION TO MAX_OBJECTIVE_MEMBER_INDEX
        // objective_value > max_objective ? max_fitness_member_index = i : 0;
    }
    average_objective = sum_objective/options.population_size;
}

//SET OPTION = 1 IF AVERAGING IS NOT REQUIRED
void Population::report(int generation, int option, int total_super_individuals, int total_semi_super_individuals, bool extinction_event)
{
    //TEST
    // char temp;
    // std::cout << "max_fitness_member_index = "  << max_fitness_member_index << std::endl;
    // std::cout << "variables[0] = " << members[max_fitness_member_index].get_dimensions()[0] << std::endl;
    // std::cin >> temp;

    //NON-AVERAGING REPORT
    if(options.GA_iteration == 0 || option == 1)
    {
        std::ofstream out(options.output_file, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision) << add_whitespace(generation, options.max_generations, true)
                << generation << ",\t\t" << min << ",\t\t" << average << ",\t\t" << max
                    << ",\t\t" << (extinction_event ? 1 : 0)
                        << ",\t\t\t\t\t" << std::setprecision(5) << convergence << ",\t\t" << semi_super_individuals << ",\t\t\t" << super_individuals << ",\t\t\t" << total_semi_super_individuals << ",\t\t\t" << total_super_individuals
                            << ",\t\t\t\t" << std::setprecision(options.print_precision) << 1.5 * (members[max_fitness_member_index].get_dimensions()[0] + options.living_width_offset)
                                << ",\t\t" << members[max_fitness_member_index].get_dimensions()[0] + options.living_width_offset
                                    << ",\t\t" << 1.5* pow(members[max_fitness_member_index].get_dimensions()[0] + options.living_width_offset, 2)
                                        << ",\t\t" << members[max_fitness_member_index].get_dimensions()[1] + options.kitchen_length_offset
                                            << ",\t\t" << members[max_fitness_member_index].get_dimensions()[2] + options.kitchen_width_offset
                                                << ",\t\t" << members[max_fitness_member_index].get_dimensions()[1] + options.kitchen_length_offset * (members[max_fitness_member_index].get_dimensions()[2] + options.kitchen_width_offset)
                                                    <<",\t\t" << "5.5"
                                                        << ",\t\t" << members[max_fitness_member_index].get_dimensions()[3] + options.hall_width_offset
                                                            << ",\t\t" << 5.5 * (members[max_fitness_member_index].get_dimensions()[3] + options.hall_width_offset)
                                                                << ",\t\t" << 1.5 * (members[max_fitness_member_index].get_dimensions()[4] + options.bed_1_width_offset)
                                                                    << ",\t\t" << members[max_fitness_member_index].get_dimensions()[4] + options.bed_1_width_offset
                                                                        << ",\t\t" << 1.5 * pow(members[max_fitness_member_index].get_dimensions()[4] + options.bed_1_width_offset, 2)
                                                                            << ",\t\t" << 1.5 * (members[max_fitness_member_index].get_dimensions()[5] + options.bed_2_width_offset)
                                                                                << ",\t\t" << members[max_fitness_member_index].get_dimensions()[5] + options.bed_2_width_offset
                                                                                    << ",\t\t" << 1.5 * pow(members[max_fitness_member_index].get_dimensions()[5] + options.bed_2_width_offset, 2)
                                                                                        << ",\t\t" << 1.5 * (members[max_fitness_member_index].get_dimensions()[6] + options.bed_3_width_offset)
                                                                                            << ",\t\t" << members[max_fitness_member_index].get_dimensions()[6] + options.bed_3_width_offset
                                                                                                << ",\t\t" << 1.5 * pow(members[max_fitness_member_index].get_dimensions()[6] + options.bed_3_width_offset, 2) << std::endl;
            out.close();
    }
    //AVERAGING REPORT
    else
    {
        std::string temp;
        std::string min_prev_str;
        std::string ave_prev_str;
        std::string max_prev_str;
        std::ifstream in(options.input_file);

        //FINDS BOTTOM LINE OF CURRENT REPORT
        for(int i = 0; i < generation + 1; i++)
        {
            getline(in,temp);
        }

        getline(in,temp,',');
        getline(in,min_prev_str,',');
        getline(in,ave_prev_str,',');
        getline(in,max_prev_str,',');
        double min_prev = strtod(min_prev_str.c_str(), NULL);
        double ave_prev = strtod(ave_prev_str.c_str(), NULL);
        double max_prev = strtod(max_prev_str.c_str(), NULL);

        std::ofstream out(options.output_file, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision) << generation << ",\t\t" << min + min_prev << ",\t\t" << average + ave_prev << ",\t\t" << max + max_prev << "," << std::endl;
        out.close();
    }
}

//SET OPTION = 1 IF AVERAGING IS NOT REQUIRED
void Population::report_o(int generation, int option)
{
    if(options.GA_iteration == 0 || option == 1)
    {
        std::ofstream out(options.output_file_o, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision_o) << generation << ",\t\t" << min_objective << ",\t\t" << average_objective << ",\t\t" << max_objective << "," << std::endl;
        out.close();
    }
    else
    {
        std::string temp;
        std::string min_prev_str;
        std::string ave_prev_str;
        std::string max_prev_str;
        std::ifstream in(options.input_file_o);
        for(int i = 0; i < generation + 1; i++)
        {
            getline(in,temp);
        }
        getline(in,temp,',');
        getline(in,min_prev_str,',');
        getline(in,ave_prev_str,',');
        getline(in,max_prev_str,',');
        double min_prev = atof(min_prev_str.c_str());
        double ave_prev = atof(ave_prev_str.c_str());
        double max_prev = atof(max_prev_str.c_str());

        std::ofstream out(options.output_file_o, std::ios::app);
        out << std::fixed << std::setprecision(options.print_precision_o) << generation << ",\t\t" << min_objective + min_prev << ",\t\t" << average_objective + ave_prev << ",\t\t" << max_objective + max_prev << "," << std::endl;
        out.close();
    }
}

void Population::generation(Population*& child, int srand_offset)
{
    int parent_index_1 = 0;
    int parent_index_2 = 0;
    int child_index_1 = 0;
    int child_index_2 = 0;

    Individual *parent_1, *parent_2, *child_1, *child_2;
;
    for(int i = 0; i < options.population_size; i += 2)
    {   
        parent_index_1 = proportional_selection(srand_offset*options.population_size + i);

        // THE FOLLOWING LOOP STOPS ASEXUAL SELECTION
        // ADDED THE k OFFSET FOR SRAND() BECAUSE OCCASIONALLY GETTING HELD UP IN THIS LOOP, PROBABLY DUE TO TIME(NULL) SEED
        int k = 0;
        while(parent_index_2 == parent_index_1)
        {
            parent_index_2 = proportional_selection(srand_offset*options.population_size + i + 1 + k);
            k++;
        }

        child_index_1 = i;
        child_index_2 = i+1;

        parent_1 = &members[parent_index_1];
        parent_2 = &members[parent_index_2];
        
        child_1 = &(child->members[child_index_1]);
        child_2 = &(child->members[child_index_2]);

        // UNIT TEST: STRING EQUIVALENCE OBJECTS
        Individual test_1_p1(*parent_1);
        Individual test_2_p2(*parent_2);

        xover_mutate(parent_1, parent_2, child_1, child_2, srand_offset*options.population_size + i);

        // UNIT TEST: STRING EQUIVALENCE
        verify_string_equivalence(parent_1, &test_1_p1, "POP::GENERATION, AFTER AFTER XOVER_MUTATE CALL");
        verify_string_equivalence(parent_2, &test_2_p2, "POP::GENERATION, AFTER AFTER XOVER_MUTATE CALL");

        child_1->get_transform_data()[options.m_isParent_index] = 0;
        child_2->get_transform_data()[options.m_isParent_index] = 0;
        child_1->get_transform_data()[options.m_parent_1_index] = parent_index_1;
        child_1->get_transform_data()[options.m_parent_2_index] = parent_index_2;
        child_2->get_transform_data()[options.m_parent_1_index] = parent_index_2;
        child_2->get_transform_data()[options.m_parent_2_index] = parent_index_1;

        for(int j = 0; j < child_1->get_mutate_count(); j++)
            child_1->get_transform_data()[j + options.m_meta_length] = child_1->get_mutate_data()[j];
        for(int j = 0; j < child_2->get_mutate_count(); j++)
            child_2->get_transform_data()[j + options.m_meta_length] = child_2->get_mutate_data()[j];

        set_child_transform_data_by_row(child_1->get_transform_data(), i);
        set_child_transform_data_by_row(child_2->get_transform_data(), i + 1);

        parent_1 = nullptr;
        parent_2 = nullptr;
        child_1 = nullptr;
        child_2 = nullptr;
    }
}

int Population::proportional_selection(int srand_offset)
{
    srand(options.random_seed + srand_offset);
    double random_fraction = (double)rand()/RAND_MAX;
    double limits[options.population_size];
    limits[0] = members[0].get_fitness()/sum_fitness;

    for(int i = 1; i < options.population_size; i++)
        limits[i] = limits[i-1] + members[i].get_fitness()/sum_fitness;

    for(int i = 0; i < options.population_size; i++)
    {
        if(random_fraction <= limits[i])
            return i;
    }

    return -1;
}

void Population::xover_mutate(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    // UNIT TEST: STRING EQUIVALENCE OBJECTS
    Individual test_1_p1(*parent_1);
    Individual test_2_p2(*parent_2);
   
    for(int i = 0; i < options.chromosome_length; i++)
    {
        child_1->get_chromosome()[i] = parent_1->get_chromosome()[i];
        child_2->get_chromosome()[i] = parent_2->get_chromosome()[i];
    }

    // UNIT TESTS: STRING EQUIVALENCE
    verify_string_equivalence(parent_1, &test_1_p1, "POP::XOVER_MUTATE, AFTER SETTING CHILD = PARENT");
    verify_string_equivalence(parent_2, &test_2_p2, "POP::XOVER_MUTATE, AFTER SETTING CHILD = PARENT");

    
    //TEST
    // std::cout << "POP::XOVER" << std::endl;
    // std::cout << "probability_x = " << options.probability_x << std::endl;
    // char t;
    // std::cin >> t;

    int index = -1;
    if(flip(options.probability_x, options.random_seed, srand_offset))
        index = one_point_xover(parent_1, parent_2, child_1, child_2, srand_offset);

    child_1->mutate(options.probability_mutation, options.random_seed, srand_offset);
    child_2->mutate(options.probability_mutation, options.random_seed, srand_offset + rand());

    int child_1_transform_array_length = options.m_meta_length + child_1->get_mutate_count();
    int child_2_transform_array_length = options.m_meta_length + child_2->get_mutate_count();

    child_1->get_transform_data()[0] = child_1_transform_array_length;
    child_2->get_transform_data()[0] = child_2_transform_array_length;

    child_1->get_transform_data()[options.m_xover_index] = index;
    child_2->get_transform_data()[options.m_xover_index] = index;
}

int Population::one_point_xover(Individual*& parent_1, Individual*& parent_2, Individual*& child_1, Individual*& child_2, int srand_offset)
{
    int index = random_index_in_range(0, options.chromosome_length, options.random_seed, srand_offset);

    for(int i = index + 1; i < options.chromosome_length; i++)
    {
            child_1->get_chromosome()[i] = parent_2->get_chromosome()[i];
            child_2->get_chromosome()[i] = parent_1->get_chromosome()[i];
    }

    return index;
}


void Population::CHC_generation(Population* child, Population *temp)
{
    int index = -1;
    for(int j = 0; j < options.population_size; j++)
    {
        double fitness = 0;
        for(int i = 0; i < options.population_size*2; i++)
        {
            if(i < options.population_size)
            {
                if(members[i].get_fitness() >= fitness)
                {
                    fitness = members[i].get_fitness();
                    index = i;
                }
            }
            else
            {
                if(child->members[i - options.population_size].get_fitness() >= fitness)
                {
                    fitness = child->members[i - options.population_size].get_fitness();
                    index = i;
                }
            }
        }

        if(index < options.population_size)
        {
             temp->members[j] = members[index];
            // temp->members[j].copy_individual_data(members[index]);
            // temp->members[j].set_dimensions(members[index].get_dimensions(),members[index].get_dimension_count());
            temp->set_transform_data_by_row(transform_data[index],j);
            temp->transform_data[j][options.m_isParent_index] = 1;
            members[index].set_fitness(-1);
        }
        else
        {
            temp->members[j] = child->members[index - options.population_size];
            // temp->members[j].copy_individual_data(child->members[index - options.population_size]);
            // temp->members[j].set_dimensions(child->members[index - options.population_size].get_dimensions(), child->members[index - options.population_size].get_dimension_count());
            temp->set_transform_data_by_row(child_transform_data[index - options.population_size],j);
            child->members[index - options.population_size].set_fitness(-1);
        }
    }

    // child = temp;
    // delete child;
    // child = new Population(options);
    child->copy_population(*temp);

    //TEST
    // std::cout << "POP::CHC(END): after child copy temp" << std::endl;
    // std::cout << "POP::CHC(END): child members" << std::endl;
    
    // UNIT TESTS: STRING EQUIVALENCE
    for(int i = 0; i < options.population_size; i++)
    {
        verify_string_equivalence(&child->get_members()[i], &temp->get_members()[i], "CHC TEST FOR CHILD = TEMP");
    }
}

//TEST
void Population::print_pop()
{
    for(int i = 0; i < options.population_size; i++)
    {
        std::cout << "MEM_"<<i<<": ";
        members[i].print_ind();
    }
    std::cout << std::endl;
}

void Population::print_xover_mut_data()
{
    if(transform_data != nullptr)
    {
        for(int i = 0; i < options.population_size; i++)
        {
            for(int j = 0; j < get_transform_data(i)[0]; j++)
            {
                if(j == 0)
                    std::cout << "MEM_" << i << ": " << get_transform_data(i)[j] << " ";
                else
                    std::cout << get_transform_data(i)[j] << " ";
            }
            std::cout << std::endl;
        }
    }
}