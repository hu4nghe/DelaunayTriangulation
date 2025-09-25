/**
 * @file delaunay.cpp
 * @author HUANG He (he.hu4ng@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "csv_parser.h"


#include <print>
 
int main()
{
    try 
    {
        std::filesystem::path csvfile = "points.csv"; 
        auto coords = read_csv_coords(csvfile);

        // debug output
        for (auto [x, y] : coords)
            std::println("x = {}, y = {}.", x, y);
    }
    catch (const parse_error& e) 
    {
        std::println(stderr, "Format error : {}", e.what());
        return 1;
    }
    
}
