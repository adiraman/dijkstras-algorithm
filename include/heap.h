#ifndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <exception>

/*
 * A Generic heap data structure that provides a minimum heap by
 * default. In order to get a max heap, pass in `std::less<T>`
 * comparator, or a custom implementation of `less than` operator.
 */
template <class T, class Compare = std::greater<T>>
class heap
{
  public:
    heap() = default;
    heap(const std::vector<T> &elems, const Compare &comp);
    heap(const T elems[], int len, const Compare &comp);
    heap(const std::vector<T> &elems);
    heap(const T elems[], int len);

    // Basic Operations interface :-
    /*
     * returns the minimum value by default. Returns the max value,
     * if a `less than` operator is passed in as a template arg.
     */
    T pop();
    /*
     * Insert a new element in the heap.
     */
    void insert(T elem);
    /*
     * Erase an existing element from the heap.
     * This method searches the container for the argument provided
     * and removes it from the heap if found.
     */
    void erase(T elem);

    // basic container operations :-
    /*
     * Returns the size of the container.
     */
    int size() const;
    /*
     * Check if the container is empty.
     */
    bool empty() const;
    /*
     * Clears all the elements of the container.
     */
    void clear() noexcept;

    // iterator access :-
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    iterator begin() { return m_heap.begin(); }
    const_iterator begin() const { return m_heap.begin(); }
    const_iterator cbegin() const { return end(); }

    iterator end() { return m_heap.end(); }
    const_iterator end() const { return m_heap.end(); }
    const_iterator cend() const { return end(); }

  private:
    std::vector<T> m_heap;
    Compare m_comp;

    // convenience functions to get access to the child/parent of a
    // given node index
    int getLeftChildIndex(const int &parentIndex) const;
    int getRightChildIndex(const int &parentIndex) const;
    int getParentIndex(const int &childIndex) const;

    bool hasLeftChild(const int &index) const;
    bool hasRightChild(const int &index) const;
    bool hasParent(const int &index) const;

    T leftChild(const int &index) const;
    T rightChild(const int &index) const;
    T parent(const int &index) const;

    // Helper functions that govern the operation of
    // the data container
    void make_heap();
    void bubble_up(int index);
    void bubble_down(int index);
    int getElementIndex(const T &elem) const;
};

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T> &elems, const Compare &comp)
    : m_heap(elems), m_comp(comp)
{
    make_heap();
}

template <class T, class Compare>
heap<T, Compare>::heap(const T elems[], int len, const Compare &comp)
    : m_comp(comp)
{
    for (int i = 0; i < len; ++i)
    {
        m_heap.emplace_back(elems[i]);
    }
    make_heap();
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T> &elems)
    : m_heap(elems), m_comp(Compare())
{
    make_heap();
}

template <class T, class Compare>
heap<T, Compare>::heap(const T elems[], int len)
    : m_comp(Compare())
{
    for (int i = 0; i < len; ++i)
    {
        m_heap.emplace_back(elems[i]);
    }
    make_heap();
}

template <class T, class Compare>
int heap<T, Compare>::size() const
{
    return m_heap.size();
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return m_heap.empty();
}

template <class T, class Compare>
void heap<T, Compare>::clear() noexcept
{
    m_heap.clear();
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (m_heap.empty())
    {
        throw std::logic_error("Popping an empty heap");
    }
    // extract the root
    T minima = m_heap[0];

    // swap last element with the root
    m_heap[0] = m_heap[m_heap.size() - 1];

    // delete the last element and decrement the size
    m_heap.pop_back();

    // bubble_down the root to preserve the heap property
    bubble_down(0);

    return minima;
}

template <class T, class Compare>
void heap<T, Compare>::insert(T elem)
{
    // insert element at the end and increment the size
    m_heap.emplace_back(elem);

    // bubble up the last element to preserve the heap property
    bubble_up(m_heap.size() - 1);

    return;
}

