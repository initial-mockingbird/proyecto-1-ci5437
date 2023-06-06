#pragma once

#include <vector>
#include <cassert>


emum PDB_MODE {ADD, MAX};

struct PDB_INFO {
  abstraction_t * abst;
  state_map_t * pdb;
};

struct PDB {
  std::vector<PDB_INFO> pdbs;
  PDB_MODE mode;

  int h(state_t current_state){
    int *pdb_value;
    int value = 0;
    int temp;
    for(auto pdb_info : this->pdbs)
    {

      state_t abst_state;
      abstract_state(pdb_info.abst, &state, &abst_state);
      *pdb_value = state_map_get(pdb_info.pdb, &abst_state);
      assert(pdb_value != 0);
      temp = *pdb_value;
      switch (this->mode)
      {
      case PDB_MODE::ADD:
        value += temp;
        break;
      case PDB_MODE::MAX:
        value = value >= temp ? value : temp;
        break;
      default:
        break;
      }
    }
    return value;
  }

};