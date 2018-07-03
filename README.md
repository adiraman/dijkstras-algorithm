# Dijkstra's algorithm

Dijkstra's algorithm implementation using a minimum heap data structure

Algorithm:-

1.  Initialize distances of all vertices as infinity
2.  Create an empty minimum heap. Every item of the heap is a pair (weight, vertex). Insert source vertex with distance 0.
3.  While the heap is non empty:-
  -  Extract min-distance vertex of the heap.
  -  loop through all adjacent vertices of the corresponding vertex.
  -  update distances and insert into heap.