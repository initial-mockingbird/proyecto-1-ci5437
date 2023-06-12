#pragma once
#include <optional>

std::optional<state_t> do_ida(state_t root,PDB pdb);
void print_state(state_t &state);