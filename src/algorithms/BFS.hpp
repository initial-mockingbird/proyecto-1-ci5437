#pragma once
#include <optional>

std::optional<state_t> do_bfs(state_t root);
std::optional<state_t> do_bfs_prunning(state_t root);