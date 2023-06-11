#include "../../utils/pdb.hpp"
#include "../../algorithms/A_star/A_star.hpp"
#include <vector>
#include <string>
#include <optional>
int main(int argc, char const *argv[])
{
  if (argc < NUMVARS){
    std::cout << "THE STATE VECTOR IS INCOMPLETE, FATAL ERROR. PROVIDE GOOD INPUT" << std::endl;
    return 1;
  }
  std::vector<std::string> names{"abst_1","abst_2","abst_3","abst_4"};
  PDB pdb{names,PDB_MODE::ADD};
  state_t state;

  std::cout << NUMVARS << std::endl;
  for (size_t i = 1; i <= NUMVARS; i++)
  {
    state.vars[i-1]  = std::stoi(argv[i]);
  }
  
  
  GlobalConfig config {pdb,state};
  
  std::optional<Node> result = a_star<GlobalConfig,State,Node,Action>(config);
  std::cout << result.has_value() << std::endl;
  return 0;
}
