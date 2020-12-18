#ifndef UTILS
#define UTILS

template<class T> void delete_and_assign(T **origin, T *source) {
    T *to_delete = *origin;
    *origin = source;
    delete to_delete;
}

#endif
