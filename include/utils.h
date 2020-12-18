#ifndef UTILS
#define UTILS

#include<string>

void write_any_input();

template<class T> void delete_and_assign(T **origin, T *source) {
    T *to_delete = *origin;
    *origin = source;
    delete to_delete;
}

#endif
