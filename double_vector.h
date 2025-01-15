#ifndef double_vector_H_DEFINED
#define double_vector_H_DEFINED

#include <cstddef>

/**
 * @class double_vector
 * @brief A toy vector class using basic a basic double array.
 */
class double_vector {
 private:
  double *data_;
  std::size_t size_;
  std::size_t capacity_;

  /**
   * @brief reallocate - Private helper to reallocate array to new capacity
   * @param n The new capacity size. If n is less than size then only n elements
   * will be copied
   */
  void reallocate(std::size_t n);

  /**
   * @brief copy_contents - Private helper copies elements from one array to
   * another.
   * @param to Destination array pointer.
   * @param from Source array pointer.
   * @param n Number of elements to copy.
   */
  void copy_contents(double *from, double *to, std::size_t n);

 public:
  /**
   * @brief double_vector - Default constructor. Initializes an empty
   * double_vector with size and capacity to 0.
   */
  double_vector();

  /**
   * @brief double_vector - Constructs a double_vector with the specified
   * capacity and size.
   * @param capacity Initial capacity and size of the vector, initializing all
   * values to 0.
   */
  double_vector(std::size_t capacity);

  /**
   * @brief double_vector - Copy constructor.
   * @param rhs The double_vector to copy from.
   */
  double_vector(const double_vector &rhs);

  /**
   * @brief operator= - Copy assignment operator.
   * @param rhs The double_vector to copy from.
   * @return Reference to this double_vector.
   */
  double_vector &operator=(const double_vector &rhs);

  /**
   * @brief ~double_vector - Destructor.
   */
  ~double_vector();

  /**
   * @brief size - Gets the current number of elements in the vector.
   * @return The size of the vector.
   */
  std::size_t size() const;

  /**
   * @brief max_size - Gets the maximum size the vector could be.
   * @return The maximum possible size.
   */
  std::size_t max_size() const;

  /**
   * @brief capacity - Gets the current capacity of the vector.
   * @return The maximum number of elements the vector can hold before resizing.
   */
  std::size_t capacity() const;

  /**
   * @brief resize - Resizes the vector to contain n elements. If n is less than
   * size, than all values greater than n to size are set to 0. Otherwise size
   * increased to n with default value of 0 set.
   * @param n New size of the vector.
   */
  void resize(std::size_t n);

  /**
   * @brief resize - Resizes the vector to contain n elements. If n is less than
   * size, than all values greater than n to size are set to val. Otherwise size
   * increased to n with value set to val.
   * @param n New size of the vector.
   * @param val Value to initialize new elements.
   */
  void resize(std::size_t n, double val);

  /**
   * @brief empty - Checks if the vector is empty.
   * @return True if the vector is empty, false otherwise.
   */
  bool empty() const;

  /**
   * @brief reserve - Increases the capacity of the vector to n if n is greater
   * than current capacity.
   * @param n New capacity.
   */
  void reserve(std::size_t n);

  /**
   * @brief shrink_to_fit - Reduces capacity to fit the current size.
   */
  void shrink_to_fit();

  /**
   * @brief push_back - Adds an element to the end of the vector.
   * @param val The value to add.
   */
  void push_back(const double &val);

  /**
   * @brief pop_back - Removes the last element of the vector.
   */
  void pop_back();

  /**
   * @brief swap - Swaps the contents of this vector with another.
   * @param other The other double_vector to swap with.
   */
  void swap(double_vector &other);

  /**
   * @brief clear - Empties the vector of all values and sets size to 0.
   */
  void clear();

  /**
   * @brief operator[] - Accesses an element at the specified index.
   * @param n Index of the element.
   * @return Reference to the element at index n.
   */
  double &operator[](size_t n);

  /**
   * @brief at - Accesses an element at the specified index with bounds
   * checking.
   * @param n Index of the element.
   * @return Reference to the element at index n.
   * @throws range_error if n is out of bounds.
   */
  double &at(size_t n) const;

  /**
   * @brief front - Accesses the first element in the vector.
   * @return Reference to the first element.
   */
  double &front() const;

  /**
   * @brief back - Accesses the last element in the vector.
   * @return Reference to the last element.
   */
  double &back() const;

  /**
   * @brief data - Gets a pointer to the data_ array.
   * @return Pointer to the array of elements.
   */
  double *data() const;

  /**
   * @class iterator
   * @brief An iterator class for double_vector.
   */
  class iterator {
   private:
    double *ptr_;

    /**
     * @brief iterator - Private constructor.
     * @param ptr Pointer to the starting element for the iterator.
     */
    iterator(double *ptr);

    /**
     * friend double_vector to allow access to constructor
     */
    friend class double_vector;

   public:
    /**
     * @brief operator++ - Pre-increment operator.
     * @return Reference to the incremented iterator.
     */
    iterator &operator++();

    /**
     * @brief operator++ - Post-increment operator.
     * @return Copy of the iterator before incrementing.
     */
    iterator operator++(int);

    /**
     * @brief operator-- - Pre-decrement operator.
     * @return Reference to the decremented iterator.
     */
    iterator &operator--();

    /**
     * @brief operator-- - Post-decrement operator.
     * @return Copy of the iterator before decrementing.
     */
    iterator operator--(int);

    /**
     * @brief operator* - Dereference operator to access the element.
     * @return Reference to the element pointed to by the iterator.
     */
    double &operator*() const;

    /**
     * @brief operator== - Equality operator to compare two iterators.
     * @param other The iterator to compare with.
     * @return True if the iterators point to the same element, false otherwise.
     */
    bool operator==(const iterator &other) const;

    /**
     * @brief operator!= - Inequality operator to compare two iterators.
     * @param other The iterator to compare with.
     * @return True if the iterators point to different elements, false
     * otherwise.
     */
    bool operator!=(const iterator &other) const;
  };

  /**
   * @brief begin - Returns an iterator at the beginning of the vector.
   * @return An iterator at the first element.
   */
  iterator begin();

  /**
   * @brief end - Returns an iterator at the end of the vector.
   * @return An iterator at one past the last element.
   */
  iterator end();
};

#endif
