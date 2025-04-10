#include "object.h"
#include <string>

namespace renderer {

class Parser {
public:
    static Object parse(const std::string &filename);

private:
    struct ParserTriangle {
        int a;
        int b;
        int c;
    };
    static void parse_polygon(std::istringstream &iss, std::vector<ParserTriangle> &triangles,
                              std::vector<int32_t> &normals);
};

} // namespace renderer
