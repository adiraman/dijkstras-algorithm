#include "../include/shortestPath.h"
#include <queue>

typedef std::pair<int, int> iPair;

shortestPath::shortestPath(const graph& g)
{
    m_graph = g.getAdjacencyList();
}


std::vector<int> shortestPath::compute(const int& source) const
{
    // initialize and set all distances to infinity.
    int inf = std::numeric_limits<int>::max();
    std::vector<int> distances(m_graph.size(), inf);

    // create a min heap to store vertices that are being processed,
    // 1st element of the pair is the distance and 2nd is the vertex.
    heap<iPair> minHeap;
    /* std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> minHeap; */
    /* minHeap.push(std::make_pair(0, source)); */
    minHeap.insert(std::make_pair(0, source));
    distances[source] = 0;

    /* Loop till the heap is empty (or till all the distances are not
     * finalized. */
    while (!minHeap.empty()) {
        /* The first vertex in the pair is the min distance vertex.
         * Extract it from the heap. The second element of the pair
         * is the vertex label. */
        auto up = minHeap.pop();
        int u = up.second;
        /* int u = minHeap.top().second; */
        /* minHeap.pop(); */

        for (auto vp : m_graph.at(u)) {
            int v = vp.first;
            int weight = vp.second;

            // check if there is a shorter path from u to v
            if (distances[v] > distances[u] + weight) {
                // update distance of v
                distances[v] = distances[u] + weight;
                minHeap.insert(std::make_pair(distances[v], v));
                /* minHeap.push(std::make_pair(distances[v], v)); */
            }
        }
    }
    return distances;
}
