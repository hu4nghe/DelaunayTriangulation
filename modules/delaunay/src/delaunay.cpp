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
#include "geo_2D/triangle_2D.h"

#include <ranges>
#include <functional>
#include <set>

using namespace tools_2D;

auto super_triangle(const std::vector<point>& points) 
{
    auto [min_x, max_x] = std::ranges::minmax(points | std::views::transform(std::mem_fn(&point::get_x)));
    auto [min_y, max_y] = std::ranges::minmax(points | std::views::transform(std::mem_fn(&point::get_x)));

    double avg_x = (min_x + max_x) / 2.0;
    const point p1(avg_x, max_y);
    const point p2(max_x, min_y);
    double k = p1.slope(p2);

    const point a(avg_x,                               max_y - k * avg_x);
    const point b(max_x + (min_y - max_y - 1) / k + 1, min_y - 1);
    const point c(2 * avg_x - b.get_x(),               min_y - 1); 

    return std::tuple(a, b, c);
}

auto delaunay_triangulate(const std::vector<point>& points) 
{
    if (points.size() <= 3) 
        throw std::invalid_argument("At least 4 points are required for triangulation.");

    // Construct a super triangle at first.
    auto [p1, p2, p3] = super_triangle(points);
    std::vector<triangle> all_triangles{triangle(p1, p2, p3)};

    for (const auto& p : points) 
    {
        std::set<segment> polygon;
        std::erase_if(
            all_triangles, 
            [&](const triangle& tri)
            {
                if (tri.circum_circle().contains(p))
                {
                    for (const auto& e : tri.get_edges()) 
                        if (!polygon.erase(e)) 
                            polygon.insert(e);
                    return true;
                }
                return false;             
            });
                         
        //construct new triangles with current point and segments.                                
        for (const auto& e : polygon)
            all_triangles.emplace_back(p, e);
            
    }

    // Remove triangles that contain any of the super triangle vertices.
    std::erase_if(
        all_triangles,
        [&](const triangle& tri) 
        {
            for (const auto& p : {p1, p2, p3})
                if(tri.containsVertex(p)) 
                    return true;
            return false;
        });
                                        
    return all_triangles;
}

int main()
{
    auto coords = read_csv_coords("points.csv");
    std::vector<point> points;
    for(const auto [x, y] : coords)
        points.emplace_back(x, y);

    auto result = delaunay_triangulate(points);

    return 0;   
}