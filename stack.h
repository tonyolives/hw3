#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:

    // -- NOTE: "top" of stack is the back -- //

    Stack() {};
    ~Stack() {};

    // check if stack empty
    bool empty() const {
        return std::vector<T>::empty();
    };

    // return size of stack
    size_t size() const {
        return std::vector<T>::size();
    };

    // add item to back
    void push(const T& item) {
        std::vector<T>::push_back(item);
    };

    // delete last element
    // throws std::underflow_error if empty
    void pop() {
        if (empty()) {
            throw std::underflow_error("Satck is empty");
        }
        std::vector<T>::pop_back();
    }

    // get last element
    // throws std::underflow_error if empty
    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Satck is empty");
        }
        return std::vector<T>::back();
    }

    // Add other members only if necessary
};


#endif