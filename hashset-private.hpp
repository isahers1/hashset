/**
 * hashset-private.hpp
 * Authors: (your names here)
 *
 * Implements HashSet<T>, a hash-table class template

 * Part of CS70 Homework 8. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.

 */

#ifndef HASHSET_PRIVATE_HPP_INCLUDED

#define HASHSET_PRIVATE_HPP_INCLUDED

// Includes required for your templated code go here
#include <iostream>
#include <forward_list>

// Constant load factor
template <typename T>
const double HashSet<T>::MAX_LOAD_FACTOR = 0.75;

/**
 * We chose the value of 0.75 for the max load factor
 * based off of some brief online research. On sites
 * such as stackoverflow and geeksforgeeks we found that
 * 0.75 was a default value, which seems suitable for our
 * purposes.
**/

template <typename T>
HashSet<T>::HashSet() : numBuckets_(1), size_(0), collisions_(0),
      resizes_(0), buckets_{new std::forward_list<T>[1]}, maximal_(0) {}

template <typename T>
HashSet<T>::HashSet(size_t s) : numBuckets_(s), size_(0), collisions_(0),
      resizes_(0), buckets_{new std::forward_list<T>[s]}, maximal_(0) {}

template <typename T>
HashSet<T>::~HashSet() {
  delete[] buckets_;
}

template <typename T>
size_t HashSet<T>::size() const {
  return size_;
}

template <typename T>
double HashSet<T>::loadFactor() const {
  return size_/numBuckets_;
}

template <typename T>
size_t HashSet<T>::buckets() const {
  return numBuckets_;
}

template <typename T>
size_t HashSet<T>::reallocations() const {
  return resizes_;
}

template <typename T>
size_t HashSet<T>::collisions() const {
  return collisions_;
}

template <typename T>
size_t HashSet<T>::maximal() const {
  return maximal_;
}

template <typename T>
void HashSet<T>::insert(const T& element) {
// only insert unique elements
  if (!exists(element)) {
    size_t hashVal = myhash(element)%numBuckets_;
    // check for collisions before adding
    if (!(buckets_[hashVal].empty())) {
      ++collisions_;
    }

    buckets_[hashVal].push_front(element);
    ++size_;
    // check if we need to resize after adding element
    if (loadFactor() > MAX_LOAD_FACTOR) {
      resize();
    }
  }
}

template <typename T>
void HashSet<T>::resize() {
  // copy member variables that we need to remember
  size_t numBucketsCopy = numBuckets_;
  std::forward_list<T>* bucketsCopy = buckets_;

  // change member variable values
  size_ = 0;
  numBuckets_ *= 2;
  ++resizes_;
  collisions_ = 0;
  buckets_ = new std::forward_list<T>[numBuckets_];

  // Insert all elements of old array into our updated array
  for (size_t i = 0; i < numBucketsCopy; ++i) {
    for (auto item = bucketsCopy[i].begin();
    item != bucketsCopy[i].end(); ++item) {
      insert(*item);
    }
  }

  delete[] bucketsCopy;
}

template <typename T>
bool HashSet<T>::exists(const T& t) const {
  size_t hashVal = myhash(t)%numBuckets_;
  size_t newMaximal = 0;
  for (auto i = buckets_[hashVal].begin(); i != buckets_[hashVal].end(); ++i) {
    // update new maximal
    ++newMaximal;
    if (newMaximal > maximal_) {
      maximal_ = newMaximal;
    }

    if (*i == t) {
      return true;
    }
  }
  return false;
}

// Templated code for member functions goes here

template <typename Value>
std::ostream& HashSet<Value>::showStatistics(std::ostream& out) const {
      return out << reallocations() << " expansions"
                 << ", "
                 << "load factor " << loadFactor()
                 << ", "
                 << collisions() << " collisions"
                 << ", "
                 << "longest run " << maximal()
                 << std::endl;
    return out << "Statistics functions not implemented yet!" << std::endl;
}

#endif
