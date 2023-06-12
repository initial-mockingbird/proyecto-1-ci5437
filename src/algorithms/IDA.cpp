#include <limits>
#include <iostream>
#include <utility> 
#include "IDA.hpp"
#include "../utils/pdb.hpp"
#include <chrono>

using namespace std::chrono;

#define MAX_RUN_TIME 420000
//#include "../top-spin/12-4spin.h"
int64_t total_nodes = 0;

int64_t alreadySpentMaxRuntime(system_clock::time_point &from) {
    int64_t curTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return curTime > MAX_RUN_TIME ? curTime : -1;
}

typedef unsigned long long bound_t;
typedef std::pair<std::optional<state_t>, bound_t> ida_pair_t;


bound_t g = 0ULL;

void print_state(state_t &state) {
    for (int i = 0; i < NUMVARS; ++i)
        std::cout << static_cast<int16_t>(state.vars[i]) << ", ";
    std::cout << std::endl;
}

ida_pair_t f_bounded_dfs_visit(state_t &state, bound_t bound, PDB pdb,system_clock::time_point start){
    int64_t auxTime;
    bound_t f = g + pdb.h(state);
    if (f > bound) return ida_pair_t(std::nullopt, f);
    if (is_goal(&state)) return ida_pair_t(std::optional<state_t>{state}, f);

    int action;
    ruleid_iterator_t iter;
    init_fwd_iter(&iter, &state);

    bound_t t = std::numeric_limits<bound_t>::max();
    
    while ((action = next_ruleid(&iter)) >= 0) {
        total_nodes++;
        if ((auxTime = alreadySpentMaxRuntime(start)) != -1) {
            std::cout << "Tiempo de corrida " << auxTime << "ms" << std::endl;
            break;
        }
        state_t m;
        int cost = get_fwd_rule_cost(action);
        g += cost;

        apply_fwd_rule(action, &state, &m);
        ida_pair_t p = f_bounded_dfs_visit(m, bound,pdb,start);

        g -= cost;
        if (p.first.has_value()) return p;
        t = std::min<bound_t>(t, p.second);
    }

    return ida_pair_t(std::nullopt, t);
}


std::optional<state_t> do_ida(state_t root,PDB pdb) {
    bound_t bound = 1ULL;

    std::cout << "Estado raiz" << std::endl;
    print_state(root);
    int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();

    while (true)
    {
        g = 0ULL;
        ida_pair_t p(f_bounded_dfs_visit(root, bound, pdb, start));

        if ((auxTime = alreadySpentMaxRuntime(start)) != -1) {
            std::cout << "Tiempo de corrida " << auxTime << "ms" << std::endl;
            std::cout << "Nodos totales expandidos: " << total_nodes << std::endl;
            return std::nullopt;
        }
        if (p.first.has_value()){
          std::cout << "Nodos totales expandidos: " << total_nodes << std::endl;
          return p.first.value();
        } 
        
        bound = p.second + 1; // + 1 por los momentos
    }

}