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

    // run iterations
    while (iter < max_iter) {
        
        // initialize parallel
        #pragma omp parallel for shared(u, f, Nm1, div6) private(i,j,k)
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    u[i][j][k] = div6 * (u[i-1][j][k] + u[i+1][j][k] + u[i][j-1][k] + u[i][j+1][k] + u[i][j][k-1] + u[i][j][k+1] + f[i][j][k]);
                }
            }
        }
        
        // increment iteration
        iter++;
    }
}
