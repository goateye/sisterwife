//to compile this turd: gcc sisterwife.c -o sisterwife -lpthread 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>


int howlong;
int NTHREADS;
void *cpukill(void *x)
{
  int tid;
  time_t t1;
  int count;

  count = 0;
  tid = *((int *) x);
  t1 = time(0) + howlong;
  while( time(0) < t1 )
        {
                if( ( count % 10000000 ) == 0 )
                {
                        //printf( "." );
                        fflush( stdout );
                }
        count++;
        }




  return NULL;
}


int main(int argc, char** argv)
{
    unsigned long mem;
    pid_t pid;
int count;
time_t t1;
 pthread_t threads[NTHREADS];
  int thread_args[NTHREADS];
  int rc, i;
count = 0;
NTHREADS = 8;
howlong = 30;
mem = 1024*1024*512; //512mb
if (argc  <= 1) 
	{
  printf("\nsisterwife - Goateye Software - Use memory and cpu\n\n");
  printf("Example:\n");
           
  printf("         sisterwife 800 60 8  - eat 800mb of memory and max out cpu for 60 sec, with 8 threads\n\n");
  exit(0);
}
if (argc > 1) 
	{
		mem = (atol(argv[1])*1024)*1024;
		//printf("mem: %d\n", mem);
	}
if (argc > 2) 
	{
		howlong = atoi(argv[2]);
		//printf("mem: %d\n", mem);
	}
if (argc > 3)
        {
                NTHREADS = atoi(argv[3]);
                //printf("mem: %d\n", mem);
        }

char* ptr = malloc(mem);
  memset(ptr, 0, mem);

printf("mem: %ld\n", mem);

for (i=0; i<NTHREADS; ++i)
    {
      thread_args[i] = i;
      printf("spawning thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, cpukill, (void *) &thread_args[i]);
    }

printf("Wife malloc'd: %ldmb of ram and is going to chew up cpu for %d sec. \n",(mem/1024)/1024, howlong);

 for (i=0; i<NTHREADS; ++i) {
    rc = pthread_join(threads[i], NULL);
  } 

      free(ptr);

      exit(0);

}

