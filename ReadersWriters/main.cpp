#include <iostream>
#include <pthread.h>

#define NUM_READERS 20
#define NUM_WRITERS 10000

void * read(void *);
void * write(void *);

struct shared
{
    void * data = nullptr;
    unsigned long size_buffer = 0;
};

static pthread_cond_t readingEnd;
static pthread_cond_t writingEnd;

static pthread_mutex_t mutexR;
static pthread_mutex_t mutexW;

static int readers = 0;
static int writers = 0;


int main()
{
    setlocale(LC_CTYPE, "Russian");


    shared *buff = new shared;

    pthread_t threadsR[NUM_READERS];
    pthread_t threadsW[NUM_WRITERS];

    pthread_mutex_init(&mutexR, nullptr);
    pthread_mutex_init(&mutexW, nullptr);

    pthread_cond_init(&writingEnd, nullptr);
    pthread_cond_init(&readingEnd, nullptr);

    for(int i = 0; i < NUM_WRITERS; ++i)
    {
        int thread = pthread_create(&threadsW[i], nullptr, write,  &buff);

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

    printf("Buffer : %s\n", buff);

    //free(buff);

    return 0;
}


void * read(void * buffer)
{
    pthread_mutex_lock(&mutexR);

    readers++;

    if(writers != 0)
    {
        pthread_cond_wait(&writingEnd, &mutexR);
    }
     printf("Reader -> %s\n", buffer);

    readers--;

    if(readers == 0)
    {
        pthread_cond_signal(&readingEnd);
    }
    pthread_mutex_unlock(&mutexR);


    return nullptr;
}

void * write(void * buffer)
{      

    pthread_mutex_lock(&mutexW);

    writers++;

    pthread_mutex_lock(&mutexR);

    if(writers != 1)
    {
        if(readers != 0)
        {
            pthread_cond_wait(&readingEnd, &mutexW);
        }
    }
    shared* str = static_cast<shared*>(buffer);
    unsigned long size = str->size_buffer++;

    char s = '$';

    buffer = new char[size];

    if(buffer != nullptr)
    {
        static_cast<char*>(str->data)[size] = s;
    }
    else
    {
        return nullptr;
    }
    printf("Writer -> %c\n", s);

    writers--;

    pthread_cond_broadcast(&writingEnd);

    pthread_mutex_unlock(&mutexR);
    pthread_mutex_unlock(&mutexW);

    return nullptr;
}
