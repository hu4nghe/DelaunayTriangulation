#include <stdexcept>
#include <fstream>

#include "csv_parser.h"

struct parse_error : std::runtime_error 
{
    using std::runtime_error::runtime_error;
};

auto parse_line(const std::string& line, std::size_t lineno) -> std::pair<double,double> 
{
    auto comma_pos = line.find(',');
    
    if (comma_pos == std::string::npos)
        throw parse_error("Line " + std::to_string(lineno) + ": missing comma");

    auto parse_double = [&](std::string_view sv)
    {
        double value{};
        auto* begin = sv.data();
        auto* end = sv.data() + sv.size();
        auto  res = std::from_chars(begin, end, value);
        
        if (res.ec != std::errc() || res.ptr != end) 
            throw parse_error("Line " + std::to_string(lineno) + ": invalid double '" + std::string(sv) + "'");
        
        return value;
    };

    double x = parse_double(std::string_view(line).substr(0, comma_pos));
    double y = parse_double(std::string_view(line).substr(comma_pos + 1));
    return {x, y};
}

std::vector<std::pair<double,double>> read_csv_coords(const std::filesystem::path& file)
{
    std::ifstream fin(file);
    if (!fin.is_open())
        throw std::runtime_error("Cannot open file: " + file.string());

    std::vector<std::pair<double,double>> coords;
    std::string line;
    std::size_t lineno{};

    while (std::getline(fin, line)) 
    {
        lineno++;
        if (line.empty()) continue;
        coords.push_back(parse_line(line, lineno));
    }
    return coords;
}
