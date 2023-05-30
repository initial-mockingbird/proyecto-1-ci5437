#include <iostream>
#include <queue>
#include <unordered_map>

#include "BFS.hpp"
#include "../utils/state_comparer.hpp"

//#include "../top-spin/12-4spin.h"

enum COLOR {WHITE, GRAY, BLACK};

std::optional<state_t> do_bfs(state_t root)
{
    unsigned long long nodos = 0ULL;
    std::queue<state_t> q;
    ruleid_iterator_t iter;

    q.emplace(root);

    while (!q.empty()) {
        int action;
        state_t n = q.front(); q.pop();
        init_fwd_iter(&iter, &n);
        
        if (is_goal(&n)) return std::optional<state_t>(n);

        while ((action = next_ruleid(&iter)) >= 0) {
            state_t s;
            apply_fwd_rule(action, &n, &s);

            q.emplace(s);
        }
    }

    return std::nullopt;
}

std::optional<state_t> do_bfs_prunning(state_t root)
{
    unsigned long long nodos = 0ULL;
    std::queue<state_t> q;
    std::unordered_map<state_t, COLOR> colors = {{}};
    ruleid_iterator_t iter;

    colors[root] = COLOR::WHITE;
    q.emplace(root);

    while (!q.empty()) {
        int action;
        state_t n = q.front(); q.pop();
        init_fwd_iter(&iter, &n);
        
        if (is_goal(&n)) return std::optional<state_t>(n);

        while ((action = next_ruleid(&iter)) >= 0) {
            state_t s;
            apply_fwd_rule(action, &n, &s);
            if (colors.contains(s)) {
                if (colors[s] == COLOR::WHITE) {
                    colors[s] = COLOR::GRAY;
                    q.emplace(s);
                }
            }    
            else {
                colors[s] = COLOR::GRAY;
                q.emplace(s);
            }
        }

        colors[n] = COLOR::BLACK;
    }

    return std::nullopt;
}