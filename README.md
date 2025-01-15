# DoubleVector-Class
Basic vector-like container for Doubles in C++

## Overview

The `double_vector` class is a custom implementation of a dynamic array designed to manage collections of double-precision floating-point numbers. It mimics the functionality of the C++ STL `std::vector` class while providing iterators, memory management, and additional utilities.

## Features

- **Dynamic resizing:** Automatically manages memory allocation as elements are added or removed.
- **Iterators:** Supports custom iterators for traversal.
- **Memory management:** Includes functions for reserving capacity and shrinking memory usage.
- **Error handling:** Provides bounds-checked access with the `at()` method.
- **Comprehensive operations:**
  - Adding and removing elements with `push_back()` and `pop_back()`.
  - Resizing and reserving space.
  - Swapping contents with another `double_vector`.

## Class API

### Constructors
- **Default Constructor:** Creates an empty vector.
- **Parameterized Constructor:** Initializes a vector with a specified capacity.
- **Copy Constructor:** Creates a deep copy of another `double_vector`.

### Destructors
- **Destructor:** Properly cleans up allocated memory.

### Core Methods
- `size()`: Returns the current size of the vector.
- `capacity()`: Returns the current capacity of the vector.
- `empty()`: Checks if the vector is empty.
- `resize(n, val)`: Resizes the vector to `n` elements, initializing new elements to `val`.
- `reserve(n)`: Increases the capacity to at least `n`.
- `shrink_to_fit()`: Reduces capacity to match the size.
- `push_back(val)`: Adds a new element to the end of the vector.
- `pop_back()`: Removes the last element from the vector.
- `clear()`: Clears all elements in the vector.

### Element Access
- `operator[]`: Direct, unchecked access to elements.
- `at(n)`: Bounds-checked access to elements.
- `front()`: Accesses the first element.
- `back()`: Accesses the last element.
- `data()`: Provides a raw pointer to the underlying array.

### Iterators
- `begin()`: Returns an iterator to the beginning of the vector.
- `end()`: Returns an iterator to one past the last element of the vector.

### Utility
- `swap(other)`: Swaps the contents of the vector with another `double_vector`.

## Example Usage

Here’s how to use the `double_vector` class:

```cpp
#include <iostream>
#include "double_vector.h"

int main() {
    double_vector dv(5); // Create a vector with capacity 5
    for (std::size_t i = 0; i < 5; ++i) {
        dv.push_back(i * 1.1);
    }

    for (double_vector::iterator it = dv.begin(); it != dv.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    dv.resize(3);
    dv.push_back(9.9);
    std::cout << "Front: " << dv.front() << ", Back: " << dv.back() << std::endl;

    return 0;
}