template <class T, class Compare>
void heap<T, Compare>::erase(T elem)
{
    int index = getElementIndex(elem);
    if (index == -1)
    {
        return; // if element is not found
    }

    // swap this element with the last element and delete it
    m_heap[index] = m_heap[m_heap.size() - 1];
    m_heap.pop_back();

    // bubble down if this is the root node
    if (!hasParent(index))
    {
        bubble_down(index);
        return;
    }
    // bubble up if this is a leaf node
    if (!hasLeftChild(index))
    {
        bubble_up(index);
        return;
    }
    // for other nodes in the interior :-

    // 1. Bubble up if its parent is greater
    if (m_comp(parent(index), m_heap[index]))
    {
        bubble_up(index);
    }

    // 2. Bubble down if it's greater than the smaller child
    auto left = leftChild(index);
    auto right = rightChild(index);
    int smallerChildIndex = m_comp(left, right) ? getRightChildIndex(index) : getLeftChildIndex(index);
    if (m_comp(m_heap[index], m_heap[smallerChildIndex]))
    {
        bubble_down(smallerChildIndex);
    }

    return;
}

template <class T, class Compare>
int heap<T, Compare>::getElementIndex(const T &elem) const
{
    //  returns -1 if element is not found in the heap, else
    //  returns the very first element index that it finds
    auto pos = std::find(m_heap.begin(), m_heap.end(), elem);
    return pos == m_heap.end() ? -1 : std::distance(m_heap.begin(), pos);
}

template <class T, class Compare>
int heap<T, Compare>::getLeftChildIndex(const int &parentIndex) const
{
    return (parentIndex << 1) + 1;
}

template <class T, class Compare>
int heap<T, Compare>::getRightChildIndex(const int &parentIndex) const
{
    return (parentIndex << 1) + 2;
}

template <class T, class Compare>
int heap<T, Compare>::getParentIndex(const int &childIndex) const
{
    return ((childIndex - 1) >> 1);
}

template <class T, class Compare>
bool heap<T, Compare>::hasLeftChild(const int &index) const
{
    int n = m_heap.size();
    return (getLeftChildIndex(index) < n);
}

template <class T, class Compare>
bool heap<T, Compare>::hasRightChild(const int &index) const
{
    int n = m_heap.size();
    return (getRightChildIndex(index) < n);
}

template <class T, class Compare>
bool heap<T, Compare>::hasParent(const int &index) const
{
    return (getParentIndex(index) >= 0);
}

template <class T, class Compare>
T heap<T, Compare>::leftChild(const int &index) const
{
    return m_heap[getLeftChildIndex(index)];
}

template <class T, class Compare>
T heap<T, Compare>::rightChild(const int &index) const
{
    return m_heap[getRightChildIndex(index)];
}

template <class T, class Compare>
T heap<T, Compare>::parent(const int &index) const
{
    return m_heap[getParentIndex(index)];
}

template <class T, class Compare>
void heap<T, Compare>::bubble_up(int index)
{
    // base case, bubbled up to root.
    if (!hasParent(index))
    {
        return;
    }
    // check if the current node and its parent violate the
    // heap property
    int parentIndex = getParentIndex(index);
    if (m_comp(parent(index), m_heap[index]))
    {
        // swap the two
        std::iter_swap(m_heap.begin() + parentIndex, m_heap.begin() + index);

        // recursively bubble up the parent node
        bubble_up(parentIndex);
    }
    return;
}

template <class T, class Compare>
void heap<T, Compare>::bubble_down(int index)
{
    // base case, bubbled down to leaf (no children)
    if (!hasLeftChild(index) && !hasRightChild(index))
    {
        return;
    }

    // Find the smaller of the 2 children
    int smallerChildIndex = 0;
    if (hasLeftChild(index))
    {
        // if it has only left child, the smaller child index will
        // be set accordingly
        smallerChildIndex = getLeftChildIndex(index);
        if (hasRightChild(index) && m_comp(leftChild(index), rightChild(index)))
        {
            smallerChildIndex = getRightChildIndex(index);
        }
    }

    // if node is greater than its smaller child, swap
    if (m_comp(m_heap[index], m_heap[smallerChildIndex]))
    {
        std::iter_swap(m_heap.begin() + index, m_heap.begin() + smallerChildIndex);
        bubble_down(smallerChildIndex);
    }
    return;
}

template <class T, class Compare>
void heap<T, Compare>::make_heap()
{
    for (int i = m_heap.size() - 1; i >= 0; --i)
    {
        bubble_down(i);
    }
    return;
}

#endif /* ifndef HEAP_H */
