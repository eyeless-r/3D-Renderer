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
    std::vector<Vector3> normals;
    std::vector<ParserTriangle> parser_triangles;
    std::vector<int32_t> normal_numbers;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            Point p;
            iss >> p.x >> p.y >> p.z;
            points.push_back(p);
        } else if (type == "vn") {
            Vector3 normal;
            iss >> normal[0] >> normal[1] >> normal[2];
            normal.normalize();
            normals.push_back(normal);
        } else if (type == "f") {
            parse_polygon(iss, parser_triangles, normal_numbers);
        }
    }
    std::vector<Triangle> triangles;
    for (int32_t triangle_number = 0; triangle_number < parser_triangles.size(); ++triangle_number) {
        ParserTriangle triangle = parser_triangles[triangle_number];
        int32_t normal_number = normal_numbers[triangle_number];
        Vector3 normal{0, 0, 0};
        if (normal_number != -1) {
            normal = normals[normal_number];
        }
        triangles.push_back(Triangle{points[triangle.a], points[triangle.b], points[triangle.c], normal});
    }
    return Object(triangles);
}

void Parser::parse_polygon(std::istringstream &iss, std::vector<ParserTriangle> &triangles,
                           std::vector<int32_t> &normals) {
    std::vector<int32_t> polygon;
    int32_t normal = -1;
    std::string vertex_info;
    while (iss >> vertex_info) {
        std::istringstream vertex_stream(vertex_info);
        std::string point_number;
        std::getline(vertex_stream, point_number, '/');
        polygon.push_back(std::stoi(point_number) - 1);
        std::getline(vertex_stream, point_number, '/');
        if (std::getline(vertex_stream, point_number)) {
            normal = std::stoi(point_number) - 1;
        }
    }
    for (int32_t polygon_point = 2; polygon_point < polygon.size(); ++polygon_point) {
        triangles.push_back(ParserTriangle{polygon[0], polygon[polygon_point - 1], polygon[polygon_point]});
        normals.push_back(normal);
    }
}

} // namespace renderer