#include "object.h"

#include <string>

namespace renderer {

class Parser {
public:
    static Object parse(const std::string &filename, Color color);

private:
    struct ParserTriangle {
        int a;
        int b;
        int c;
    };
    static void parse_polygon(std::istringstream &iss, std::vector<ParserTriangle> &triangles);
};

} // namespace renderer
