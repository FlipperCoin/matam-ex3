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
        explicit SharedPointer(T* pointer) : m_pointer(pointer), ref_count(1) {};

        ~SharedPointer() {
            if (ref_count-- == 1) {
                delete pointer;
            }
        }

        SharedPointer(SharedPointer& other) {
            other.ref_count++;
            ref_count = other.ref_count;
            pointer = other.pointer;
        }
        // by-value to use copy constructor
        SharedPointer& operator=(SharedPointer other) {
            ref_count = other.ref_count;
            pointer = other.pointer;
        }

        T& operator*() {
            return *pointer;
        }
        const T& operator*() const{
            return *pointer;
        }

    private:
        T* pointer;
        int ref_count;
    };
}
#endif _SHAREDPOINTER_H
