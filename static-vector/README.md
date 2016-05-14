# Static Vector

```cpp
template <typename T, std::size_t N> class static_vector
```

static_vector aims to be a mixture between std::vector and std::array. The overall capacity is set at compile time
but static_vector acts dynamically like std::vector would.

It's currently a work-in-progress and is rather feature-less compared to its STL bretheren but it does offer
modern C++ container iterator syntax and is compatible with other STL algorithms.

Example:
```cpp
  // it should be transform-able
  {
    // declare 2 static_vectors
    std::size_t const size = 32;
    regulus::static_vector<int, size> a;
    decltype(a) b;
    
    // no fill() method yet but emplace_back()
    // suffices for building the vector
    for (int i = 0; i < (int ) size; ++i) {
      a.emplace_back(i);
    }
    
    // resize to ensure proper iteration
    // resize() will default construct elements
    b.resize(size);
    
    assert(a.size() == size);
    assert(a.size() == b.size());
    
    // map over our sequence and store the result in b
    std::transform(a.begin(), a.end(), b.begin(), [](int x)
    {
      return x * x;
    });
    
    // if this passes, it means at least part of it works!
    for (int i = 0; i < (int ) size; ++i) {
      assert(b[i] == i * i);
    }
  }
```

## Typedefs
```cpp
    // Member Types
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer; 
```

## Methods



##### static_vector(void)
Default constructs the vector to a size of 0.

##### static_vector(const_reference init)
Constructs the vector and fills it to capacity with copies of init.


##### reference at(size_type const pos)
##### const_reference at(size_type const pos) const
Element access that will throw an out of range exception.

##### reference operator[](size_type const pos)
##### const_reference operator[](size_type const pos) const
Array-like element access.

##### reference front(void)
##### const_reference front(void) const
Get a reference to the first element in the vector.

##### reference back(void)
##### const_reference back(void) const
Get a reference to the last element in the vector.

##### iterator begin(void)
Return an iterator the beginning of the vector.

##### iterator end(void)
Return a one-past-the-end iterator. Should not be dereferenced.

##### size_type size(void) const
Obtain the current size of the vector.

##### iterator insert(iterator it, const_reference val)
Inserts a copy of `val` to the location `it`. This shifts all
elements to the right so this is an `O(n)` operation. Is most 
efficient when inserting elements towards the end of the vector
and is least efficient when inserting at the front.

##### iterator erase(iterator it)
Erase the data pointed at by it and return an iterator
to element that came after `it`. Will return the `end()`
iterator in the case that `it` is the last element.

##### template <typename ...Args>
##### void emplace_back(Args&& ...args)
Construct an element in-place at the end of the vector.

##### void pop_back(void)
Remove the last element of the vector.

##### void resize(size_type const count)
Default construct elements at the end of the vector
until the `size()` is equal to `count`.

##### static_vector slice(size_type const pos)
Move elements of the current vector from `[pos, size)` to
a new vector.
