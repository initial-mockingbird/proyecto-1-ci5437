#include "../../../algorithms/A_star/top-spinner.hpp"

int main(int argc, char const *argv[])
{
    GlobalConfig opt;
    std::optional<Node> result = a_star_sane<GlobalConfig,State,Node,Action>(opt);

    std::cout << "Exito? " << result.has_value() << std::endl;
    return 0;
}


