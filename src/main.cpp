#include "../include/directed_weighted_graph.h"
#include "../include/heap.h"
#include "../include/shortestPath.h"
#include "../include/undirected_weighted_graph.h"

template <typename T>
void printVec(const T& elements)
{
    for (auto const& e : elements) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    undirected_weighted_graph g1;
    std::cout << "Undirected Graph" << std::endl;
    g1.addEdge(0, 1, 6);
    g1.addEdge(0, 2, 2);
    g1.addEdge(0, 3, 2);
    g1.addEdge(1, 4, 3);
    g1.addEdge(1, 5, 4);
    g1.addEdge(2, 6, 3);
    g1.addEdge(3, 7, 1);
    g1.addEdge(4, 7, 3);
    g1.addEdge(5, 7, 5);
    g1.addEdge(6, 7, 4);
    g1.writeDot("graph1.dot");
    std::cout << g1 << std::endl;

    shortestPath sp1(g1);
    auto dist = sp1.compute(0);
    std::cout << "Distances from vertex 0 : ";
    printVec(dist);

    directed_weighted_graph g2;
    std::cout << "Directed Graph" << std::endl;
    g2.addEdge(0, 1, 6);
    g2.addEdge(0, 2, 2);
    g2.addEdge(0, 3, 2);
    g2.addEdge(1, 4, 3);
    g2.addEdge(1, 5, 4);
    g2.addEdge(2, 6, 3);
    g2.addEdge(3, 7, 1);
    g2.addEdge(4, 7, 3);
    g2.addEdge(5, 7, 5);
    g2.addEdge(6, 7, 4);
    g2.writeDot("graph2.dot");
    std::cout << g2 << std::endl;

    shortestPath sp2(g2);
    auto dist1 = sp2.compute(0);
    std::cout << "Distances from vertex 0 : ";
    printVec(dist1);

    return 0;
}
