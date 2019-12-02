#include <iostream>
#include <pthread.h>

#define NUM_READERS 10
#define NUM_WRITERS 100

void * read(void *);
void * write(void *);

static pthread_cond_t readingEnd;
static pthread_cond_t writingEnd;

static pthread_mutex_t _mutexR;
static pthread_mutex_t _mutexW;

static int readers = 0;
static int writers = 0;

static unsigned long size_buffer = 0;


int main()
{
    char* buff = new char[0];

    pthread_t threadsR[NUM_READERS];
    pthread_t threadsW[NUM_WRITERS];

    pthread_mutex_init(&_mutexR, nullptr);
    pthread_mutex_init(&_mutexW, nullptr);

    pthread_cond_init(&writingEnd, nullptr);
    pthread_cond_init(&readingEnd, nullptr);

    for(int i = 0; i < NUM_WRITERS; ++i)
    {
        int thread = pthread_create(&threadsW[i], nullptr, write, buff);

        if(thread != 0)
        {
            return 1;
        }
    }

    for(int i = 0; i < NUM_READERS; ++i)
    {
        int thread = pthread_create(&threadsR[i], nullptr, read, buff);

        if (thread != 0)
        {
            return 1;
        }
    }

    for(int i = 0; i < NUM_READERS; ++i)
    {
        int success = pthread_join(threadsR[i], nullptr);

        if(success != 0)
        {
            return 1;
        }
    }

    for(int i = 0; i< NUM_WRITERS; ++i)
    {
        int success = pthread_join(threadsW[i], nullptr);

        if(success != 0)
        {
            return 1;
        }
    }

    printf("Буфер записи : %s\n", buff);

    delete[] buff;

    return 0;
}


void * read(void * buffer)
{
    pthread_mutex_lock(&_mutexR);

    readers++;

    if(writers != 0)
    {
        pthread_cond_wait(&writingEnd, &_mutexR);
    }

     printf("Читаталь -> %s\n", static_cast<char*>(buffer));

    readers--;

    if(readers == 0)
    {
        pthread_cond_signal(&readingEnd);
    }
    pthread_mutex_unlock(&_mutexR);


    return nullptr;
}

void * write(void * buffer)
{      
    pthread_mutex_lock(&_mutexW);

    writers++;

    pthread_mutex_lock(&_mutexR);

    if(writers != 1)
    {
        if(readers != 0)
        {
            pthread_cond_wait(&readingEnd, &_mutexW);
        }
    }

    size_buffer++;

    char s = '$';

    buffer = realloc(buffer, size_buffer + sizeof(s));

    static_cast<char*>(buffer)[size_buffer - 1] = s;

    printf("Писатель -> %c\n", s);

    writers--;

    pthread_cond_broadcast(&writingEnd);

    pthread_mutex_unlock(&_mutexR);
    pthread_mutex_unlock(&_mutexW);

    return nullptr;
}
