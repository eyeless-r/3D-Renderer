#include "parser.h"
#include <fstream>
#include <sstream>

namespace renderer {

Object Parser::parse(const std::string &filename) {
    if ((filename.size() < 4) || (filename.substr(filename.size() - 4, 4) != ".obj")) {
        throw std::invalid_argument("Filename should end with .obj");
    }
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
    }

    std::vector<Point> points;
    std::vector<ParserTriangle> parser_triangles;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            Point p;
            iss >> p.x >> p.y >> p.z;
            points.push_back(p);
        } else if (type == "f") {
            parse_polygon(iss, parser_triangles);
        }
    }
    std::vector<Triangle> triangles;
    for (const ParserTriangle &triangle : parser_triangles) {
        triangles.push_back(Triangle(points[triangle.a], points[triangle.b], points[triangle.c]));
    }
    return Object(triangles);
}

void Parser::parse_polygon(std::istringstream &iss, std::vector<ParserTriangle> &triangles) {
    std::vector<int32_t> polygon;
    std::string vertex_info;
    while (iss >> vertex_info) {
        std::istringstream vertex_stream(vertex_info);
        std::string point_number;
        std::getline(vertex_stream, point_number, '/');
        polygon.push_back(std::stoi(point_number) - 1);
    }
    for (int32_t polygon_point = 2; polygon_point < polygon.size(); ++polygon_point) {
        triangles.push_back(ParserTriangle{polygon[0], polygon[polygon_point - 1], polygon[polygon_point]});
    }
}

} // namespace renderer
