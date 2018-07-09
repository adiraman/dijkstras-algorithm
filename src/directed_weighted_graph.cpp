#include "../include/directed_weighted_graph.h"

directed_weighted_graph::directed_weighted_graph(int vertices)
{
    for (int i = 0; i < vertices; ++i)
    {
        m_adjList[i] = std::set<std::pair<int, int>>();
    }
}

void directed_weighted_graph::addVertex(int vertex)
{
    // If the list is empty no need to check for the vertex, simply
    // add it to the list.
    if (m_adjList.empty())
    {
        m_adjList.emplace(vertex, std::set<std::pair<int, int>>());
        return;
    }
    // check to see if the vertex is already in the adjacency list.
    // If not, add it to the list.
    if (m_adjList.find(vertex) == m_adjList.end())
    {
        m_adjList.emplace(vertex, std::set<std::pair<int, int>>());
    }
    return;
}

void directed_weighted_graph::removeVertex(int vertex)
{
    // first delete the vertex
    m_adjList.erase(vertex);

    // remove all entries connected to the removed vertex
    for (auto i : m_adjList)
    {
        for (auto j : i.second)
        {
            if (j.first == vertex)
            {
                i.second.erase(j);
            }
        }
    }
    return;
}

void directed_weighted_graph::addEdge(int source, int dest, int weight)
{
    // check if both the vertices exist in the graph
    // this is already done in the addVertex call
    addVertex(source);
    addVertex(dest);

    // create connections between the source and destination
    // vertices
    m_adjList[source].emplace(dest, weight);
    return;
}

void directed_weighted_graph::removeEdge(int source, int dest)
{
    // remove the connections between source and destination
    if (m_adjList.find(source) != m_adjList.end())
    {
        for (auto d : m_adjList[source])
        {
            if (d.first == dest)
            {
                m_adjList[source].erase(d);
            }
        }
    }
    return;
}

int directed_weighted_graph::countVertices()
{
    return m_adjList.size();
}

int directed_weighted_graph::countEdges()
{
    // iterate through the map and sum up the set sizes.
    int edges = 0;
    for (auto i : m_adjList)
    {
        edges += i.second.size();
    }
    return edges;
}

bool directed_weighted_graph::writeDot(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (file.is_open())
    {
        file << "digraph {" << std::endl;

        for (auto i : m_adjList)
        {
            for (auto j : i.second)
            {
                file << "  " << i.first << " -> " << j.first << ";" << std::endl;
            }
        }
        file << "}" << std::endl;
        file.close();
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> directed_weighted_graph::getEdges() const
{
    std::vector<std::pair<int, int>> edges;
    for (auto it : m_adjList)
    {
        for (auto di : it.second)
        {
            edges.push_back(std::make_pair(it.first, di.first));
        }
    }
    return edges;
}

std::vector<int> directed_weighted_graph::getVertices() const
{
    std::vector<int> vertices;
    for (auto it : m_adjList)
    {
        vertices.push_back(it.first);
    }
    return vertices;
}

std::map<int, std::set<std::pair<int, int>>> directed_weighted_graph::getAdjacencyList() const
{
    return m_adjList;
}

std::ostream &operator<<(std::ostream &oss, const directed_weighted_graph &graph)
{
    for (auto it : graph.m_adjList)
    {
        oss << it.first << " :: ";
        for (auto di : it.second)
        {
            oss << " => " << di.first << " (weight = " << di.second << ")";
        }
        oss << std::endl;
    }
    return oss;
}
