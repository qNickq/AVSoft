#include <iostream>
#include <pthread.h>

#define NUM_READERS 12
#define NUM_WRITERS 1000

struct Shared
{
    void * data = nullptr;
    unsigned long size = 0;
};

void * read(void *);
void * write(void *);


static pthread_cond_t readingEnd;
static pthread_cond_t writingEnd;

static pthread_mutex_t mutexR;
static pthread_mutex_t mutexW;

static int readers = 0;
static int writers = 0;


int main()
{

    Shared* buff = new Shared;

    pthread_t threadsR[NUM_READERS];
    pthread_t threadsW[NUM_WRITERS];

    pthread_mutex_init(&mutexR, nullptr);
    pthread_mutex_init(&mutexW, nullptr);

    pthread_cond_init(&writingEnd, nullptr);
    pthread_cond_init(&readingEnd, nullptr);

    for(int i = 0, k = 0; i < NUM_WRITERS || k < NUM_READERS; ++i, ++k)
    {
        if(i < NUM_WRITERS)
        {
            int threadW = pthread_create(&threadsW[i], nullptr, write,  buff);

            if(threadW != 0)
            {
                printf("Thread cant be created!");
                return -1;
            }
        }
        if(k < NUM_READERS)
        {
            int threadR = pthread_create(&threadsR[k], nullptr, read,  buff);

            if(threadR != 0)
            {
                printf("Thread cant be created!");
                return -1;
            }
        }
    }


    for(int i = 0; i < NUM_WRITERS; ++i)
    {
        pthread_join(threadsW[i], nullptr);
    }
    for(int i = 0; i < NUM_READERS; ++i)
    {
        pthread_join(threadsR[i], nullptr);
    }

    printf("Buffer size: %lu\n", buff->size);

    free (buff->data);

    delete buff;

    return 0;
}


void* read(void* buffer)
{
    pthread_mutex_lock(&mutexR);

    readers++;

    if(writers != 0)
    {
        pthread_cond_wait(&writingEnd, &mutexR);
    }

    Shared *str = static_cast<Shared*>(buffer);

    printf("Reader -> %.*s\n", static_cast<int>(str->size), static_cast<char*>(str->data));

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
    char s = '$';

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

    Shared *str = static_cast<Shared*>(buffer);

    ++str->size;

    str->data = realloc(str->data, str->size);

    (static_cast<char*>(str->data))[str->size - 1] = s;

    printf("Writer -> %c\n", s);

    writers--;

    pthread_cond_broadcast(&writingEnd);

    pthread_mutex_unlock(&mutexR);
    pthread_mutex_unlock(&mutexW);

    return nullptr;
}
