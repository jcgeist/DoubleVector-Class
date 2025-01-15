#include <format>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "double_vector.h"

#define maxSize (std::pow(2,32)/sizeof(double)) - 1

double_vector::double_vector(){
    this->data_ = nullptr;
    this->size_ = 0;
    this->capacity_ = 0;
}

double_vector::double_vector(std::size_t capacity){
    if(capacity > maxSize) capacity = maxSize;
    this->data_ = new double[capacity]();
    this->size_ = capacity;
    this->capacity_ = capacity;
}

double_vector::double_vector(const double_vector &rhs){
    this->size_ = rhs.size();
    this->capacity_ = rhs.capacity();
    this->data_ = new double[this->capacity_];
    copy_contents(rhs.data(), this->data_, this->size_);
}

double_vector& double_vector::operator=(const double_vector &rhs){
    this->size_ = rhs.size();
    this->capacity_ = rhs.capacity();
    this->data_ = new double[this->capacity_];
    copy_contents(rhs.data(), this->data_, this->size_);
    return *this;
}

double_vector::~double_vector(){
    delete[] this->data_;
}

std::size_t double_vector::size() const{
    return this->size_;
}

std::size_t double_vector::max_size() const{
    return maxSize;
}

std::size_t double_vector::capacity() const{
    return this->capacity_;
}

void double_vector::resize(std::size_t n){
    resize(n, 0);
}

void double_vector::resize(std::size_t n, double val){
    bool n_small = n < this->size_;
    std::size_t start_at = n_small ? n : this->size_;
    std::size_t end_at = n_small ? this->size_ : n;
    if(n > this->capacity_){
        reallocate(n);
    }
    for(std::size_t i = start_at; i < end_at; i++){
        this->data_[i] = val;
    }
    this->size_ = n;
}

bool double_vector::empty() const{
    return (this->size_ == 0);
}

void double_vector::reserve(std::size_t n){
    if(n > this->capacity_){
        reallocate(n);
    }
}

void double_vector::shrink_to_fit(){
    if(this->size_ != this->capacity_) reallocate(this->size_);
}

void double_vector::push_back(const double &val){
    if(this->size_ >= this->capacity_){
        std::size_t new_cap = (this->capacity_ * 2 < maxSize) ? this->capacity_ * 2 : maxSize;
        if(new_cap == 0) new_cap = 1;
        reallocate(new_cap);
    }
    this->data_[this->size_] = val;
    this->size_++;
}

void double_vector::pop_back(){
    if(!empty()){
        this->size_--;
        this->data_[this->size_] = 0;
    }
}

void double_vector::swap(double_vector &other){
    double *temp_data = other.data();
    std::size_t temp_size = other.size();
    std::size_t temp_capacity = other.capacity();
    other.size_ = this->size_;
    other.capacity_ = this->capacity_;
    other.data_ = this->data_;
    this->size_ = temp_size;
    this->capacity_ = temp_capacity;
    this->data_ = temp_data;
}

void double_vector::clear(){
    std::fill(this->data_, this->data_ + this->size_, 0);
    this->size_ = 0;
}

double& double_vector::operator[](size_t n){
    return this->data_[n];

}

double& double_vector::at(size_t n) const{
    if(n >= this->size_){
        throw(std::range_error(std::format("Error: index \"{}\" is out of bounds.\n", n)));
    }
    return this->data_[n];
}

double& double_vector::front() const{
    return this->data_[0];
}

double& double_vector::back() const{
    return this->data_[this->size_-1];
}

double* double_vector::data() const{
    return this->data_;
}

void double_vector::reallocate(std::size_t n){
    this->capacity_ = n;
    double *temp = new double[n];
    n = (this->size_ > n) ? n : this->size_;
    copy_contents(this->data_, temp, n);
    delete[] this->data_;
    this->data_ = temp;
}

void double_vector::copy_contents(double *from, double *to, std::size_t n){
    for(std::size_t i = 0; i < n; i++){
        to[i] = from[i];
    }
}

double_vector::iterator::iterator(double* ptr) : ptr_(ptr) {}

double_vector::iterator& double_vector::iterator::operator++(){
    ++ptr_;
    return *this;
}

double_vector::iterator double_vector::iterator::operator++(int){
    double_vector::iterator temp = *this;
    ++ptr_;
    return temp;
}

double_vector::iterator& double_vector::iterator::operator--(){
    --ptr_;
    return *this;
}

double_vector::iterator double_vector::iterator::operator--(int){
    double_vector::iterator temp = *this;
    --ptr_;
    return temp;
}

double& double_vector::iterator::operator*() const{
    return *ptr_;
}

bool double_vector::iterator::operator==(const iterator &other) const{
    return ptr_ == other.ptr_;
}

bool double_vector::iterator::operator!=(const iterator &other) const{
    return ptr_ != other.ptr_;
}

double_vector::iterator double_vector::begin(){
    return double_vector::iterator(this->data_);
}

double_vector::iterator double_vector::end(){
    return double_vector::iterator(this->data_ + this->size_);
}