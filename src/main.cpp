#include <iostream>

#include "algorithms/IDA.hpp"
#include "algorithms/BFS.hpp"

int main(int argc, char const *argv[])
{
    do_ida();
    state_t root = {
        {3, 2, 1, 0, 7, 6, 5, 4, 8, 9, 10, 11}
    };
    do_bfs(root);
    do_bfs_prunning(root);
    return 0;
}
