#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


//firstprivate - shared - shared
int main (int argc, char *argv[])
{
	int *a;
	int *b;
	int *c;

    int n = 8;
	int n_per_thread;
	int total_threads = 4;
	int i;

    a = (int *)malloc(sizeof(int)*n);
	b = (int *)malloc(sizeof(int)*n);
	c = (int *)malloc(sizeof(int)*n);

    for(i=0; i<n; i++)
    {
        a[i] = i+(i/2);
    }
    for(i=0; i<n; i++)
    {
    	b[i] = i*(i/2);
    }

	omp_set_num_threads(total_threads);

	n_per_thread = n/total_threads;

	#pragma omp parallel for firstprivate(b) shared(a, c) shared(i)
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

	return 0;
}
