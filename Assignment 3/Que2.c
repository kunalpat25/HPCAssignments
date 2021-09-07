/* compute matrix A multiplied by matrix B; the results are stored in matrix C */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//size of resultant matrix - N*M
#define N 250 /* number of rows in matrix A */
#define P 100 /* number of columns in matrix A */
#define M 100 /* number of columns in matrix B */
#define threads_cnt 2

int main (int argc, char *argv[])
{
    clock_t start, end;
  
    /* Recording the starting clock tick.*/
    start = clock();


    int tid, nthreads, i, j, k;
    double a[N][P], b[P][M], c[N][M];
    /*** Create a parallel region explicitly scoping all variables ***/

    omp_set_num_threads(threads_cnt);
    #pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Starting matrix multiple with %d threads\n",nthreads);
            printf("Initializing matrices...\n");
        }

        /*** Initialize matrices ***/
        #pragma omp for
            for (i=0; i<N; i++)
                for (j=0; j<P; j++)
                    a[i][j]= i+j;
        
        #pragma omp for
            for (i=0; i<P; i++)
                for (j=0; j<M; j++)
                    b[i][j]= i*j;
         
        #pragma omp for
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    c[i][j]= 0;

        /*** Do matrix multiply sharing iterations on outer loop ***/
        /*** Display who does which iterations for demonstration purposes ***/
        
        printf("Thread %d starting matrix multiply...\n",tid);
        #pragma omp for
            for (i=0; i<N; i++)
            {
                printf("Thread=%d did row=%d\n",tid,i);
                for(j=0; j<M; j++)
                    for (k=0; k<P; k++)
                        c[i][j] += a[i][k] * b[k][j];
            }
     } /*** End of parallel region ***/
    
    /*** Print results ***/
    printf("******************************************************\n");
    printf("Result Matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%6.2f ", c[i][j]);
        printf("\n");
    }
    
    printf("******************************************************\n");

    
    
    printf ("Done.\n\n");
   end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nTime taken : %0.4f\n",time_taken);
    return(0);
}
