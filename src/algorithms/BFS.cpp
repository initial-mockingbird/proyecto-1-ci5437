#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <unordered_map>
#include "BFS.hpp"
#include "../utils/state_comparer.hpp"

#define MAX_RUN_TIME 420000
//#include "../aux.hpp"

using namespace std::chrono;

enum COLOR {WHITE, GRAY, BLACK};

std::vector<int64_t> levelNodes {};
int curLevelNodes;
int nexLevelNodes;

int64_t alreadySpentMaxRuntime(system_clock::time_point &from) {
    int64_t curTime = duration_cast<milliseconds>(high_resolution_clock::now() - from).count();
    return curTime > MAX_RUN_TIME ? curTime : -1;
}


std::optional<state_t> do_bfs(state_t root)
{
    int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();

    unsigned long long nodos = 0ULL;
    std::queue<state_t> q;
    ruleid_iterator_t iter;

    q.emplace(root);

    levelNodes.clear();
    curLevelNodes = 1;
    nexLevelNodes = 1;

    while (!q.empty()) {
        int action;
        state_t n = q.front(); q.pop();
        init_fwd_iter(&iter, &n);

        if (curLevelNodes == 0) 
        {
            levelNodes.push_back(nexLevelNodes);
            curLevelNodes = nexLevelNodes;
            nexLevelNodes = 0;

            std::cout << "Profundidad: " << levelNodes.size() << std::endl;
            std::cout << "Tiene " << curLevelNodes << " nodo(s)." << std::endl;
        }

        if (is_goal(&n))
        {
            std::cout << "Profundidad: " << levelNodes.size() << std::endl;
            std::cout << "Tiene " << levelNodes.back() << " nodo(s)." << std::endl;
            std::cout << "Tiempo de corrida " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
            std::cout << "ms" << std::endl << std::endl;
            return std::optional<state_t>(n);
        }

        if ((auxTime = alreadySpentMaxRuntime(start)) != -1) {
            std::cout << "Tiempo de corrida " << auxTime << "ms" << std::endl;
            break;
        }

        while ((action = next_ruleid(&iter)) >= 0) {
            state_t s;
            apply_fwd_rule(action, &n, &s);

            q.emplace(s);
            nexLevelNodes += 1;
        }
        curLevelNodes--;
    }

    std::cout << "No hay objetivo" << std::endl;
    std::cout << "Tiempo de corrida " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    std::cout << "ms" << std::endl << std::endl;
    return std::nullopt;
}


std::optional<state_t> do_bfs_prunning(state_t root)
{
    int64_t auxTime;
    system_clock::time_point start = high_resolution_clock::now();

    unsigned long long nodos = 0ULL;
    std::queue<state_t> q;
    std::unordered_map<state_t, COLOR> colors = {{}};
    ruleid_iterator_t iter;

    colors[root] = COLOR::WHITE;
    q.emplace(root);

    levelNodes.clear();
    curLevelNodes = 1;
    nexLevelNodes = 1;

    while (!q.empty()) {
        int action;
        state_t n = q.front(); q.pop();
        init_fwd_iter(&iter, &n);

        if (curLevelNodes == 0) 
        {
            levelNodes.push_back(nexLevelNodes);
            curLevelNodes = nexLevelNodes;
            nexLevelNodes = 0;

            std::cout << "Profundidad: " << levelNodes.size() << std::endl;
            std::cout << "Tiene " << curLevelNodes << " nodo(s)." << std::endl;
        }
        
        if (is_goal(&n))
        {
            std::cout << "Profundidad: " << levelNodes.size() << std::endl;
            std::cout << "Tiene " << levelNodes.back() << " nodo(s)." << std::endl;
            std::cout << "Tiempo de corrida " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
            std::cout << "ms" << std::endl << std::endl;
            return std::optional<state_t>(n);
        }

        if ((auxTime = alreadySpentMaxRuntime(start)) != -1) {
            std::cout << "Tiempo de corrida " << auxTime << "ms" << std::endl;
            break;
        }

        while ((action = next_ruleid(&iter)) >= 0) {
            state_t s;
            apply_fwd_rule(action, &n, &s);
            if (colors.contains(s)) {
                if (colors[s] == COLOR::WHITE) {
                    colors[s] = COLOR::GRAY;
                    q.emplace(s);
                    nexLevelNodes += 1;
                }
            }    
            else {
                colors[s] = COLOR::GRAY;
                q.emplace(s);
                nexLevelNodes += 1;
            }
        }

        curLevelNodes--;
        colors[n] = COLOR::BLACK;
    }

    std::cout << "No hay objetivo" << std::endl;
    std::cout << "Tiempo de corrida " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    std::cout << "ms" << std::endl << std::endl;
    return std::nullopt;
}