#include "ga.h"
#include "test.h"

// TEST
#include "options.h"

// CB 10/20/23: THIS PROGRAM BREAKS IF I INSTANTIATE 2 POPULATION OBJECTS STATICALLY, BUT DOES NOT BREAK IF THEY ARE INSTANTIATED DYNAMICALLY. STATICALLY ALLOCATING A SINGLE POPULATION OBJECT DOESN'T BREAK THE PROGRAM. WHY?
int main(int argc, char* argv[])
{
    //TEST: SRAND/RADN
    // srand(time(NULL));
    // std::cout << "1st rand(same seed) = " << rand() << std::endl;
    // std::cout << "2nd rand(same seed) = " << rand() << std::endl;
    // srand(time(NULL));
    // std::cout << "1st rand(dif seed) = " << rand() << std::endl;
    // srand(time(NULL) + 1);
    // std::cout << "2nd rand(dif seed) = " << rand() << std::endl;
    // TEST
    Options options;
    options.random_seed = 1;
    options.population_size = 2;
    options.chromosome_length = 20;
    options.probability_x = 1;
    options.probability_mutation = 0;
    Individual* ind_1 = new Individual[2];
    Individual* ind_2 = new Individual[2];

    int chrom_1[20] = {3,17,13,9,2,10,6,12,11,7,15,18,16,1,4,0,5,14,8,19};
    int chrom_2[20] = {16,1,4,0,5,14,8,19,6,9,2,13,11,17,15,10,7,3,18,12};
    ind_1[0].set_chromosome(20,chrom_1);
    ind_1[1].set_chromosome(20,chrom_2);
    ind_2[0].set_chromosome(20,chrom_1);
    ind_2[1].set_chromosome(20,chrom_2);
    Population* pop = new Population;
    Population* child = new Population;
    pop->set_members_ptr(ind_1);
    pop->set_options(options);
    child->set_members_ptr(ind_2);
    child->set_options(options);
    std::cout << "BEFORE::POP MEMBERS:\n";
    pop->print_pop();
    std::cout << "BEFORE::CHILD MEMBERS:\n";
    child->print_pop();
    pop->pmx(&pop->get_members()[0],&pop->get_members()[1],&child->get_members()[0],&child->get_members()[1],1);

    int temp[2];
    temp[0] = pop->get_pmx_indices()[0];
    temp[1] = pop->get_pmx_indices()[1];

    std::cout << "MAIN:: PMX indicies:" << std::endl;
    std::cout << "index_1 = " << temp[0] << std::endl;
    std::cout << "index_2 = " << temp[1] << std::endl;
    std::cout << std::endl;

    std::cout << "AFTER::POP MEMBERS:\n";
    pop->print_pop();
    std::cout << "AFTER::CHILD MEMBERS:\n";
    child->print_pop();



    /////////////////////////////////////
    /////////////////////////////////////
    // EVERYTHING BELOW HERE IS REAL!!!!

    // std::cout << "If report is needed, must set argv[1] = 1; otherwise reporting is skipped." << std::endl;
    // std::cout << "If multiple runs are needed, must set argv[2] = #runs; 1 run by default." << std::endl;
    // std::cout << "GA type is CHC by default. If a different version is required, set argv[3] to one of the following options:" << std::endl;
    // std::cout << "  1. Simple GA" << std::endl;
    // std::cout << "  2. Simple GA w/extinction event" << std::endl;
    // std::cout << "  3. CHC" << std::endl;
    // std::cout << "  4. CHC w/extinction event" << std::endl;
    // std::cout << "If runtime change to mutation probability is required, set argv[4] = mutation probability." << std::endl;
    // std::cout << "  - Note: Currently, argv[4] will take an interger and divide it by 10 to get the actual mutation probability)" << std::endl;
    // std::cout << "      - e.g. argv[4] = 1 converts to mutation_probability = 0.1" << std::endl;
    // std::cout << "If runtime change to xover probability is required, set argv[5] = xover probability." << std::endl;
    // std::cout << "  - Note: Currently, argv[5] will take an interger and divide it by 10 to get the actual mutation probability)" << std::endl;
    // std::cout << "      - e.g. argv[5] = 1 converts to xover_probability = 0.1" << std::endl;
    // std::cout << "  - Note: If no runtime change to mutation probability is required, you must set argv[4] = -1" << std::endl;

    // int report_option = 0;
    // int runs = 1;
    // int ga_variant_option = 3;
    // double mutation_probability = -1;
    // double xover_probability = -1;
    // int eval_option = 1;
    
    // if(argc == 2)
    // {
    //     report_option = std::stoi(argv[1]);
    //     if(report_option != 0 && report_option != 1)
    //     {
    //         std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
    //         std::cout << "Switching to no reporting by default" << std::endl;
    //         report_option = 0;
    //     }
    // }
    
    // if(argc == 3)
    // {
    //     report_option = std::stoi(argv[1]);
    //     if(report_option != 0 && report_option != 1)
    //     {
    //         std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
    //         std::cout << "Switching to no reporting by default" << std::endl;
    //         report_option = 0;
    //     }

    //     runs = std::stoi(argv[2]);
    //     if(runs <= 0 || runs > 10)
    //     {
    //         std::cout << "Can only choose up to 10 runs maximum" << std::endl;
    //         std::cout << "Switching to 1 run by default" << std::endl;
    //         runs = 1;
    //     }
    // }
    
    // if(argc == 4)
    // {
    //     report_option = std::stoi(argv[1]);
    //     if(report_option != 0 && report_option != 1)
    //     {
    //         std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
    //         std::cout << "Switching to no reporting by default" << std::endl;
    //         report_option = 0;
    //     }

    //     runs = std::stoi(argv[2]);
    //     if(runs <= 0 || runs > 10)
    //     {
    //         std::cout << "Can only choose up to 10 runs maximum" << std::endl;
    //         std::cout << "Switching to 1 run by default" << std::endl;
    //         runs = 1;
    //     }

    //     ga_variant_option = std::stoi(argv[3]);
    //     if(ga_variant_option <= 0 || ga_variant_option > 4)
    //     {
    //         std::cout << "List of available variants" << std::endl;
    //         std::cout << "1. Simple GA" << std::endl;
    //         std::cout << "2. Simple GA w/extinction event" << std::endl;
    //         std::cout << "3. CHC" << std::endl;
    //         std::cout << "4. CHC w/extinction event" << std::endl;
    //         std::cout << "Switching to option 3 (CHC) by default" << std::endl;
    //         runs = 1;
    //         ga_variant_option = 3;
    //     }
    // }
    
    // if(argc == 5)
    // {
    //     report_option = std::stoi(argv[1]);
    //     if(report_option != 0 && report_option != 1)
    //     {
    //         std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
    //         std::cout << "Switching to no reporting by default" << std::endl;
    //         report_option = 0;
    //     }

    //     runs = std::stoi(argv[2]);
    //     if(runs <= 0 || runs > 10)
    //     {
    //         std::cout << "Can only choose up to 10 runs maximum" << std::endl;
    //         std::cout << "Switching to 1 run by default" << std::endl;
    //         runs = 1;
    //     }
        
    //     ga_variant_option = std::stoi(argv[3]);
    //     if(ga_variant_option <= 0 || ga_variant_option > 4)
    //     {
    //         std::cout << "List of available variants" << std::endl;
    //         std::cout << "1. Simple GA" << std::endl;
    //         std::cout << "2. Simple GA w/extinction event" << std::endl;
    //         std::cout << "3. CHC" << std::endl;
    //         std::cout << "4. CHC w/extinction event" << std::endl;
    //         std::cout << "Switching to option 3 (CHC) by default" << std::endl;
    //         ga_variant_option = 3;
    //     }

    //     mutation_probability = std::strtod(argv[4], NULL);
    //     mutation_probability /= 10;
    //     if(mutation_probability <= 0 || mutation_probability >= 1)
    //     {
    //         std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
    //         mutation_probability = -1;
    //     }
    // }
    
    // if(argc == 6)
    // {
    //     report_option = std::stoi(argv[1]);
    //     if(report_option != 0 && report_option != 1)
    //     {
    //         std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
    //         std::cout << "Switching to no reporting by default" << std::endl;
    //         report_option = 0;
    //     }

    //     runs = std::stoi(argv[2]);
    //     if(runs <= 0 || runs > 10)
    //     {
    //         std::cout << "Can only choose up to 10 runs maximum" << std::endl;
    //         std::cout << "Switching to 1 run by default" << std::endl;
    //         runs = 1;
    //     }
        
    //     ga_variant_option = std::stoi(argv[3]);
    //     if(ga_variant_option <= 0 || ga_variant_option > 4)
    //     {
    //         std::cout << "List of available variants" << std::endl;
    //         std::cout << "1. Simple GA" << std::endl;
    //         std::cout << "2. Simple GA w/extinction event" << std::endl;
    //         std::cout << "3. CHC" << std::endl;
    //         std::cout << "4. CHC w/extinction event" << std::endl;
    //         std::cout << "Switching to option 3 (CHC) by default" << std::endl;
    //         ga_variant_option = 3;
    //     }
        
    //     mutation_probability = std::strtod(argv[4], NULL);
    //     mutation_probability /= 10;
    //     if(mutation_probability <= 0 || mutation_probability >= 1)
    //     {
    //         std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
    //         mutation_probability = -1;
    //     }
        
    //     xover_probability = std::strtod(argv[5], NULL);
    //     xover_probability /= 10;
    //     if(xover_probability <= 0 || xover_probability >= 1)
    //     {
    //         std::cout << "Xover probability can only be given between 0 - 1" << std::endl;
    //         xover_probability = -1;
    //     }
    // }

    // switch(ga_variant_option)
    // {
    //     case 1:
    //         std::cout << "Simple GA\n";
    //         break;
    //     case 2:
    //         std::cout << "Simple GA w/extinction\n";
    //         break;
    //     case 3:
    //         std::cout << "CHC\n";
    //         break;
    //     case 4:
    //         std::cout << "CHC w/extinction\n";
    //         break;
    // }

    // for(int j = 0; j < runs; j++)
    // {

    //     GA ga(argc, argv, eval_option, j, ga_variant_option, mutation_probability, xover_probability);
        
    //     switch(ga_variant_option)
    //     {

    //         case 1:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 ga.set_option_xover_prob(xover_probability);
    //                 ga.set_option_mutation_prob(mutation_probability);
                    
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "S_probM-" + temp_2 + "S_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             else
    //             {
    //                 // ga.set_option_xover_prob(0.667);
    //                 // if(argc == 5 && mutation_probability != -1)
    //                 // {
    //                 //     ga.set_option_mutation_prob(mutation_probability);
                        
    //                 //     std::stringstream ss;
    //                 //     std::string temp_1;
    //                 //     ss.precision(2);
    //                 //     ss << mutation_probability;
    //                 //     ss >> temp_1;
    //                 //     std::string temp_2 = "S_probM-" + temp_1;
    //                 //     ga.set_option_ga_variant_name(temp_2);
    //                 // }
    //                 // else if(argc < 5)
    //                 // {
    //                     ga.set_option_mutation_prob(0.01);
    //                     ga.set_option_xover_prob(0.667);
    //                     ga.set_option_ga_variant_name("S");
    //                 // }
    //                 ga.set_file_names(j);
    //             }
    //             break;
    //         case 2:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 ga.set_option_xover_prob(xover_probability);
    //                 ga.set_option_mutation_prob(mutation_probability);
                    
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "S-E_probM-" + temp_2 + "S-E_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // ga.set_option_xover_prob(0.667);
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     ga.set_option_mutation_prob(mutation_probability);
                    
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "S-E_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             // else if(argc < 5)
    //             else
    //             {
    //                 ga.set_option_mutation_prob(0.01);
    //                 ga.set_option_xover_prob(0.667);
    //                 ga.set_option_ga_variant_name("S-E"); // THIS NAME IS BEING USED TO TRIGGER PROPER EXTINCTION_EVENT
    //             }
    //             ga.set_file_names(j);
    //             ga.set_option_extinction_delay(50);
    //             ga.set_option_convergence_resolution_threshold(0.02);
    //             break;
    //         case 3:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 ga.set_option_xover_prob(xover_probability);
    //                 ga.set_option_mutation_prob(mutation_probability);
                    
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "CHC_probM-" + temp_2 + "CHC_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // ga.set_option_xover_prob(0.99);
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     ga.set_option_mutation_prob(mutation_probability);
                    
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "CHC_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             // else if(argc < 5)
    //             else
    //             {
    //                 //TEST
    //                 std::cout << "::MAIN:: SETTING CHC OPTIONS\n\n";

    //                 ga.set_option_mutation_prob(0.1);
    //                 ga.set_option_xover_prob(0.5);
    //                 ga.set_option_ga_variant_name("CHC");
    //             }
    //             ga.set_file_names(j);
    //             break;
    //         case 4:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 ga.set_option_xover_prob(xover_probability);
    //                 ga.set_option_mutation_prob(mutation_probability);
                    
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "CHC-E_probM-" + temp_2 + "CHC-E_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // ga.set_option_xover_prob(0.99);
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     ga.set_option_mutation_prob(mutation_probability);
                    
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "CHC-E_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             // else if(argc < 5)
    //             else
    //             {
    //                 ga.set_option_mutation_prob(0.1);
    //                 ga.set_option_xover_prob(0.5);
    //                 ga.set_option_ga_variant_name("CHC-E");
    //             }
    //             ga.set_file_names(j);
    //             break;
    //     }

    //     try
    //         {ga.init(eval_option, report_option);}
    //     catch(double variable_value[])
    //     {

    //         //TEST
    //         std::cout << "INIT " << j << std::endl;

    //         switch((int)variable_value[0] + 1)
    //         {
    //             case 1:
    //                 std::cout << "Living room max width ("<<ga.get_options().max_variable_value[0]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 2:
    //                 std::cout << "Kitchen max length ("<<ga.get_options().max_variable_value[1]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 3:
    //                 std::cout << "Kitchen max width ("<<ga.get_options().max_variable_value[2]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 4:
    //                 std::cout << "Hall max width ("<<ga.get_options().max_variable_value[3]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 5:
    //                 std::cout << "Bed 1 max width ("<<ga.get_options().max_variable_value[4]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 6:
    //                 std::cout << "Bed 2 max width ("<<ga.get_options().max_variable_value[5]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 7:
    //                 std::cout << "Bed 3 max width ("<<ga.get_options().max_variable_value[6]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //         }
    //     }

    //     try
    //         {ga.run(eval_option, report_option);}
    //     catch(double variable_value[])
    //     {

    //         //TEST
    //         std::cout << "RUN " << j << std::endl; 

    //         switch((int)variable_value[0] + 1)
    //         {
    //             case 1:
    //                 std::cout << "Living room max width ("<<ga.get_options().max_variable_value[0]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 2:
    //                 std::cout << "Kitchen max length ("<<ga.get_options().max_variable_value[1]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 3:
    //                 std::cout << "Kitchen max width ("<<ga.get_options().max_variable_value[2]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 4:
    //                 std::cout << "Hall max width ("<<ga.get_options().max_variable_value[3]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 5:
    //                 std::cout << "Bed 1 max width ("<<ga.get_options().max_variable_value[4]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 6:
    //                 std::cout << "Bed 2 max width ("<<ga.get_options().max_variable_value[5]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //             case 7:
    //                 std::cout << "Bed 3 max width ("<<ga.get_options().max_variable_value[6]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
    //                 return EXIT_FAILURE;
    //         }
    //     }
    //     catch(std::string xover_mutate_test)
    //     {
    //         std::cout << xover_mutate_test << std::endl;
            
    //         //TEST
    //         // char temp;
    //         // std::cin >> temp;
    //         // sleep(2);

    //         //REAL
    //         return EXIT_FAILURE;
    //     }
        
    //     // count++;
    // }

    // // FILENAME SETUP FOR REPORT AVERAGER (REPORT AVERAGER RUNS AFTER FILENAME SETUP)
    // if(report_option == 1)
    // {
    //     GA ga(argc, argv, eval_option, runs, ga_variant_option, mutation_probability, xover_probability);
    //     switch(ga_variant_option)
    //     {
    //         case 1:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "S_probM-" + temp_2 + "S_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "S_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             else
    //             {
    //                 ga.set_option_ga_variant_name("S");
    //             }
    //             break;
    //         case 2:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "S-E_probM-" + temp_2 + "S-E_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "S-E_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             else
    //             {
    //                 ga.set_option_ga_variant_name("S-E"); // THIS NAME IS BEING USED TO TRIGGER PROPER EXTINCTION_EVENT
    //             }
    //             break;
    //         case 3:
    //         if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //         {
    //             std::stringstream ss;
    //             std::string temp_1;
    //             std::string temp_2;
    //             ss.precision(2);
    //             ss << xover_probability;
    //             ss >> temp_1;
    //             ss.clear();
    //             ss << mutation_probability;
    //             ss >> temp_2;
    //             std::string temp_3 = "CHC_probM-" + temp_2 + "CHC_probX-" + temp_1;
    //             ga.set_option_ga_variant_name(temp_3);
    //         }
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "CHC_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             else
    //             {
    //                 ga.set_option_ga_variant_name("CHC");
    //             }
    //             break;
    //         case 4:
    //             if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
    //             {
    //                 std::stringstream ss;
    //                 std::string temp_1;
    //                 std::string temp_2;
    //                 ss.precision(2);
    //                 ss << xover_probability;
    //                 ss >> temp_1;
    //                 ss.clear();
    //                 ss << mutation_probability;
    //                 ss >> temp_2;
    //                 std::string temp_3 = "CHC-E_probM-" + temp_2 + "CHC-E_probX-" + temp_1;
    //                 ga.set_option_ga_variant_name(temp_3);
    //             }
    //             // if(argc == 5 && mutation_probability != -1)
    //             // {
    //             //     std::stringstream ss;
    //             //     std::string temp_1;
    //             //     ss.precision(2);
    //             //     ss << mutation_probability;
    //             //     ss >> temp_1;
    //             //     std::string temp_2 = "CHC-E_probM-" + temp_1;
    //             //     ga.set_option_ga_variant_name(temp_2);
    //             // }
    //             else
    //             {
    //                 ga.set_option_ga_variant_name("CHC-E");
    //             }
    //             break;
    //     }
    //     ga.report_averager(runs);
    // }
}