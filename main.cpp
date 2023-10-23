#include "ga.h"
#include "test.h"

// TEST
#include "options.h"

// CB 10/20/23: THIS PROGRAM BREAKS IF I INSTANTIATE 2 POPULATION OBJECTS STATICALLY, BUT DOES NOT BREAK IF THEY ARE INSTANTIATED DYNAMICALLY. STATICALLY ALLOCATING A SINGLE POPULATION OBJECT DOESN'T BREAK THE PROGRAM. WHY?
int main(int argc, char* argv[])
{
    std::cout << "* argv[1]" << std::endl;
    std::cout << "* TSP filename must be given as argv[1]." << std::endl << std::endl;
    std::cout << "* argv[2]" << std::endl;
    std::cout << "* If a single runtime options modifcation is needed, set argv[2] = 0." << std::endl;
    std::cout << "* If mulitple runtime options modifcations are needed, set argv[2] = 1." << std::endl;
    std::cout << "* If no argv[2] is given, the program defaults to no modifcations." << std::endl;
    std::cout << "* If no argv[2] is given, the program defaults to no modifcations." << std::endl << std::endl;
    std::cout << "* argv[3]" << std::endl;
    std::cout << "* If single runtime modification is needed, set argv[3] equal to one of the following options:" << std::endl;
    std::cout << "    1. 0 to disable reporting, 1 to enable reporting " << std::endl;
    std::cout << "    2. # of runs" << std::endl;
    std::cout << "    3. GA type given by the following:" << std::endl;
    std::cout << "      1. Simple GA" << std::endl;
    std::cout << "      2. Simple GA w/extinction event" << std::endl;
    std::cout << "      3. CHC" << std::endl;
    std::cout << "      4. CHC w/extinction event" << std::endl << std::endl;
    std::cout << "    4. mutation probability" << std::endl;
    std::cout << "    5. xover probability" << std::endl << std::endl;
    std::cout << "** argv[3] alternate instructions **" << std::endl;
    std::cout << "* If argv[2] = 1 (multiple option modifcations), then argv assignment instructions are given as follows:" << std::endl << std::endl;
    std::cout << "* argv[3]" << std::endl;
    std::cout << "* If report is needed, must set argv[3] = 1; otherwise reporting is skipped." << std::endl << std::endl;
    std::cout << "* argv[4]" << std::endl;
    std::cout << "* If multiple runs are needed, must set argv[4] = #runs; 1 run by default." << std::endl << std::endl;
    std::cout << "* argv[5]" << std::endl;
    std::cout << "* GA type is CHC by default. If a different version is required, set argv[5] to one of the following options:" << std::endl;
    std::cout << "    1. Simple GA" << std::endl;
    std::cout << "    2. Simple GA w/extinction event" << std::endl;
    std::cout << "    3. CHC" << std::endl;
    std::cout << "    4. CHC w/extinction event" << std::endl << std::endl;
    std::cout << "* argv[6]" << std::endl;
    std::cout << "* If runtime change to mutation probability is required, set argv[6] = mutation probability." << std::endl;
    std::cout << "   - Note: Currently, argv[6] will take an interger and divide it by 10 to get the actual mutation probability)" << std::endl;
    std::cout << "      - e.g. argv[6] = 1 converts to mutation_probability = 0.1" << std::endl << std::endl;
    std::cout << "* argv[7]" << std::endl;
    std::cout << "* If runtime change to xover probability is required, set argv[7] = xover probability." << std::endl;
    std::cout << "   - Note: Currently, argv[7] will take an interger and divide it by 10 to get the actual mutation probability)" << std::endl;
    std::cout << "      - e.g. argv[7] = 1 converts to xover_probability = 0.1" << std::endl;
    std::cout << "   - Note: If no runtime change to mutation probability is required, you must set argv[6] = -1" << std::endl << std::endl;

    int report_option = 0;
    int runs = 1;
    int ga_variant_option = 3;
    double mutation_probability = -1;
    double xover_probability = -1;

    if(argc == 1)
    {
        std::cout << "TSP filename must be given as argv[1]. Aborting." << std::endl;
        return EXIT_FAILURE;
    }

    if(argc == 2)
    {
        std::cout << "No runtime modifcations given. Program running in default mode." << std::endl;
    }

    if(argc == 4 && argv[2] == "0")
    {
        

        int option_modification = std::atoi(argv[3]);
        switch(option_modification)
        {
            case 1:
                report_option = option_modification;
                break;
            case 2:
                runs = option_modification;
                break;
            case 3:
                ga_variant_option = option_modification;
                break;
            case 4:
                mutation_probability = std::strtod(argv[3], NULL);
                break;
            case 5:
                xover_probability = std::strtod(argv[3], NULL);
                break;
        }
    }
    
    if(argc == 4 && std::stoi(argv[2]) == 1)
    {
        report_option = std::stoi(argv[3]);
        if(report_option != 0 && report_option != 1)
        {
            std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
            std::cout << "Switching to no reporting by default" << std::endl;
            report_option = 0;
        }
        else
            std::cout << "Setting report option = " << report_option << std::endl;
    }
    
    if(argc == 5 && std::stoi(argv[2]) == 1)
    {
        report_option = std::stoi(argv[3]);
        if(report_option != 0 && report_option != 1)
        {
            std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
            std::cout << "Switching to no reporting by default" << std::endl;
            report_option = 0;
        }
        else
            std::cout << "Setting report option = " << report_option << std::endl;

        runs = std::stoi(argv[4]);
        if(runs <= 0 || runs > 30)
        {
            std::cout << "Can only choose up to 30 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
        else
            std::cout << "Setting # of runs = " << runs << std::endl;
    }
    
    if(argc == 6 && std::stoi(argv[2]) == 1)
    {
        report_option = std::stoi(argv[3]);
        if(report_option != 0 && report_option != 1)
        {
            std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
            std::cout << "Switching to no reporting by default" << std::endl;
            report_option = 0;
        }
        else
            std::cout << "Setting report option = " << report_option << std::endl;

        runs = std::stoi(argv[4]);
        if(runs <= 0 || runs > 30)
        {
            std::cout << "Can only choose up to 30 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
        else
            std::cout << "Setting # of runs = " << runs << std::endl;

        ga_variant_option = std::stoi(argv[5]);
        if(ga_variant_option <= 0 || ga_variant_option > 4)
        {
            std::cout << "List of available variants" << std::endl;
            std::cout << "1. Simple GA" << std::endl;
            std::cout << "2. Simple GA w/extinction event" << std::endl;
            std::cout << "3. CHC" << std::endl;
            std::cout << "4. CHC w/extinction event" << std::endl;
            std::cout << "Switching to option 3 (CHC) by default" << std::endl;
            runs = 1;
            ga_variant_option = 3;
        }
        else
            std::cout << "Setting ga variant option = " << ga_variant_option << std::endl;
    }
    
    if(argc == 7  && std::stoi(argv[2]) == 1)
    {
        report_option = std::stoi(argv[3]);
        if(report_option != 0 && report_option != 1)
        {
            std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
            std::cout << "Switching to no reporting by default" << std::endl;
            report_option = 0;
        }
        else
            std::cout << "Setting report option = " << report_option << std::endl;

        runs = std::stoi(argv[4]);
        if(runs <= 0 || runs > 30)
        {
            std::cout << "Can only choose up to 30 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
        else
            std::cout << "Setting # of runs = " << runs << std::endl;
        
        ga_variant_option = std::stoi(argv[5]);
        if(ga_variant_option <= 0 || ga_variant_option > 4)
        {
            std::cout << "List of available variants" << std::endl;
            std::cout << "1. Simple GA" << std::endl;
            std::cout << "2. Simple GA w/extinction event" << std::endl;
            std::cout << "3. CHC" << std::endl;
            std::cout << "4. CHC w/extinction event" << std::endl;
            std::cout << "Switching to option 3 (CHC) by default" << std::endl;
            ga_variant_option = 3;
        }
        else
            std::cout << "Setting ga variant option = " << ga_variant_option << std::endl;

        mutation_probability = std::strtod(argv[6], NULL);
        if(mutation_probability <= 0 || mutation_probability >= 1)
        {
            std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
            mutation_probability = -1;
        }
        else
            std::cout << "Setting mutation probability = " << mutation_probability << std::endl;

    }
    
    if(argc == 8 && std::stoi(argv[2]) == 1)
    {
        report_option = std::stoi(argv[3]);
        if(report_option != 0 && report_option != 1)
        {
            std::cout << "Can only choose 0 or 1 as a report option (reporting or no reporting, respectively)" << std::endl;
            std::cout << "Switching to no reporting by default" << std::endl;
            report_option = 0;
        }
        else
            std::cout << "Setting report option = " << report_option << std::endl;

        runs = std::stoi(argv[4]);
        if(runs <= 0 || runs > 30)
        {
            std::cout << "Can only choose up to 30 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
        else
            std::cout << "Setting # of runs = " << runs << std::endl;
        
        ga_variant_option = std::stoi(argv[5]);
        if(ga_variant_option <= 0 || ga_variant_option > 4)
        {
            std::cout << "List of available variants" << std::endl;
            std::cout << "1. Simple GA" << std::endl;
            std::cout << "2. Simple GA w/extinction event" << std::endl;
            std::cout << "3. CHC" << std::endl;
            std::cout << "4. CHC w/extinction event" << std::endl;
            std::cout << "Switching to option 3 (CHC) by default" << std::endl;
            ga_variant_option = 3;
        }
        else
            std::cout << "Setting ga variant option = " << ga_variant_option << std::endl;
        
        mutation_probability = std::strtod(argv[6], NULL);
        if(mutation_probability <= 0 || mutation_probability >= 1)
        {
            std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
            mutation_probability = -1;
        }
        else
            std::cout << "Setting mutation probability = " << mutation_probability << std::endl;
        
        xover_probability = std::strtod(argv[7], NULL);
        if(xover_probability <= 0 || xover_probability >= 1)
        {
            std::cout << "Xover probability can only be given between 0 - 1" << std::endl;
            xover_probability = -1;
        }
        else
            std::cout << "Setting xover probability = " << xover_probability << std::endl;
    }

    switch(ga_variant_option)
    {
        case 1:
            std::cout << "Simple GA\n";
            break;
        case 2:
            std::cout << "Simple GA w/extinction\n";
            break;
        case 3:
            std::cout << "CHC\n";
            break;
        case 4:
            std::cout << "CHC w/extinction\n";
            break;
    }

    for(int j = 0; j < runs; j++)
    {
        try
        {
            GA ga(argc, argv, j, ga_variant_option, mutation_probability, xover_probability);
        
            switch(ga_variant_option)
            {

                case 1: // NOT UPDATED FOR ARGC = 8 && MUTATION_PROB == -1
                    if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                    {
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "S_probM-" + temp_2 + "S_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else if(argc == 8 && xover_probability != -1 && mutation_probability == -1)
                    {
                        mutation_probability = 0.01;
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "S_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else
                    {
                        if(argc == 7 && mutation_probability != -1)
                        {
                            xover_probability = 0.677;
                            ga.set_option_mutation_prob(mutation_probability);
                            ga.set_option_xover_prob(xover_probability);
                            
                            std::stringstream ss;
                            std::string temp_1;
                            std::string temp_3;
                            ss.precision(2);
                            ss << mutation_probability;
                            ss >> temp_1;
                            ss.clear();
                            ss << xover_probability;
                            ss >> temp_3;
                            std::string temp_2 = "S_probM-" + temp_1 + "_probX-" + temp_3;
                            ga.set_option_ga_variant_name(temp_2);
                        }
                        else
                        {
                            ga.set_option_mutation_prob(0.01);
                            ga.set_option_xover_prob(0.667);
                            ga.set_option_ga_variant_name("S");
                        }
                    }
                    ga.set_file_names(j);
                    break;
                case 2: // NOT UPDATED FOR ARGC = 8 && MUTATION_PROB == -1
                    if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                    {
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "S-E_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else if(argc == 8 && xover_probability != -1 && mutation_probability == -1)
                    {
                        mutation_probability = 0.01;
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "S-E_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else
                    {
                        if(argc == 7 && mutation_probability != -1)
                        {
                            ga.set_option_mutation_prob(mutation_probability);
                            ga.set_option_xover_prob(0.667);
                            
                            std::stringstream ss;
                            std::string temp_1;
                            std::string temp_3;
                            ss.precision(2);
                            ss << mutation_probability;
                            ss >> temp_1;
                            ss.clear();
                            ss << xover_probability;
                            ss >> temp_3;
                            std::string temp_2 = "S-E_probM-" + temp_1 + "_probX-" + temp_3;
                            ga.set_option_ga_variant_name(temp_2);
                        }
                        else
                        {
                            ga.set_option_mutation_prob(0.01);
                            ga.set_option_xover_prob(0.667);
                            ga.set_option_ga_variant_name("S-E"); // THIS NAME IS BEING USED TO TRIGGER PROPER EXTINCTION_EVENT
                        }
                    }
                    ga.set_file_names(j);
                    ga.set_option_extinction_delay(50);
                    ga.set_option_convergence_resolution_threshold(0.02);
                    break;
                case 3:
                    if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                    {
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "CHC_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else if(argc == 8 && xover_probability != -1 && mutation_probability == -1)
                    {
                        mutation_probability = 0.01;
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "CHC_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else
                    {
                        if(argc == 7 && mutation_probability != -1)
                        {
                            xover_probability = 0.5;
                            ga.set_option_mutation_prob(mutation_probability);
                            ga.set_option_xover_prob(xover_probability);
                            
                            std::stringstream ss;
                            std::string temp_1;
                            std::string temp_3;
                            ss.precision(2);
                            ss << mutation_probability;
                            ss >> temp_1;
                            ss.clear();
                            ss << xover_probability;
                            ss >> temp_3;
                            std::string temp_2 = "CHC_probM-" + temp_1 + "_probX-" + temp_3;
                            ga.set_option_ga_variant_name(temp_2);
                        }
                        else
                        {
                            ga.set_option_mutation_prob(0.01);
                            ga.set_option_xover_prob(0.5);
                            ga.set_option_ga_variant_name("CHC");
                        }
                    }
                    ga.set_file_names(j);
                    break;
                case 4:
                    if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                    {
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "CHC-E_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else if(argc == 8 && xover_probability != -1 && mutation_probability == -1)
                    {
                        mutation_probability = 0.01;
                        ga.set_option_xover_prob(xover_probability);
                        ga.set_option_mutation_prob(mutation_probability);
                        
                        std::stringstream ss;
                        std::string temp_1;
                        std::string temp_2;
                        ss.precision(2);
                        ss << xover_probability;
                        ss >> temp_1;
                        ss.clear();
                        ss << mutation_probability;
                        ss >> temp_2;
                        std::string temp_3 = "CHC-E_probM-" + temp_2 + "_probX-" + temp_1;
                        ga.set_option_ga_variant_name(temp_3);
                    }
                    else
                    {
                        if(argc == 7 && mutation_probability != -1)
                        {
                            xover_probability = 0.5;
                            ga.set_option_mutation_prob(mutation_probability);
                            ga.set_option_xover_prob(xover_probability);
                            
                            std::stringstream ss;
                            std::string temp_1;
                            std::string temp_3;
                            ss.precision(2);
                            ss << mutation_probability;
                            ss >> temp_1;
                            ss.clear();
                            ss << xover_probability;
                            ss >> temp_3;
                            std::string temp_2 = "CHC-E_probM-" + temp_1 + "_probX-" + temp_3;
                            ga.set_option_ga_variant_name(temp_2);
                        }
                        else
                        {
                            ga.set_option_mutation_prob(0.01);
                            ga.set_option_xover_prob(0.5);
                            std::string temp_1(argv[1]);
                            ga.set_option_ga_variant_name(temp_1 + "_CHC-E");
                            if(temp_1 == "burma14.tsp")
                                ga.set_eval_option(2);
                            else
                                ga.set_eval_option(1);
                        }
                    }
                    ga.set_file_names(j);
                    break;
            }

            int eval_option = ga.get_options().eval_option;

            try
                {ga.init(eval_option, report_option);}
            catch(double variable_value[])
            {

                //TEST
                std::cout << "INIT " << j << std::endl;

                switch((int)variable_value[0] + 1)
                {
                    case 1:
                        std::cout << "Living room max width ("<<ga.get_options().max_variable_value[0]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 2:
                        std::cout << "Kitchen max length ("<<ga.get_options().max_variable_value[1]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 3:
                        std::cout << "Kitchen max width ("<<ga.get_options().max_variable_value[2]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 4:
                        std::cout << "Hall max width ("<<ga.get_options().max_variable_value[3]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 5:
                        std::cout << "Bed 1 max width ("<<ga.get_options().max_variable_value[4]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 6:
                        std::cout << "Bed 2 max width ("<<ga.get_options().max_variable_value[5]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 7:
                        std::cout << "Bed 3 max width ("<<ga.get_options().max_variable_value[6]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                }
            }
            catch(std::string error_message)
            {
                throw(error_message);
            }

            try
                {ga.run(eval_option, report_option);}
            catch(double variable_value[])
            {

                //TEST
                std::cout << "RUN " << j << std::endl; 

                switch((int)variable_value[0] + 1)
                {
                    case 1:
                        std::cout << "Living room max width ("<<ga.get_options().max_variable_value[0]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 2:
                        std::cout << "Kitchen max length ("<<ga.get_options().max_variable_value[1]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 3:
                        std::cout << "Kitchen max width ("<<ga.get_options().max_variable_value[2]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 4:
                        std::cout << "Hall max width ("<<ga.get_options().max_variable_value[3]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 5:
                        std::cout << "Bed 1 max width ("<<ga.get_options().max_variable_value[4]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 6:
                        std::cout << "Bed 2 max width ("<<ga.get_options().max_variable_value[5]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                    case 7:
                        std::cout << "Bed 3 max width ("<<ga.get_options().max_variable_value[6]<<") exceeded @ "<<variable_value[1]<<". Exiting..."<< std::endl;
                        return EXIT_FAILURE;
                }
            }
            catch(std::string error_message)
            {
                std::cout << error_message << std::endl;
                return EXIT_FAILURE;
            }
        }
        catch (std::string error_message)
        {
            std::cout << error_message << std::endl;
            return EXIT_FAILURE;
        }
    }

    // FILENAME SETUP FOR REPORT AVERAGER (REPORT AVERAGER RUNS AFTER FILENAME SETUP)
    if(report_option == 1)
    {
        GA ga(argc, argv, runs, ga_variant_option, mutation_probability, xover_probability);
        switch(ga_variant_option)
        {
            case 1:
                if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                {
                    std::stringstream ss;
                    std::string temp_1;
                    std::string temp_2;
                    ss.precision(2);
                    ss << xover_probability;
                    ss >> temp_1;
                    ss.clear();
                    ss << mutation_probability;
                    ss >> temp_2;
                    std::string temp_3 = "S_probM-" + temp_2 + "_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "S_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                else
                {
                    ga.set_option_ga_variant_name("S");
                }
                break;
            case 2:
                if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                {
                    std::stringstream ss;
                    std::string temp_1;
                    std::string temp_2;
                    ss.precision(2);
                    ss << xover_probability;
                    ss >> temp_1;
                    ss.clear();
                    ss << mutation_probability;
                    ss >> temp_2;
                    std::string temp_3 = "S-E_probM-" + temp_2 + "_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "S-E_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                else
                {
                    ga.set_option_ga_variant_name("S-E"); // THIS NAME IS BEING USED TO TRIGGER PROPER EXTINCTION_EVENT
                }
                break;
            case 3:
            if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
            {
                std::stringstream ss;
                std::string temp_1;
                std::string temp_2;
                ss.precision(2);
                ss << xover_probability;
                ss >> temp_1;
                ss.clear();
                ss << mutation_probability;
                ss >> temp_2;
                std::string temp_3 = "CHC_probM-" + temp_2 + "probX-" + temp_1;
                ga.set_option_ga_variant_name(temp_3);
            }
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "CHC_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                else
                {
                    ga.set_option_ga_variant_name("CHC");
                }
                break;
            case 4:
                if(argc == 8 && xover_probability != -1 && mutation_probability != -1)
                {
                    std::stringstream ss;
                    std::string temp_1;
                    std::string temp_2;
                    ss.precision(2);
                    ss << xover_probability;
                    ss >> temp_1;
                    ss.clear();
                    ss << mutation_probability;
                    ss >> temp_2;
                    std::string temp_3 = "CHC-E_probM-" + temp_2 + "_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "CHC-E_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                else
                {
                    std::string temp_1(argv[1]);
                    ga.set_option_ga_variant_name(temp_1 + "_CHC-E");
                }
                break;
        }
        ga.report_averager(runs);
    }
}