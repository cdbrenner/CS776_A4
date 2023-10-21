#include "helpers.h"

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