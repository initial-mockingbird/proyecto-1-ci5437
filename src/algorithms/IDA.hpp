#pragma once
#include <optional>

std::optional<state_t> do_ida();
void print_state(state_t &state);