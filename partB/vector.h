//
// Only for trivial types!!!!!!!!!!!!!!!!!!!!!!!!
//

#ifndef _VECTOR_H
#define _VECTOR_H

namespace mtm {

    template<typename T>
    class Vector {
    public:
        explicit Vector(size_t initial_size = 10);
        Vector(const Vector<T>& other);
        ~Vector();
        void add(const T &item);
        void remove(const T &item);
        void sort_int();
        int find(const T &item) const;
        int getCount() const;
        T& operator[](int i) const;
        Vector<T>& operator=(Vector<T> other);


    private:
        void resize();

        T *data;
        size_t size;
        size_t count;
    };


    template<typename T>
    Vector<T>::Vector(size_t initial_size) :
            data(new T[initial_size]),
            size(initial_size),
            count(0) {
    }

    template<typename T>
    Vector<T>::~Vector() {
        delete[] data;
    }

    template<typename T>
    void Vector<T>::resize() {
        auto temp = new T[size * 2];

        for (int i = 0; i < count; i++) {
            temp[i] = data[i];
        }
        delete[] data;

        size *= 2;
        data = temp;
    }

    template<typename T>
    void Vector<T>::add(const T &item) {
        if (count >= size) {
            resize();
        }
        data[count] = item;
        ++count;
    }

    template<typename T>
    void Vector<T>::remove(const T &item) {
        int index = find(item);
        data[index] = data[--count];
    }

    template<typename T>
    void Vector<T>::sort_int() {
        int i, j, min, temp;
        for (i = 0; i < count - 1; i++) {
            min = i;
            for (j = i + 1; j < count; j++) {
                if (data[j] < data[min]) {
                    min = j;
                }
            }
            temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
    }

    template<typename T>
    int Vector<T>::find(const T &item) const {
        for (int i = 0; i < count; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    int Vector<T>::getCount() const {
        return count;
    }

    template<typename T>
    T &Vector<T>::operator[](int i) const {
        return data[i];
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(Vector<T> other) {
        size = other.size;
        count = other.count;
        data = new T[other.size];
        for (int i = 0; i < count; i++) {
            data[i] = other[i];
        }
        return *this;
    }

    template<typename T>
    Vector<T>::Vector(const Vector<T> &other) : size(other.size), count(other.count){
        data = new T[other.size];
        for (int i = 0; i < count; i++) {
            data[i] = other[i];
        }
    }
}
#endif //PARTA_VECTOR_H
