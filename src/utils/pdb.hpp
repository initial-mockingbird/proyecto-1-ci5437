#pragma once

#include <vector>
#include <cassert>
#include <string>

enum class PDB_MODE {ADD, MAX};


struct PDB_INFO {
  abstraction_t * abst;
  state_map_t * pdb;

  PDB_INFO(){}

  PDB_INFO(std::string abst_fname, std::string pdb_fname){
    this->abst = read_abstraction_from_file(abst_fname.c_str());
    FILE *pdb_file = fopen(pdb_fname.c_str(), "r");
    assert(pdb_file != NULL);
    this->pdb = read_state_map(pdb_file);
    fclose(pdb_file);
  }
};


struct PDB {
  std::vector<PDB_INFO> pdbs;
  PDB_MODE mode;

  PDB(){}

  PDB(std::vector<std::string> names,PDB_MODE mode){
    for (auto name: names){
      PDB_INFO info{name+".abst",name+".pdb"};
      this->pdbs.push_back(info);
    }
    this->mode=mode;
  }

  int h(state_t current_state){
    int *pdb_value;
    int value = 0;
    int temp;
    for(auto pdb_info : this->pdbs)
    {

      state_t abst_state;
      abstract_state(pdb_info.abst, &current_state, &abst_state);
      pdb_value = state_map_get(pdb_info.pdb, &abst_state);
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