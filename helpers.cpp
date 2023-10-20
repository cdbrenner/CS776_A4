#include "helpers.h"

//DYNAMIC HELPERS
int add_dynamic_element_to_end(int *&dynamic_array, int array_length, int new_element)
{

    // std::cout << "BEGIN ADD_DYNAMIC_ELEMNT" << std::endl;

    int updated_array_length = array_length + 1;
    int* temp = new int[updated_array_length];
    //TEST
    // std::cout << "NEW:       " << new_element << std::endl;
    // std::cout << "UP_LEN:    " << updated_array_length << std::endl;
    
    for(int i = 0; i < array_length; i++)
        temp[i] = dynamic_array[i];    
    
    temp[updated_array_length - 1] = new_element;

    //TEST
    // for(int i = 0; i < updated_array_length; i++)
    // {
    //     if(i == 0 && updated_array_length == 1)
    //         std::cout << "temp:      " << temp[i] << std::endl;
    //     else if(i == 0)
    //         std::cout << "temp:      " << temp[i] << " ";
    //     else if(i < updated_array_length - 1)
    //         std::cout << temp[i] << " ";
    //     else
    //         std::cout << temp[i] << std::endl;
    // }
    // //TEST
    // if(dynamic_array != nullptr)
    // {
    //     for(int i = 0; i < array_length; i++)
    //     {
    //         if(i == 0 && array_length == 1)
    //             std::cout << "DYNAMIC:   " << dynamic_array[i] << std::endl;
    //         else if(i == 0)
    //             std::cout << "DYNAMIC:   " << dynamic_array[i] << " ";
    //         else if(i < array_length - 1)
    //             std::cout << dynamic_array[i] << " ";
    //         else
    //             std::cout << dynamic_array[i] << std::endl;
    //     }
    // }
    // else
    //     std::cout << "DYNAMIC: NULL\n";

    if(dynamic_array != nullptr)
    {
        //TEST
        // std::cout << "INSIDE DYNAMIC DELETE" << std::endl;

        delete[] dynamic_array;
    }

    // dynamic_array = new int[updated_array_length];
    // for(int i = 0; i < updated_array_length; i++)
    // {
    //     dynamic_array[i] = temp[i];
    // }

    dynamic_array = temp;

    
    //TEST
    // for(int i = 0; i < updated_array_length; i++)
    // {
    //     if(dynamic_array != nullptr)
    //     {
    //         if(i == 0 && updated_array_length == 1)
    //             std::cout << "P-DYNAMIC: " << dynamic_array[i] << std::endl;
    //         else if(i == 0)
    //             std::cout << "P-DYNAMIC: " << dynamic_array[i] << " ";
    //         else if(i < updated_array_length - 1)
    //             std::cout << dynamic_array[i] << " ";
    //         else
    //             std::cout << dynamic_array[i] << std::endl;
    //     }
    //     else
    //         std::cout << "P-DYNAMIC: NULL\n";
    // }
    //TEST
    // std::cout << std::endl;
    // delete[] temp;

    temp = nullptr;

    return updated_array_length;
}

int add_dynamic_element_to_beginning(int *&dynamic_array, int array_length, int new_element)
{
    int updated_array_length = array_length + 1;
    int* temp = new int[updated_array_length];
    
    temp[0] = new_element;

    for(int i = 0; i < array_length; i++)
        temp[i + 1] = dynamic_array[i];
    

    if(dynamic_array != nullptr)
        delete[] dynamic_array;

    dynamic_array = temp;
    temp = nullptr;

    return updated_array_length;
}

int combine_dynamic_arrays(int *&beginning_dynamic_array, int *&ending_dynamic_array, int beginning_array_length, int ending_array_length)
{
    int updated_array_length = beginning_array_length + ending_array_length;
    int* temp = new int[updated_array_length];
    
    for(int i = 0; i < beginning_array_length; i++)
        temp[i] = beginning_dynamic_array[i];

    for(int i = 0; i < ending_array_length; i++)
        temp[i + beginning_array_length] = ending_dynamic_array[i];
    
    if(beginning_dynamic_array != nullptr)
        delete[] beginning_dynamic_array;
    if(ending_dynamic_array != nullptr)
        delete[] ending_dynamic_array;

    beginning_dynamic_array = temp;
    temp = nullptr;
    ending_dynamic_array = nullptr;

    return updated_array_length;
}

//PRINT HELPERS
std::string add_whitespace(int current_line_number, int total_line_count, bool delimeter)
{
    int current_digits;
    int total_digits;
    if(delimeter)
    {
        current_digits = std::to_string(current_line_number).length() + 1;
        total_digits = std::to_string(total_line_count).length() + 1;
    }
    else
    {
        current_digits = std::to_string(current_line_number).length();
        total_digits = std::to_string(total_line_count).length();
    }

    if(total_digits >= 4 && total_digits < 8)
    {
        if(current_digits == 1)
            return "   ";
        else if(current_digits == 2)
            return "  ";
        else if(current_digits == 3)
            return " ";
    }

    return "";
}

int flip(float probability, int random_seed, int offset)
{
    srand(random_seed + offset);
    return (rand() < probability*RAND_MAX ? 1 : 0);
}

int random_index_in_range(int low, int high, int random_seed, int offset)
{
    srand(random_seed + offset);
    return low + rand()%(high - low);
}

void report_averager(int iterations, std::string filename, std::string output_name, int precision, int population_size)
{
    std::cout << filename << std::endl;
    std::cout << output_name << std::endl;

    std::ifstream in(filename);
    std::ofstream out(output_name);

    out << "GEN,\t\tMIN,\t\t\tAVE,\t\t\tMAX,\n";

    std::string temp;
    std::string gen_str;
    std::string min_str;
    std::string ave_str;
    std::string max_str;
    int gen;
    double min;
    double ave;
    double max;
    getline(in, temp);

    for(int i = 0; i < population_size; i++)
    {
        getline(in,gen_str,',');
        getline(in,min_str,',');
        getline(in,ave_str,',');
        getline(in,max_str,',');
        gen = atoi(gen_str.c_str());
        min = atof(min_str.c_str());
        ave = atof(ave_str.c_str());
        max = atof(max_str.c_str());

        min /= iterations;
        ave /= iterations;
        max /= iterations;

        out << std::fixed << std::setprecision(precision) << gen << ",\t\t" << min << ",\t\t" << ave << ",\t\t" << max << "," << std::endl;

    }
    out.close();
    std::remove(filename.c_str());
}