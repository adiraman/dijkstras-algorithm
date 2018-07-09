#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "../include/directed_weighted_graph.h"
#include "../include/heap.h"
#include "../include/undirected_weighted_graph.h"

/*
 * Implementation of the Dijkstra's shortest path algorithm
 */
class shortestPath
{
  public:
    shortestPath(const graph &g);
    shortestPath() = delete;
    ~shortestPath() = default;

    std::vector<int> compute(const int &source) const;

  private:
    std::map<int, std::set<std::pair<int, int>>> m_graph;
};

#endif /* ifndef SHORTEST_PATH_H */
