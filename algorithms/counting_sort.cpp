#include <iostream>
#include <vector>
#include <map>
#include <iterator>

template<typename Iter>
void counting_sort(Iter begin, Iter end) {
    std::map<decltype(typename std::iterator_traits<Iter>::value_type()), int> count;

    for(auto it = begin; it != end; it++)
        ++count[*it];

    for (auto& pair : count) {
        while (pair.second > 0) {
            *begin = pair.first;
            ++begin;
            --pair.second;
        }
    }

}