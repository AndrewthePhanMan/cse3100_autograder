#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m1;
pthread_mutex_t m2;

void *thread1(void *arg)
{
    pthread_mutex_lock(&m1);
    sleep(1);
    pthread_mutex_lock(&m2);

    return NULL;
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&m2);
    sleep(1);
    pthread_mutex_lock(&m1);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}