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
    
    {state.is_goal()}              -> std::same_as<bool>;
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
    if(get<0>(a) > get<0>(b))
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

    opt.set_distance(opt.init(),0);
    pq.push({opt.h(opt.init()),opt.make_root_node(opt.init())});
    
    while (!pq.empty()){
        //Node n   = pop<Node>(pq);
        Node n = std::get<1>(pq.top());
        pq.pop();
        State ns = n.state();
        if (n.g() < opt.get_distance(ns)){
            std::cout << "ACA" << std::endl;
            opt.set_distance(ns,n.g());
            if (ns.is_goal()) return n;
            for(auto [s,a,c] : ns.successors())
            {   
                
                std::cout << "Costo: " << c << std::endl;
                if (opt.h(s) <  std::numeric_limits<double>::infinity()){
                    std::tuple<double,Node> _ns{
                        n.g() + c + opt.h(s), 
                        n.make_node(s,a)
                    };
                    std::cout << "Pusheando nodo con costo: " << std::get<0>(_ns) << std::endl;
                    pq.push(_ns);
                }
            }
        }
    }

    return std::nullopt;

}


// kinda works? A* is Best First Search + partial duplicate pruning. This is just Best First Search
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
        if (ns.is_goal()){
            std::cout << "GOLAZO" << std::endl;
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