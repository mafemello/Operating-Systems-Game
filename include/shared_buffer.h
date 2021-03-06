#ifndef SHARED_BUFFER
#define SHARED_BUFFER

#include <semaphore.h>

template <typename T> class SharedBuffer {
    public: 
        SharedBuffer() {
            sem_init(&can_read, 0, 0);
            sem_init(&can_write, 0, 0);
        }

        SharedBuffer(T content) {
            this->content = content;
            sem_init(&can_read, 0, 0);
            sem_init(&can_write, 0, 0);
        }

        T read() {
            allow_write();
            sem_wait(&can_read);
            return content;
        }

        void write(T content) {
            sem_wait(&can_write);
            this->content = content;
            allow_read();
        }
    
    private:
        sem_t can_read;
        sem_t can_write;
        T content;

        void allow_read() {
            sem_post(&can_read);
        }

        void allow_write() {
            sem_post(&can_write);
        }
};

#endif
