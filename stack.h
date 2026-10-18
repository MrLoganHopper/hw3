#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
// Private inheritance: a Stack is implemented in terms of a vector, but
// users should not get vector operations like insert() or operator[].
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T>
Stack<T>::Stack() : std::vector<T>()
{
}

template <typename T>
Stack<T>::~Stack()
{
}

template <typename T>
bool Stack<T>::empty() const
{
    return std::vector<T>::empty();
}

template <typename T>
size_t Stack<T>::size() const
{
    return std::vector<T>::size();
}

// The back of the vector is the top of the stack, so all ops are O(1)
template <typename T>
void Stack<T>::push(const T& item)
{
    std::vector<T>::push_back(item);
}

template <typename T>
void Stack<T>::pop()
{
    if (empty()) {
        throw std::underflow_error("pop() called on empty stack");
    }
    std::vector<T>::pop_back();
}

template <typename T>
const T& Stack<T>::top() const
{
    if (empty()) {
        throw std::underflow_error("top() called on empty stack");
    }
    return std::vector<T>::back();
}

#endif
