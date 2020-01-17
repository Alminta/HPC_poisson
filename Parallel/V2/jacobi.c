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

    double tmp, sum, tol, tol_min;
    double div6 = 1.0 / 6.0;

    tol_min = tolerance * tolerance;
    tol = 2.0 * tol_min;
    
    for (iter = 0 ; iter < max_iter; iter++) {

        // run inner grid iterations
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


/*void
jacobi(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance)
{
    int i, j, k;
    int Nm1 = N - 1;
    int iter = 0;

    double ***u3;

    double tmp, sum, tol, tol_min;
    double div6 = 1.0 / 6.0;

    tol_min = tolerance * tolerance;
    tol = 2.0 * tol_min;

    #pragma omp parallel
    {

    while (iter < max_iter) {

        // #pragma omp barrier // ensure all threads are in loop before resetting tol
        // tol = 0.0;

        // run inner grid iterations
        #pragma omp for \
        // firstprivate(u1, u2) \
        // lastprivate(u2) \
        // shared(u1,u2) \
        // schedule(static) \
        // reduction(+ : tol)
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    u2[i][j][k] = div6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                    // u2[i][j][k] = tmp;
                    // tmp -= u1[i][j][k];
                    // tol += tmp * tmp;
                }
            }
        }

        #pragma omp single
        {
        // swap pointers
        u3 = u1; 
        u1 = u2;
        u2 = u3;
        
        // increment iteration
        iter++;
        }
    }
    }
}
*/