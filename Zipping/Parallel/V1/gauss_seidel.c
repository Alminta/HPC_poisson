/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void
gauss_seidel(double ***u, double ***f, int N, int max_iter, double tolerance) 
{
    int i, j, k;
    int Nm1 = N - 1;
    int iter = 0;

    double div6 = 1.0 / 6.0;

    // initialize parallel
    #pragma omp parallel shared(u, f, Nm1, div6, iter, max_iter) private(i, j, k) 
    {

    // run iterations
    for (iter = 0 ; iter < max_iter; ) {

        #pragma omp for ordered(2)
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
            #pragma omp ordered depend(sink:i-1,j) depend(sink:i, j-1)
                for (k = 1; k < Nm1; k++){
                    u[i][j][k] = div6 * (u[i-1][j][k] + u[i+1][j][k] + u[i][j-1][k] + u[i][j+1][k] + u[i][j][k-1] + u[i][j][k+1] + f[i][j][k]);
                }
            #pragma omp ordered depend(source)
            }
        }

        #pragma omp single
        {
        // increment iterator
        iter++;
        }
    }
    } // end parallel
}
