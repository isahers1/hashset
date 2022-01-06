/**
 * hashset.hpp
 *
 * Authors: (Your names here)
 *
 * Provides HashSet<T>, a set class template, using hash tables
 *
 * Part of CS70 Homework 8. This file may NOT be
 * shared with anyone other than the author(s) and
 * the current semester's CS70 staff without
 * explicit written permission from one of the
 * CS70 instructors.

 */

#ifndef HASHSET_HPP_INCLUDED
#define HASHSET_HPP_INCLUDED

#include <iostream>
#include <forward_list>

/* Our Hash Table
 *
 * TODO(Students): Fill this in
 * Explain what kind of hash table you implemented, and why you chose it.
 *
 * State the load factor you settled on, and your justification for
 * choosing that particular value.
 */

// Templated interfaces (e.g., the HashSet class declarations) go here
//
// Most users of this header file would be interested in interfaces: how does
// one use a HashSet<T>? What member functions does it provide? What parameters
// do they take?

template <typename T>
class HashSet {
 public:
    HashSet();
    HashSet(size_t s);
    ~HashSet();
    HashSet(const HashSet& orig) = delete;
    HashSet& operator=(const HashSet& rhs) = delete;

    // member functions
    /**
     * \brief Return number of elements in set
     * \return number of elements in set
     **/
    size_t size() const;

    /**
     * \brief Insert element in hashset
     * \param t is element to be inserted
     * \return othing
     **/
    void insert(const T& t);

    /**
     * \brief Check if element is in hashset
     * \param t is element to be check
     * \return boolean whether element was in set
     **/
    bool exists(const T& t) const;

    /**
     * \brief Return number of buckets in set
     * \return number of buckets in set
     **/
    size_t buckets() const;

    /**
     * \brief Return current loadfactor of the set
     * \return current loadfactor of the set
     **/
    double loadFactor() const;

    /**
     * \brief Return number of reallocations that have happened
     * \return number of reallocations that have happened
     **/
    size_t reallocations() const;

    /**
     * \brief Return number of collisions in set
     * \return number of collisions in set
     **/
    size_t collisions() const;

    /**
     * \brief Return maximal search performed so far in tree
     * \return maximal search performed so far in tree
     **/
    size_t maximal() const;


    std::ostream& showStatistics(std::ostream& out) const;

 private:
    size_t numBuckets_;
    size_t size_;
    size_t collisions_;
    size_t resizes_;
    std::forward_list<T>* buckets_;
    mutable size_t maximal_;

    void resize();

    static const double MAX_LOAD_FACTOR;
};

#include "hashset-private.hpp"

#endif
