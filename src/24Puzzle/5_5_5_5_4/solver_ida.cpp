#include "../../utils/pdb.hpp"
#include "../../algorithms/IDA.hpp"
#include <vector>
#include <string>
#include <optional>
#include <iostream>


int main(int argc, char const *argv[])
{
  std::vector<std::string> names
    { "abst_1"
    , "abst_2"
    , "abst_3"
    , "abst_4"
    , "abst_5"
    };
  PDB pdb{names,PDB_MODE::MAX};
  state_t state;
 
  read_state(argv[1], &state);
  
  std::optional<state_t> result = do_ida(state,pdb);
  std::cout << result.has_value() << std::endl;
  
  return 0;
}
