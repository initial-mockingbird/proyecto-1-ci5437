#include <iostream>

#include "algorithms/BFS.hpp"
//#include "aux.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return 1;

    std::cout << argv[1] << std::endl;
    state_t root;
    read_state(argv[1], &root);

    //do_bfs(root);
    do_bfs_prunning(root);
    return 0;
}
