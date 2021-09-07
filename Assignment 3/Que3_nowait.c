#include <stdlib.h>  
#include <stdio.h>   
#include <omp.h>     
#include <time.h>

//firstprivate - shared - private
int main (int argc, char *argv[]) 
{
	clock_t start, end;
  
    /* Recording the starting clock tick.*/
    start = clock();


	int * a;
	int * b; 
	int * c;
        
    int n = 250;             
	int n_per_thread;                 
	int total_threads = 2;   
	int i;     
      
    a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);

    for(i=0; i<n; i++) 
    {
        a[i] = i;
    }
    for(i=0; i<n; i++) 
    {
    	b[i] = i;
    }   
        
	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	
	#pragma omp for nowait 
        for(i=0; i<n; i++) 
        {
			c[i] = a[i]+b[i];
			printf("Thread %d works on element %d\n", omp_get_thread_num(), i);
        }
	printf("Vector Addition :\n");
	printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");
    for(i=0; i<n; i++) 
    {
		printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
    }
	
    free(a);  
    free(b); 
    free(c);
	
	end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nTime taken : %0.4f\n",time_taken);
	return 0;
}
