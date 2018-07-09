#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <string>
#include <vector>

class graph
{
  public:
    virtual ~graph() = default;

    virtual void addVertex(int v) = 0;
    virtual void removeVertex(int v) = 0;
    virtual void addEdge(int src, int dest, int weight) = 0;
    virtual void removeEdge(int src, int dest) = 0;
    virtual int countVertices() = 0;
    virtual int countEdges() = 0;
    virtual bool writeDot(std::string filename) = 0;
    virtual std::map<int, std::set<std::pair<int, int>>>
    getAdjacencyList() const = 0;
};

#endif
