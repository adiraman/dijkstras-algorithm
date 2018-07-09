#ifndef DIRECTED_WEIGHTED_GRAPH_H
#define DIRECTED_WEIGHTED_GRAPH_H

#include "../include/graph.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

/*
 * A basic implementation of an adjacency list representation
 * for a directed graph. The adjacency list is implemented
 * as a std::map with the keys being the vertices and the value pair
 * being the std::set of unique connected vertices.
 *
 * This implementation also has basic facilities to :-
 * (1) add/remove vertices and edges.
 * (2) count the number of vertices and edges.
 * (3) Write a dot file for graphViz to plot.
 * (4) Helper functions to get a list of edges.
 */

class directed_weighted_graph : public graph
{
  public:
    directed_weighted_graph() = default;

    directed_weighted_graph(int vertices);

    virtual ~directed_weighted_graph() = default;

    virtual void addVertex(int vertex) override;

    virtual void removeVertex(int vertex) override;

    virtual void addEdge(int source, int dest, int weight) override;

    virtual void removeEdge(int source, int edge) override;

    virtual int countVertices() override;

    virtual int countEdges() override;

    virtual bool writeDot(std::string filename) override;

    std::vector<std::pair<int, int>> getEdges() const;

    std::vector<int> getVertices() const;

    virtual std::map<int, std::set<std::pair<int, int>>>
    getAdjacencyList() const override;

    friend std::ostream &operator<<(std::ostream &oss,
                                    const directed_weighted_graph &graph);

  private:
    // pair of <vertex, edgeweight>
    std::map<int, std::set<std::pair<int, int>>> m_adjList;
};

#endif /* ifndef UNDIRECTED_GRAPH_H */
