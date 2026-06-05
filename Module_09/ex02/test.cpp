#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include "test.hpp"



int main()
{
    int arr[] = {11,2,17,0,16,8,6,15,10,3,21,1,18,9,14,19,12,5,4,20,13,7};
    const std::size_t size = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> seq(arr, arr + size);

    // vector
    {
        std::vector<int> v(seq.begin(), seq.end());
        typedef std::vector<int>::iterator vit;
        vit *it_array = ford_johnson(v);
        std::cout << "vector: ";
        print_iter_array<vit>(it_array, size);
        delete[] it_array;
    }
    return 0;
    // deque
    {
        std::deque<int> d(seq.begin(), seq.end());
        typedef std::deque<int>::iterator dit;
        dit *it_array = ford_johnson(d);
        std::cout << "deque:  ";
        print_iter_array<dit>(it_array, size);
        delete[] it_array;
    }

    // list
    {
        std::list<int> l(seq.begin(), seq.end());
        typedef std::list<int>::iterator lit;
        lit *it_array = ford_johnson(l);
        std::cout << "list:   ";
        print_iter_array<lit>(it_array, size);
        delete[] it_array;
    }

    return 0;
}
