#include "ga.h"
#include "test.h"

//AFTER TESTING REPORT CLEANUP FROM GA.CPP NEEDS TO BE COMMENTED BACK IN 
int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        std::cout << "If report is needed, must set argv[1] = 1; otherwise reporting is skipped" << std::endl;
        std::cout << "If multiple runs are needed, must set argv[2] = #runs; 1 run by default" << std::endl;
        std::cout << "GA type is CHC by default. If a different version is required, set argv[3] to one of the following options:" << std::endl;
        std::cout << "  1. Simple GA" << std::endl;
        std::cout << "  2. Simple GA w/extinction event" << std::endl;
        std::cout << "  3. CHC" << std::endl;
        std::cout << "  4. CHC w/extinction event" << std::endl;
        std::cout << "If runtime change to mutation probability is required, set argv[4] = mutation probability" << std::endl;
        std::cout << "  - Note: Currently, argv[4] will take an interger and divide it by 10 to get the actual mutation probability e.g. argv[4] = 1)" << std::endl;
        std::cout << "      - e.g. argv[4] = 1 converts to mutation_probability = 0.1" << std::endl;
        std::cout << "If runtime change to xover probability is required, set argv[5] = xover probability" << std::endl;
        std::cout << "  - Note: Currently, argv[5] will take an interger and divide it by 10 to get the actual mutation probability e.g. argv[4] = 1)" << std::endl;
        std::cout << "      - e.g. argv[4] = 1 converts to mutation_probability = 0.1" << std::endl;
        std::cout << "  - Note: If no runtime change to mutation probability is required, you must set argv[4] = -1" << std::endl;
    }

    int report_option = 0;
    int runs = 1;
    int ga_variant_option = 1;
    double mutation_probability = -1;
    double xover_probability = -1;
    
    if(argc == 2)
    {
        report_option = std::stoi(argv[1]);
    }
    
    if(argc == 3)
    {
        report_option = std::stoi(argv[1]);
        runs = std::stoi(argv[2]);
        if(runs <= 0 || runs > 10)
        {
            std::cout << "Can only choose up to 10 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
    }
    
    if(argc == 4)
    {
        report_option = std::stoi(argv[1]);
        runs = std::stoi(argv[2]);
        ga_variant_option = std::stoi(argv[3]);



        if(runs <= 0 || runs > 10)
        {
            std::cout << "Can only choose up to 10 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
        if(ga_variant_option <= 0 || ga_variant_option > 4)
        {
            std::cout << "List of available variants" << std::endl;
            std::cout << "1. Simple GA" << std::endl;
            std::cout << "2. Simple GA w/extinction event" << std::endl;
            std::cout << "3. CHC" << std::endl;
            std::cout << "4. CHC w/extinction event" << std::endl;
            std::cout << "Switching to option 2 (CHC) by default" << std::endl;
            runs = 1;
            ga_variant_option = 1;
        }
    }
    
    if(argc == 5)
    {
        report_option = std::stoi(argv[1]);
        runs = std::stoi(argv[2]);
        ga_variant_option = std::stoi(argv[3]);
        mutation_probability = std::strtod(argv[4], NULL);
        mutation_probability /= 10;

        if(runs <= 0 || runs > 10)
        {
            std::cout << "Can only choose up to 10 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
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
        if(mutation_probability <= 0 || mutation_probability >= 1)
        {
            std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
            mutation_probability = -1;
        }
    }
    
    if(argc == 6)
    {
        report_option = std::stoi(argv[1]);
        runs = std::stoi(argv[2]);
        ga_variant_option = std::stoi(argv[3]);
        mutation_probability = std::strtod(argv[4], NULL);
        mutation_probability /= 10;
        xover_probability = std::strtod(argv[5], NULL);
        xover_probability /= 10;

        //TEST
        // std::cout << "MAIN:ARGC==5" << std::endl;
        // std::cout << "xover prob = " << xover_probability << std::endl;

        if(runs <= 0 || runs > 10)
        {
            std::cout << "Can only choose up to 10 runs maximum" << std::endl;
            std::cout << "Switching to 1 run by default" << std::endl;
            runs = 1;
        }
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
        if(mutation_probability <= 0 || mutation_probability >= 1)
        {
            std::cout << "Mutation probability can only be given between 0 - 1" << std::endl;
            mutation_probability = -1;
        }
        if(xover_probability <= 0 || xover_probability >= 1)
        {
            std::cout << "Xover probability can only be given between 0 - 1" << std::endl;
            xover_probability = -1;
        }
    }

    //TEST
    // std::cout << "MAIN::RUN = " << j << std::endl << std::endl;
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

        GA ga(argc, argv, 6, j, ga_variant_option, mutation_probability, xover_probability);
        
        switch(ga_variant_option)
        {

            case 1:
                if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                else
                {
                    // ga.set_option_xover_prob(0.667);
                    // if(argc == 5 && mutation_probability != -1)
                    // {
                    //     ga.set_option_mutation_prob(mutation_probability);
                        
                    //     std::stringstream ss;
                    //     std::string temp_1;
                    //     ss.precision(2);
                    //     ss << mutation_probability;
                    //     ss >> temp_1;
                    //     std::string temp_2 = "S_probM-" + temp_1;
                    //     ga.set_option_ga_variant_name(temp_2);
                    // }
                    // else if(argc < 5)
                    // {
                        ga.set_option_mutation_prob(0.01);
                        ga.set_option_xover_prob(0.667);
                        ga.set_option_ga_variant_name("S");
                    // }
                    ga.set_file_names(j);
                }
                break;
            case 2:
                if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                    std::string temp_3 = "S-E_probM-" + temp_2 + "S-E_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // ga.set_option_xover_prob(0.667);
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     ga.set_option_mutation_prob(mutation_probability);
                    
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "S-E_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                // else if(argc < 5)
                else
                {
                    ga.set_option_mutation_prob(0.01);
                    ga.set_option_xover_prob(0.667);
                    ga.set_option_ga_variant_name("S-E"); // THIS NAME IS BEING USED TO TRIGGER PROPER EXTINCTION_EVENT
                }
                ga.set_file_names(j);
                ga.set_option_extinction_delay(50);
                ga.set_option_convergence_resolution_threshold(0.02);
                break;
            case 3:
                if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                    std::string temp_3 = "CHC_probM-" + temp_2 + "CHC_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // ga.set_option_xover_prob(0.99);
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     ga.set_option_mutation_prob(mutation_probability);
                    
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "CHC_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                // else if(argc < 5)
                else
                {
                    ga.set_option_mutation_prob(0.1);
                    ga.set_option_xover_prob(0.5);
                    ga.set_option_ga_variant_name("CHC");
                }
                ga.set_file_names(j);
                break;
            case 4:
                if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                    std::string temp_3 = "CHC-E_probM-" + temp_2 + "CHC-E_probX-" + temp_1;
                    ga.set_option_ga_variant_name(temp_3);
                }
                // ga.set_option_xover_prob(0.99);
                // if(argc == 5 && mutation_probability != -1)
                // {
                //     ga.set_option_mutation_prob(mutation_probability);
                    
                //     std::stringstream ss;
                //     std::string temp_1;
                //     ss.precision(2);
                //     ss << mutation_probability;
                //     ss >> temp_1;
                //     std::string temp_2 = "CHC-E_probM-" + temp_1;
                //     ga.set_option_ga_variant_name(temp_2);
                // }
                // else if(argc < 5)
                else
                {
                    ga.set_option_mutation_prob(0.1);
                    ga.set_option_xover_prob(0.5);
                    ga.set_option_ga_variant_name("CHC-E");
                }
                ga.set_file_names(j);
                break;
        }

        try
            {ga.init(6, report_option);}
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

        try
            {ga.run(6, report_option);}
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
        catch(std::string xover_mutate_test)
        {
            std::cout << xover_mutate_test << std::endl;
            
            //TEST
            // char temp;
            // std::cin >> temp;
            // sleep(2);

            //REAL
            return EXIT_FAILURE;
        }
        
        // count++;
    }

    GA ga(argc, argv, 6, runs, ga_variant_option, mutation_probability, xover_probability);
    switch(ga_variant_option)
    {
        case 1:
            if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                std::string temp_3 = "S_probM-" + temp_2 + "S_probX-" + temp_1;
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
            if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                std::string temp_3 = "S-E_probM-" + temp_2 + "S-E_probX-" + temp_1;
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
        if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
            std::string temp_3 = "CHC_probM-" + temp_2 + "CHC_probX-" + temp_1;
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
            if(argc == 6 && xover_probability != -1 && mutation_probability != -1)
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
                std::string temp_3 = "CHC-E_probM-" + temp_2 + "CHC-E_probX-" + temp_1;
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
                ga.set_option_ga_variant_name("CHC-E");
            }
            break;
    }
    ga.report_averager(runs);

    //TEST
    // std::cout << "OUTSIDE OF RUN: END OF PROGRAM" << std::endl;

    // std::cout << count << std::endl;

    // for(int i = 1; i <= 1; i++)
    // {
    //     GA ga(argc, argv, i, count - 1);

    //     report_averager(count, ga.options.output_file, ga.options.ave_file, ga.options.print_precision, ga.options.population_size);
    //     report_averager(count, ga.options.output_file_o, ga.options.ave_file_o, ga.options.print_precision_o, ga.options.population_size);
    // }

    // max_floorplanning_objective_value(atof(argv[1]),atof(argv[2]),atof(argv[3]));

}