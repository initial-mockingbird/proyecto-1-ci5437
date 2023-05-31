#include <limits>
#include <iostream>
#include <utility> 

#include "IDA.hpp"

//#include "../top-spin/12-4spin.h"

typedef unsigned long long bound_t;
typedef std::pair<std::optional<state_t>, bound_t> ida_pair_t;


bound_t g = 0ULL;

void print_state(state_t &state) {
    for (int i = 0; i < 12; ++i)
        std::cout << static_cast<int16_t>(state.vars[i]) << ", ";
    std::cout << std::endl;
}

ida_pair_t f_bounded_dfs_visit(state_t &state, bound_t bound){
    bound_t f = g;
    if (f > bound) return ida_pair_t(std::nullopt, f);
    if (is_goal(&state)) return ida_pair_t(std::optional<state_t>{state}, f);

    int action;
    ruleid_iterator_t iter;
    init_fwd_iter(&iter, &state);

    bound_t t = std::numeric_limits<bound_t>::max();
    
    while ((action = next_ruleid(&iter)) >= 0) {
        state_t m;
        int cost = get_fwd_rule_cost(action);
        g += cost;

        apply_fwd_rule(action, &state, &m);
        ida_pair_t p = f_bounded_dfs_visit(m, bound);

        g -= cost;
        if (p.first.has_value()) return p;
        t = std::min<bound_t>(t, p.second);
    }

    return ida_pair_t(std::nullopt, t);
}


std::optional<state_t> do_ida() {
    
    state_t root = {
        {3, 2, 1, 0, 7, 6, 5, 4, 8, 9, 10, 11}
    };

    bound_t bound = 1ULL;

    std::cout << "Estado raiz" << std::endl;
    print_state(root);
    
    while (true)
    {
        g = 0ULL;
        ida_pair_t p(f_bounded_dfs_visit(root, bound));

        if (p.first.has_value()) return p.first.value();
        
        bound = p.second + 1; // + 1 por los momentos
    }

}