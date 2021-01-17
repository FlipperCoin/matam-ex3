//
// Created by Itai on 17/01/2021.
//

#ifndef _SHAREDPOINTER_H
#define _SHAREDPOINTER_H
namespace mtm {
    template<typename T>
    class SharedPointer
    {
    public:
        explicit SharedPointer(T* pointer) : pointer(pointer), ref_count(new int(1)) {};

        SharedPointer() : pointer(nullptr), ref_count(new int(0)) {};

        ~SharedPointer() {
            if ((*ref_count)-- == 1) {
                delete pointer;
                delete ref_count;
            }
        }

        SharedPointer(const SharedPointer& other) {
            ref_count = other.ref_count;
            pointer = other.pointer;

            (*ref_count)++;
        }

        SharedPointer& operator=(const SharedPointer& other) {
            if (&other == this) {
                return *this;
            }

            ref_count = other.ref_count;
            pointer = other.pointer;

            (*ref_count)++;

            return *this;
        }

        T& operator*() {
            return *pointer;
        }
        const T& operator*() const{
            return *pointer;
        }
        T* operator->() {
            return pointer;
        }
        const T* operator->() const {
            return pointer;
        }

    private:
        T* pointer;
        int* ref_count;
    };
}
#endif
