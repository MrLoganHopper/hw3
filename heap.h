#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
  void trickleUp(size_t idx);
  void trickleDown(size_t idx);

  std::vector<T> data_;
  int m_;
  PComparator comp_;
};

// Add implementation of member functions here

// Layout: root at index 0. For node i, children are m*i+1 ... m*i+m
// and the parent is (i-1)/m.

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

// Swap a node upward while it has priority over its parent
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t idx)
{
  while (idx > 0) {
    size_t parent = (idx - 1) / m_;
    if (!comp_(data_[idx], data_[parent])) {
      break;
    }
    std::swap(data_[idx], data_[parent]);
    idx = parent;
  }
}

// Swap a node downward with its best child until heap order holds
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t idx)
{
  size_t n = data_.size();
  while (true) {
    size_t first = m_ * idx + 1;
    if (first >= n) {
      break;  // leaf
    }
    size_t best = first;
    for (size_t c = first + 1; c < first + m_ && c < n; ++c) {
      if (comp_(data_[c], data_[best])) {
        best = c;
      }
    }
    if (!comp_(data_[best], data_[idx])) {
      break;
    }
    std::swap(data_[best], data_[idx]);
    idx = best;
  }
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
    throw std::underflow_error("top() called on empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_[0];
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
    throw std::underflow_error("pop() called on empty heap");
  }

  // Move the last item to the root, shrink, then restore order
  data_[0] = data_.back();
  data_.pop_back();
  if (!data_.empty()) {
    trickleDown(0);
  }
}



#endif

