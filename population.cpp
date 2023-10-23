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
        
        // BINARY INIT
        // members[i].init(options.random_seed, i);

        // TSP
        members[i].init_TSP(options.random_seed, i);
        members[i].set_id(i);
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
        
        // BINARY INIT
        // members[i].init(options.random_seed, srand_offset*options.population_size + i);
        
        // TSP
        members[i].init_TSP(options.random_seed, srand_offset*options.population_size + i);
        members[i].set_id(i);
    }
}

Population::Population(Population& rhs)
{
    options = rhs.options;

    members = new Individual[options.population_size];

    for(int i = 0; i < options.population_size; i++)
    {
        members[i].copy_individual_data(rhs.get_members()[i]);
    }
}

Population::~Population()
{
    if(members != nullptr)
        delete[] members;
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

void Population::set_members_ptr(Individual* mem)
{
    members = mem;
}

void Population::copy_members_and_update_id(const Population &copy)
{
    for(int i = 0; i < options.population_size; i++)
    {
        members[i] = copy.members[i];
        members[i].set_id(i);
    }
}

void Population::copy_population(const Population &copy)
{
    copy_members_and_update_id(copy);

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

int* Population::get_pmx_indices()
{
    return pmx_indices;
}

void Population::evaluate(int choice, int random_seed, int srand_offset)
{
    for(int i = 0; i < options.population_size; i++)
    {
        try
        {
            eval(members[i], m_results, options.m_tour_data, options.tour_data_count, choice, random_seed, srand_offset + i);
        }
        catch(double variable_value[])
            {throw(variable_value);}
        catch(std::string error_message)
            {throw error_message;}
        
        members[i].set_fitness(m_results.fitness);
        members[i].set_objective_value(m_results.objective);
    }

    rank_selection_sort(random_seed, srand_offset);
}

void Population::stats(int& total_super_individuals, int& total_semi_super_individuals)
{
    // FITNESS STATS
    sum_fitness =  0;
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
    // END FITNESS STATS

    //OBJECTIVE STATS
    sum_objective = 0;
    min_objective = max_objective = members[0].get_objective_value();
    
    double objective_value = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        objective_value = members[i].get_objective_value();

        sum_objective += objective_value;

        if(objective_value < min_objective)
        {
            min_objective = objective_value;
        }
        if(objective_value > max_objective)
        {
            max_objective = objective_value;
        }
    }
    average_objective = sum_objective/options.population_size;
    // END OBJECTIVE STATS

    //MAYBE THE NUMBER OF ITERATIONS IN THIS SEARCH FOR SUPER INDIVIDUALS COULD BE REDUCED HEURISTICALLY 
    convergence = 0;
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

//SET OPTION = 1 IF AVERAGING IS NOT REQUIRED
void Population::report(int generation, int option, int total_super_individuals, int total_semi_super_individuals, bool extinction_event)
{
    //NON-AVERAGING REPORT
    if(options.GA_iteration == 0 || option == 1)
    {
        std::ofstream out(options.output_file, std::ios::app);
        out << std::scientific << std::setprecision(5) << add_whitespace(generation, options.max_generations, true)
                << generation << ",\t\t" << min << ",\t\t" << average << ",\t\t" << max
                    << ",\t\t" << (extinction_event ? 1 : 0)
                        << ",\t\t\t\t" << std::fixed <<  std::setprecision(5) << convergence << ",\t\t" << semi_super_individuals << ",\t\t\t" << super_individuals << ",\t\t\t" << total_semi_super_individuals << ",\t\t\t" << total_super_individuals
                            << ",\t\t\t\t\t";
                            for(int i = 0; i < options.chromosome_length; i++)
                            {
                                out << members[max_fitness_member_index].get_chromosome()[i] << ", ";
                            }
                            out << std::endl;
        out.close();

        std::ofstream out_2(options.output_file_o, std::ios::app);
        out_2 << std::fixed << std::setprecision(options.print_precision_o) << add_whitespace(generation, options.max_generations, true)
                << generation << ",\t\t" << (int) min_objective << ",\t\t" << (int) average_objective << ",\t\t" << (int) max_objective
                    << ",\t\t" << (extinction_event ? 1 : 0)
                        << ",\t\t\t\t" << std::setprecision(5) << convergence << ",\t\t" << semi_super_individuals << ",\t\t\t" << super_individuals << ",\t\t\t" << total_semi_super_individuals << ",\t\t\t" << total_super_individuals
                            << ",\t\t\t\t\t";
                            for(int i = 0; i < options.chromosome_length; i++)
                            {
                                out_2 << members[max_fitness_member_index].get_chromosome()[i] << ", ";
                            }
                            out_2 << std::endl;
        out_2.close();
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
        // PROPORTIONAL SELECTION
        // parent_index_1 = proportional_selection(srand_offset*options.population_size + i);
 
        // RANK SELECTION
        parent_index_1 = rank_selection(srand_offset*options.population_size + i);
 
        // THE FOLLOWING LOOP STOPS ASEXUAL SELECTION
        // ADDED THE k OFFSET FOR SRAND() BECAUSE OCCASIONALLY GETTING HELD UP IN THIS LOOP, PROBABLY DUE TO TIME(NULL) SEED
        int k = 0;

        parent_index_2 = rank_selection(srand_offset*options.population_size + i + 1 + k);
        
        while(parent_index_2 == parent_index_1)
        {
            k++;

            // PROPORTIONAL SELECTION
            // parent_index_2 = proportional_selection(srand_offset*options.population_size + i + 1 + k);
        
            // RANK SELECTION
            parent_index_2 = rank_selection(srand_offset*options.population_size + i + 1 + k);
        }

        child_index_1 = i;
        child_index_2 = i+1;

        parent_1 = &members[parent_index_1];
        parent_2 = &members[parent_index_2];
        
        child_1 = &(child->members[child_index_1]);
        child_2 = &(child->members[child_index_2]);

        xover_mutate(parent_1, parent_2, child_1, child_2, srand_offset*options.population_size + i);

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

void Population::set_member_ids()
{
    member_ids = new double*[options.population_size];
    for(int i = 0; i < options.population_size; i++)
    {
        member_ids[i] = new double[2];
        member_ids[i][0] = members[i].get_fitness();
        member_ids[i][1] = members[i].get_id();
    }
}

double** Population::get_member_ids()
{
    return member_ids;
}

void Population::rank_selection_sort(int random_seed, int srand_offset)
{
    set_member_ids();
    Partition<double**> sort;
    int pivot = sort.random_index_in_range(0, options.population_size, random_seed, srand_offset);
    sort.partition_sort_2D(member_ids, pivot, 0, options.population_size - 1);
}

int Population::rank_selection(int srand_offset)
{
    int rank = 1;
    double previous_fitness = -1;
    for(int i = 0; i < options.population_size; i++)
    {
        if(i == 0)
        {
            previous_fitness = member_ids[i][0];
            member_ids[i][0] = rank;
        }
        else
        {
            if(member_ids[i][0] == previous_fitness)
            {
                previous_fitness = member_ids[i][0];
                member_ids[i][0] = rank;
            }
            else
            {
                previous_fitness = member_ids[i][0];
                member_ids[i][0] = ++rank;
            }
        }
    }

    sum_rank = 0;
    for(int i = 0; i < options.population_size; i++)
        sum_rank = sum_rank + member_ids[i][0];

    srand(options.random_seed + srand_offset);
    double random_fraction = (double)rand()/RAND_MAX;
    double limits[options.population_size];

    limits[0] = member_ids[0][0]/sum_rank;

    for(int i = 1; i < options.population_size; i++)
        limits[i] = limits[i-1] + member_ids[i][0]/sum_rank;

    for(int i = 0; i < options.population_size; i++)
    {
        if(random_fraction <= limits[i])
            return i;
    }

    return -1;
}

void Population::xover_mutate(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    for(int i = 0; i < options.chromosome_length; i++)
    {
        child_1->get_chromosome()[i] = parent_1->get_chromosome()[i];
        child_2->get_chromosome()[i] = parent_2->get_chromosome()[i];
    }
   
    int index = -1;
    if(flip(options.probability_x, options.random_seed, srand_offset))
    {
        // ONE POINT XOVER
        // index = one_point_xover(parent_1, parent_2, child_1, child_2, srand_offset);

        // PMX
        pmx(parent_1, parent_2, child_1, child_2, srand_offset);
    }

    // SWAP MUTATE
    child_1->swap_mutate(options.probability_mutation, options.random_seed, srand_offset);
    child_2->swap_mutate(options.probability_mutation, options.random_seed, srand_offset + rand());
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

// THIS PMX FUNCTION ASSUMES THAT CHILD_1/CHILD_2 IS ALREADY A COPY OF PARENT_1/PARENT_2
void Population::pmx(Individual* parent_1, Individual* parent_2, Individual* child_1, Individual* child_2, int srand_offset)
{
    int index_1 = random_index_in_range(0, options.chromosome_length, options.random_seed, srand_offset);

    int index_2 = -1;
    if(index_1 != options.chromosome_length - 1)
    {
        index_2 = random_index_in_range(index_1, options.chromosome_length - 1, options.random_seed, srand_offset);
        index_2 += 1; //ENSURES ITS AT LEAST ONE INDEX FURTHER THAN INDEX_1
    }

    pmx_indices[0] = index_1;
    pmx_indices[1] = index_2;

    if(index_2 != -1)
    {
        // INDICES_ACCOUNTED_FOR WILL STORE INDICES OF ALLELES THAT HAVE ALREADY BEEN PROVIDED TO THE CHILD BY THE OPPOSITE PARENT
        int indices_accounted_1[400];
        int indices_accounted_2[400];

        // INDICES TO CHANGE WILL FIRST BE INITIALIZED WITH ALL 1s. ONCE INDICES ACCOUNTED FOR IS FILLED, THE ELEMENT IN INDICES_TO_CHANGE AT EACH ACCOUNTED_FOR INDEX WILL BE UPDATED TO -1
        int indices_to_change_1[400];
        int indices_to_change_2[400];

        int count_1 = 0;
        int count_2 = 0;
        for(int i = 0; i < options.chromosome_length; i++)
        {
            if(i >= (index_1 + 1) & i <= index_2)
            {
                indices_accounted_1[count_1++] = i;
                indices_accounted_2[count_2++] = i;
            }
            else
            {
                indices_accounted_1[i] = -1;
                indices_accounted_2[i] = -1;
            }
            
            
            indices_to_change_1[i] = 1;
            indices_to_change_2[i] = 1;
        }

        bool copy_1 = false;
        bool copy_2 = false;
        int compare_1 = -1;
        int compare_2 = -1;
        for(int j = index_1 + 1; j <= index_2; j++)
        {

            copy_1 = false;
            copy_2 = false;
            compare_1 = parent_1->get_chromosome()[j];
            compare_2 = parent_2->get_chromosome()[j];
            
            // CHILD_1 ALGORITHM PT2 (PLACES THE REMAINING NON-COPY VALUES OF THE PARENT_2 XOVER REGION IN THE CHILD_1 CHROMOSOME)
            for(int i = index_1 + 1; i <= index_2; i++)
            {
                if(compare_2 == parent_1->get_chromosome()[i])
                {
                    copy_1 = true;
                    break;
                }
            }
            if(!copy_1)
            {

                int value_to_swap = parent_1->get_chromosome()[j];
                
                one:
                for(int i = 0; i < options.chromosome_length; i++)
                {
                    if(parent_2->get_chromosome()[i] == value_to_swap)
                    {
                        if(i >= (index_1 + 1) && i <= index_2)
                        {
                            value_to_swap = parent_1->get_chromosome()[i];
                            goto one;
                        }
                        else
                        {
                            child_1->get_chromosome()[i] = compare_2;
                            indices_accounted_1[count_1++] = i;
                        }

                        break;
                    }
                }
            }
            // END CHILD_1 ALGORITHM PT2

            // CHILD_2 ALGORITHM PT2 (PLACES THE REMAINING NON-COPY VALUES OF THE PARENT_1 XOVER REGION IN THE CHILD_2 CHROMOSOME)
            for(int i = index_1 + 1; i <= index_2; i++)
            {
                if(compare_1 == parent_2->get_chromosome()[i])
                {
                    copy_2 = true;
                    break;
                }
            }
            if(!copy_2)
            {
                int value_to_swap = parent_2->get_chromosome()[j];
                
                two:
                for(int i = 0; i < options.chromosome_length; i++)
                {
                    if(parent_1->get_chromosome()[i] == value_to_swap)
                    {
                        if(i >= (index_1 + 1) && i <= index_2)
                        {
                            value_to_swap = parent_2->get_chromosome()[i];
                            goto two;
                        }
                        else
                        {
                            child_2->get_chromosome()[i] = compare_1;
                            indices_accounted_2[count_2++] = i;
                        }

                        break;
                    }
                }
            }
            //END CHILD_2 ALGORITHM PT2
        } // END FOR

        // IDENTIFY REMAINING INDICES THAT NEED TO BE XOVER'D FROM PARENT TO OPPOSITE CHILD
        for(int i = 0; i < count_1; i++) //COUNT_1 == COUNT_2 IS ALWAYS TRUE
        {
            indices_to_change_1[indices_accounted_1[i]] = -1;
            indices_to_change_2[indices_accounted_2[i]] = -1;
        }
        for(int i = 0; i < options.chromosome_length; i++)
        {
            if(indices_to_change_1[i] == 1)
                child_1->get_chromosome()[i] = parent_2->get_chromosome()[i];
            
            if(indices_to_change_2[i] == 1)
                child_2->get_chromosome()[i] = parent_1->get_chromosome()[i];
        }
    }
    else // IF INDEX_1 IS THE 2ND TO LAST INDEX OF THE CHROMOSOME, RESULTS IN ONLY SWAPPING THE VERY LAST ALLELE OF THE CHROMOSOME
    {
        child_1->get_chromosome()[index_1 + 1] = parent_2->get_chromosome()[index_1 + 1];
        child_2->get_chromosome()[index_1 + 1] = parent_1->get_chromosome()[index_1 + 1];
    }
}


void Population::CHC_generation(Population* child, Population *temp, int srand_offset)
{
    // TEST
    char temp_c;

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
            members[index].set_fitness(-1);
        }
        else
        {
            temp->members[j] = child->members[index - options.population_size];
            child->members[index - options.population_size].set_fitness(-1);
        }


    }

    child->copy_members_and_update_id(*temp);
    child->rank_selection_sort(options.random_seed, srand_offset);
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

// TEST
void Population::print_member_ids()
{
    for(int i = 0; i < options.population_size; i++)
    {
        std::cout << std::fixed << std::setprecision(2) << "(" << member_ids[i][0] << "," << std::setprecision(0) << member_ids[i][1] << ") ";
    }
    std::cout << std::endl;
}

// TEST
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