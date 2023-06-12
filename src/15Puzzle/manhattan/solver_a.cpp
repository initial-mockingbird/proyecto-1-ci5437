#include "../../utils/pdb.hpp"
#include "../../algorithms/A_star/A_star.hpp"
#include "../../algorithms/IDA.hpp"
#include <vector>
#include <string>
#include <optional>
#include<cmath>

struct PDB_M : PDB {

  int h(state_t current_state){
    int score = 0;
    for (size_t i = 0; i < NUMVARS; i++)
    {
      int value = current_state.vars[i];
      int displacement = value - i;
      score += pow(displacement / NUMVARS,2) + pow(displacement % NUMVARS,2);
    }

    return score;
    
  }
};

int main(int argc, char const *argv[])
{
  std::vector<std::string> names{"abst_1","abst_2","abst_3"};
  PDB_M pdb;
  state_t state;

  read_state(argv[1], &state);
  
  GlobalConfig config {pdb,state};
  
  std::optional<Node> result = a_star<GlobalConfig,State,Node,Action>(config);
  std::cout << result.has_value() << std::endl;
  
  
  return 0;
}
