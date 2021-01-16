//
// Created by Itai on 16/01/2021.
//

#include <exception>
#include <memory>
#include <vector>
#include <iostream>

namespace dry {

    class BadInput : std::exception {};

    template <typename T>
    std::vector<T> slice(std::vector<T> vec, int start, int step, int stop);

    template<typename T>
    bool isBadInput(const std::vector<T> &vec, int start, int step, int stop);

    template <typename T>
    std::vector<T> slice(std::vector<T> vec, int start, int step, int stop) {
        if (isBadInput(vec, start, step, stop)) {
            throw BadInput();
        }

        if (start >= stop) {
            return std::vector<T>();
        }

        std::vector<T> slicedVector;
        for (auto iter = (vec.begin() + start); iter < (vec.begin() + stop); iter += step) {
            slicedVector.push_back(*iter);
        }

        return slicedVector;
    }

    template<typename T>
    bool isBadInput(const std::vector<T> &vec, int start, int step, int stop) {
        size_t vec_size = vec.size();
        if (start < 0 || stop < 0) {
            return true;
        }

        auto long_start = static_cast<size_t>(start);
        auto long_stop = static_cast<size_t>(stop);
        if (long_start >= vec_size) {
            return true;
        }

        if (long_stop > vec_size) {
            return true;
        }

        if (step <= 0) {
            return true;
        }

        return false;
    }

    class A {
    public:
        std::vector<std::shared_ptr<int>> values;
        void add(int x) {
            values.push_back(std::make_shared<int>(x));
        }
    };
}

using dry::slice;
using dry::A;

int main(int argc, char **argv) {
    A a, sliced;
    a.add(0); a.add(1); a.add(2); a.add(3); a.add(4); a.add(5);
    sliced.values = slice(a.values, 1, 1, 4);
    *(sliced.values[0]) = 800;
    std::cout << *(a.values[1]) << std::endl;
    return 0;
}