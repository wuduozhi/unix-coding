#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
 
volatile int sv=10;
volatile int x,y,temp=10;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;
pthread_t child1,child2,child3;
int condition=1,val=1;
int count=1;
  
void *ChildThread1(void *arg)
{
    pthread_mutex_lock (&mut);
    printf("wait called\n");
    while(count<10)                      //if while loop with signal complete first don't wait
    {
        printf("In wait\n");
        pthread_cond_wait(&con, &mut);  //wait for the signal with con as condition variable
    }
    x=sv;
    x++;
    sv=x;
    printf("The child1 sv is %d\n",sv);
    pthread_mutex_unlock (&mut);
}

void *ChildThread2(void *arg)
{
 
    while(count<10)
    {
        pthread_mutex_lock (&mut);
        pthread_cond_signal(&con);  //wake up waiting thread with condition variable
                                    //con if it is called before this function
        sleep(3);
        if(val==1)
        {
            y=sv;
            y--;
            sv=y;
            printf("The child2 sv is %d\n",sv);
            val++;
        }
        count++;
        pthread_mutex_unlock (&mut);
         
    }
    printf("mutex released\n");
    printf("chil2 exit\n");
}

int main(void)
{
    int co=1;
    pthread_create(&child1,NULL,ChildThread1,NULL);
    pthread_create(&child2,NULL,ChildThread2,NULL);
    pthread_join(child1,NULL);
    pthread_join(child2,NULL);
 
    pthread_cond_destroy(&con);
    pthread_mutex_destroy(&mut);
    pthread_exit(NULL);
    return 0;
}
