#pragma once

#include <optional>
#include <cstddef>
#include <concepts>
#include <queue>
#include <string>
#include <tuple>
#include <vector>
#include <limits>
#include <optional>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "../../utils/pdb.hpp"

/* Interface */

// Declaration of the concept "A star"
// Which defines the same set of operations as in IA classes.
template<typename GlobalConfig, typename State, typename Node, typename Action>
concept A_star = requires(GlobalConfig opt, Node n, State state, double cost, Action action)
{
    {opt.init()}                   -> std::same_as<State>;
    {opt.h(state)}                 -> std::floating_point;

    {n.state()}                    -> std::same_as<State>;
    {n.g()}                        -> std::floating_point;
    {n.make_node(state,action)}    -> std::same_as<Node>;
    
    {state.is_goal_achieved()}     -> std::same_as<bool>;
    {state.successors()}           -> std::same_as<std::vector<std::tuple<State,Action,double>>>;


    {opt.make_root_node(state)}    -> std::same_as<Node>;
    
    {opt.get_distance(state)}      -> std::floating_point;
    {opt.set_distance(state,cost)} -> std::same_as<void>;
    
    {state.print()}                -> std::same_as<void>;

};


// We need a way of easily inserting things into PQ.
// priority queue comparator
template<typename T>
class Compare_Tuple{
public:
  bool operator()(const std::tuple<double,T>& a, const std::tuple<double,T>& b) const{
    if(std::get<0>(a) >= std::get<0>(b))
      return true;
    return false;
  }
};


// hush, i have to pass pq by reference or the pop doesnt mutate.
template<typename T>
T pop(std::priority_queue<
    std::tuple<double,T>, 
    std::vector<std::tuple<double,T>>,
    Compare_Tuple<T>
    > pq){
    
    std::cout << "Sacando elemento con peso: " << std::get<0>(pq.top()) << std::endl;
    T element = std::get<1>(pq.top());
    pq.pop();
    return element;
}


// doesnt work, ask the teach why
template<typename GlobalConfig, typename State, typename Node, typename Action>
requires A_star<GlobalConfig, State, Node, Action>
std::optional<Node> a_star(GlobalConfig opt){
    // Arguments swap, in the pdf it has type: PQ<Node,double>
    // but i prefer to put the cost at the beginning.
    std::priority_queue<
        std::tuple<double,Node>, 
        std::vector<std::tuple<double,Node>>,
        Compare_Tuple<Node>
        > pq;

    pq.push({opt.h(opt.init()),opt.make_root_node(opt.init())});
    
    while (!pq.empty()){
        //Node n   = pop<Node>(pq);
        Node n = std::get<1>(pq.top());
        pq.pop();
        State ns = n.state();
        if (n.g() < opt.get_distance(ns)){
            opt.set_distance(ns,n.g());
            if (ns.is_goal_achieved()) return n;
            for(auto [s,a,c] : ns.successors())
            {   
                s.print();
                double h = opt.h(s);
                std::cout << n.g() << std::endl;
                std::cout << c << std::endl;
                std::cout << h << std::endl;

                if (h <  std::numeric_limits<double>::infinity()){
                    std::tuple<double,Node> _ns{
                        n.g() + c + h, 
                        n.make_node(s,a)
                    };
                    pq.push(_ns);
                }
            }
        }
    }

    return std::nullopt;

}


// Use a* instead.
template<typename GlobalConfig, typename State, typename Node, typename Action>
requires A_star<GlobalConfig, State, Node, Action>
std::optional<Node> a_star_sane(GlobalConfig opt){
    // Arguments swap, in the pdf it has type: PQ<Node,double>
    // but i prefer to put the cost at the beginning.
    std::priority_queue<
        std::tuple<double,Node>, 
        std::vector<std::tuple<double,Node>>,
        Compare_Tuple<Node>
        > pq;

    opt.set_distance(opt.init(),0);
    pq.push({opt.h(opt.init()),opt.make_root_node(opt.init())});
    
    while (!pq.empty()){
        //Node n   = pop<Node>(pq);
        Node n = std::get<1>(pq.top());
        pq.pop();
        State ns = n.state();
        if (ns.is_goal_achieved()){
            return n;
        } 
        
        for(auto [s,a,c] : ns.successors())
        {   
            if (opt.h(s) >=  std::numeric_limits<double>::infinity()) continue;

            auto g = n.g() + c;
            std::tuple<double,Node> _ns{
                g + opt.h(s), 
                n.make_node(s,a)
            };
    
            // redudant? yes.
            if (opt.get_distance(s) >=  std::numeric_limits<double>::infinity()){
                opt.set_distance(s,g);
                pq.push(_ns);
            } else if (g < opt.get_distance(s))
            {
                opt.set_distance(s,g);
                pq.push(_ns);
            }
        }
        
    }
    return std::nullopt;
}


/* Interpreter */


typedef int Action;
struct State
{
    state_t state;

    State(){} // sigh 

    State(state_t state){
        this->state = state;
    }


    bool is_goal_achieved(){
        return is_goal(&(this->state)) == 1;
    }

    std::vector<std::tuple<State,Action,double>> successors(){
      
        std::vector<std::tuple<State,Action,double>> succs;

        ruleid_iterator_t iter;
        init_fwd_iter(&iter, &(this->state));
      
        int action;
        while ((action = next_ruleid(&iter)) >= 0) {
            state_t m;
            apply_fwd_rule(action, &(this->state), &m);
            State _m{m};
            int cost = get_fwd_rule_cost(action);

            succs.push_back({m,action,cost});
        }

        return succs;

    }

    // printea a un archivo, y que? te vas a arrechar por esa verga?
    void print(){
        std::ofstream outfile;

        outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
        
        for (int i = 0; i < 4; ++i){
          for (int j = 0; j < 4; j++)
          {
            outfile << static_cast<int16_t>(this->state.vars[i*4+j]) << " ";
          }
            outfile << std::endl;
            
        }
            
        outfile << std::endl; 
    }
    bool operator==(const State &a) {
        return compare_states(&(this->state), &(a.state)) == 0;
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
            int cost = get_fwd_rule_cost(action);
            double new_g = this->g() + cost;
            
            Node n{state,new_g};
            return n;
        }

};

struct GlobalConfig{

    private:
        PDB _pdb;
        state_t _root;
        std::unordered_map<uint64_t ,double>  costs;

        uint64_t hash_state_wrapped(State state){
            state_t st = state.state;
            return hash_state(&st);
        }

    public:

        GlobalConfig(PDB pdb, state_t root){
          this->_pdb  = pdb;
          this->_root = root;
        }

        State init(){
            State initial_state{this->_root};
            return initial_state;
        }


        // Change for pattern database implementation
        double h(State state){
            return this->_pdb.h(state.state);
        }

        Node make_root_node(State initial_state){
            Node initial_node{initial_state,0};
            return initial_node;
        }

        double get_distance(State state){
            std::uint64_t  hash = this->hash_state_wrapped(state);
            if (!this->costs.contains(hash))
                return std::numeric_limits<double>::infinity();
            return this->costs[hash];
        }

        void set_distance(State state,double cost){
            std::uint64_t  hash = this->hash_state_wrapped(state);
            this->costs[hash] = cost;
        }

};
