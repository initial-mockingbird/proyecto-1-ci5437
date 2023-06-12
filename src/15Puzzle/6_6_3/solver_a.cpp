#include "../../utils/pdb.hpp"
#include "../../algorithms/A_star/A_star.hpp"
#include "../../algorithms/IDA.hpp"
#include <vector>
#include <string>
#include <optional>


int main(int argc, char const *argv[])
{
  std::vector<std::string> names{"abst_1","abst_2","abst_3"};
  PDB pdb{names,PDB_MODE::ADD};
  state_t state;

  read_state(argv[1], &state);
  
  GlobalConfig config {pdb,state};
  
  std::optional<Node> result = a_star<GlobalConfig,State,Node,Action>(config);
  std::cout << result.has_value() << std::endl;
  
  
  return 0;
}
