#pragma once

#include "./A_star.hpp"
#include "../../top-spin/topspin12-4.hpp"

/*
 C++ doesnt have a module system like ocaml, thus there is no way of parametrize 
 the defines. 
*/
/*
  NO ME RECLAMES PEDRO.
*/
#define init_fwd_iter_top_spin( ruleid_iter, state ) { \
    (*ruleid_iter).my_funcptr = top_spin::fwdfn0_r0 ; \
    (*ruleid_iter).my_state = state; \
}

#define next_ruleid_top_spin( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

#define get_fwd_rule_cost_top_spin( ruleid ) (top_spin::fwd_rule_cost[(ruleid)]) 

#define apply_fwd_rule_top_spin( rule, state, result ) top_spin::fwd_rules[(rule)](state,result)

#define NUMVARS_top_spin 12


typedef int Action;

struct State
{
    top_spin::state_t state;

    State(){} // sigh 

    State(top_spin::state_t state){
        this->state = state;
    }


    bool is_goal(){
        return top_spin::is_goal(&(this->state)) == 1;
    }

    std::vector<std::tuple<State,Action,double>> successors(){
      
        std::vector<std::tuple<State,Action,double>> succs;

        top_spin::ruleid_iterator_t iter;
        init_fwd_iter_top_spin(&iter, &(this->state));
      
        int action;
        while ((action = next_ruleid_top_spin(&iter)) >= 0) {
            top_spin::state_t m;
            apply_fwd_rule_top_spin(action, &(this->state), &m);
            State _m{m};
            int cost = get_fwd_rule_cost_top_spin(action);

            succs.push_back({m,action,cost});
        }

        return succs;

    }

    // printea a un archivo, y que? te vas a arrechar por esa verga?
    void print(){
        std::ofstream outfile;

        outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
        
        for (int i = 0; i < 12; ++i)
            outfile << static_cast<int16_t>(this->state.vars[i]) << " ";
        outfile << std::endl;
    } 
};

struct Node
{
    private: 
        State _state;
        double _g;

    public: 

        Node(){}

        Node(State state, double g){
            this->_state = state;
            this->_g     = g;
        }

        State state(){
            return this->_state;
        }

        double g(){
            return this->_g;
        }

        Node make_node(State state, Action action){
            int cost = get_fwd_rule_cost_top_spin(action);
            double new_g = this->g() + cost;
            
            Node n{state,new_g};
            return n;
        }

};

struct GlobalConfig{

    private:

        // these things dhould be here (except the map)
        // but oh well.
        std::size_t hash_seed = NUMVARS_top_spin;

        std::unordered_map<top_spin::var_t,double>  costs;

        top_spin::var_t hash_state(State state){

            top_spin::state_t st = state.state;
            std::size_t hash = this->hash_seed;

            for (std::size_t i = 0; i < NUMVARS_top_spin; i++)
                hash ^= st.vars[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);    
            
            return hash;

        }

    public:

        GlobalConfig(){}

        State init(){
            /* top_spin::state_t root = {
                {3, 2, 1, 0, 7, 6, 5, 4, 8, 9, 10, 11}
            };  */

            top_spin::state_t root = {{0, 1, 2, 3, 4, 5, 6, 7, 11, 10, 9, 8}};
             /* top_spin::state_t root = {
                {3,2,1,0,4,5,6,7,8,9,10,11}
            };  */
            /* top_spin::state_t root = {
                {0,1,2,3,4,5,6,7,8,9}
            }; */
            State initial_state{root};

            return initial_state;
        }


        // Change for pattern database implementation
        double h(State state){
            return 0;
        }

        Node make_root_node(State initial_state){
            Node initial_node{initial_state,0};
            return initial_node;
        }

        double get_distance(State state){
            std::size_t hash = this->hash_state(state);
            if (!this->costs.contains(hash))
                return std::numeric_limits<double>::infinity();
            return this->costs[hash];
        }

        void set_distance(State state,double cost){
            std::size_t hash = this->hash_state(state);
            this->costs[hash] = cost;
        }

};
