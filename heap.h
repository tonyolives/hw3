#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;  // vector to store heap elements
  int m;                // m-ary heap (m-children per node)
  PComparator comp;     // comparator functoin

  void trickleUp(size_t index);  // restore heap property after insertion
  void trickleDown(size_t index); // restore heap property after removal
};

// Add implementation of member functions here

// ctor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m(m), comp(c) {}

// dtor (no dynamic memory, nothing to delete)
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {}

// insert
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  data.push_back(item); // insert item at end
  trickleUp(data.size() - 1); // restore heap order
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return data[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================

    throw std::underflow_error("Heap is empty");

  }

  data[0] = data.back(); // move last element to root
  data.pop_back(); // remove last elememt
  trickleDown(0); // restore heap order
}

// empty
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return data.empty();
}

// size
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data.size();
}


// trickle up
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t index) {
  while (index > 0) {
    // find parent
    size_t parent = (index - 1) / m;
    // swap if needed, use comp functor
    if (comp(data[index], data[parent])) {
      std::swap(data[index], data[parent]);
      index = parent;
    }
    else {
      break;
    }
  }
}

// trickle down
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t index) {
  while (true) {
    size_t priorityChild = index; // assume current node is best
    for (int i = 1; i <= m; ++i) {
      size_t childIndex = m * index + i;
      if (childIndex < data.size() && comp(data[childIndex], data[priorityChild])) {
        priorityChild = childIndex;
      }
    }

    if (priorityChild != index) { // Swap if needed
      std::swap(data[index], data[priorityChild]);
      index = priorityChild;
    }
    else {
      break;
    }
  }
}



#endif

