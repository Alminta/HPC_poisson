/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <stdio.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void
jacobi(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance)
{
    int i, j, k;
    int Nm1 = N - 1;
    int iter = 0;

    double ***u3;
    double div6 = 1.0 / 6.0;
    
    // run iterations
    for (iter = 0; iter < max_iter; iter++) {

        #pragma omp for
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    u2[i][j][k]  = div6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                }
            }
        }

        // swap pointers
        u3 = u1; 
        u1 = u2;
        u2 = u3;
    }
}