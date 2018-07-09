#include "../include/undirected_weighted_graph.h"

undirected_weighted_graph::undirected_weighted_graph(int vertices)
{
    for (int i = 0; i < vertices; ++i)
    {
        m_adjList[i] = std::set<std::pair<int, int>>();
    }
}

void undirected_weighted_graph::addVertex(int vertex)
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

void undirected_weighted_graph::removeVertex(int vertex)
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

void undirected_weighted_graph::addEdge(int source, int dest, int weight)
{
    // Always have the source to be less than the destination for
    // clarity of implementation
    int start = source < dest ? source : dest;
    int end = source < dest ? dest : source;

    // check if both the vertices exist in the graph
    // this is already done in the addVertex call
    addVertex(start);
    addVertex(end);

    // create connections between the source and destination
    // vertices
    m_adjList[start].emplace(end, weight);
    m_adjList[end].emplace(start, weight);
    return;
}

void undirected_weighted_graph::removeEdge(int source, int dest)
{
    // Note: each edge is represented only once in the adjacency list
    // The representation is such that the source vertex always has
    // a lower value than the destination vertex. Thus use the min of
    // provided source and dest to remove an edge.
    int start = source < dest ? source : dest;
    int end = source < dest ? dest : source;

    // remove the connections between source and destination
    if (m_adjList.find(start) != m_adjList.end())
    {
        for (auto d : m_adjList[start])
        {
            if (d.first == end)
            {
                m_adjList[start].erase(d);
            }
        }
        for (auto d : m_adjList[end])
        {
            if (d.first == start)
            {
                m_adjList[end].erase(d);
            }
        }
    }
    return;
}

int undirected_weighted_graph::countVertices()
{
    return m_adjList.size();
}

int undirected_weighted_graph::countEdges()
{
    // iterate through the map and sum up the set sizes.
    int edges = 0;
    for (auto i : m_adjList)
    {
        edges += i.second.size();
    }
    return edges / 2;
}

bool undirected_weighted_graph::writeDot(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (file.is_open())
    {
        file << "strict graph {" << std::endl;

        for (auto i : m_adjList)
        {
            for (auto j : i.second)
            {
                file << "  " << i.first << " -- " << j.first << ";" << std::endl;
            }
        }
        file << "}" << std::endl;
        file.close();
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> undirected_weighted_graph::getEdges() const
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

std::vector<int> undirected_weighted_graph::getVertices() const
{
    std::vector<int> vertices;
    for (auto it : m_adjList)
    {
        vertices.push_back(it.first);
    }
    return vertices;
}

std::map<int, std::set<std::pair<int, int>>> undirected_weighted_graph::getAdjacencyList() const
{
    return m_adjList;
}

std::ostream &operator<<(std::ostream &oss, const undirected_weighted_graph &graph)
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
