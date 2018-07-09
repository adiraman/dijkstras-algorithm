#include "../include/directed_weighted_graph.h"
#include "../include/heap.h"
#include "../include/shortestPath.h"
#include "../include/undirected_weighted_graph.h"

template <typename T>
void printVec(const T &elements)
{
    for (auto const &e : elements)
    {
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

    undirected_weighted_graph g3;
    std::cout << "Undirected Graph 2\n";
    g3.addEdge(0, 1, 4);
    g3.addEdge(0, 7, 8);
    g3.addEdge(1, 2, 8);
    g3.addEdge(1, 7, 11);
    g3.addEdge(7, 8, 7);
    g3.addEdge(7, 6, 1);
    g3.addEdge(2, 8, 2);
    g3.addEdge(2, 5, 4);
    g3.addEdge(2, 3, 7);
    g3.addEdge(8, 6, 6);
    g3.addEdge(6, 5, 2);
    g3.addEdge(3, 5, 14);
    g3.addEdge(3, 4, 9);
    g3.addEdge(5, 4, 10);
    g3.writeDot("graph3.dot");
    std::cout << g3 << std::endl;

    shortestPath sp3(g3);
    auto dist2 = sp3.compute(0);
    std::cout << "Distances from vertex 0 : ";
    printVec(dist2);

    return 0;
}
