#include <filesystem>
#include <vector>

/**
 * @brief Parse a csv file into vector cordinate (double, double)
 * 
 * @param file file to parse
 * @return std::vector<std::pair<double,double>> result
 */
auto read_csv_coords(const std::filesystem::path& file) -> std::vector<std::pair<double,double>>;