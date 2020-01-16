/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>

/* 
void
gauss_seidel(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance) 
{
    int i, j, k;
    int Nm1 = N-1;
    int iter = 0;

    double tmp, tmp2;
    double tol = 2.0 * tolerance;
    double oo6 = 1.0 / 6.0;

    while (tol > tolerance && iter < max_iter) {

        tol = 0.0;

        // run inner grid iterations
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    tmp = u1[i][j][k];
                    u1[i][j][k] = oo6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                    tmp -= u1[i][j][k];
                    tol += tmp * tmp;
                }
            }
        }

        // increment iteration
        iter++;

        // sqrt frobenius norm
        tol = sqrt(tol);
        
    }
    printf("TOL: %lf\n",tol);
    // printf("SUM: %lf\n",sum);
    printf("Iterations: %d\n",iter);
}
*/ 

void
gauss_seidel(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance) 
{
    int i, j, k;
    int Nm1 = N-1;
    int iter = 0;

    double tmp, tmp2, tol_min;
    tol_min = tolerance * tolerance;
    double tol = 2.0 * tol_min;
    double oo6 = 1.0 / 6.0;



    #pragma omp parallel \
    num_threads(2) \
    shared(u1, u2, f, Nm1, oo6, iter, tol_min, max_iter, tol) \
    private(i, j, k, tmp) 
    {

    while (tol > tol_min && iter < max_iter) {

        #pragma omp barrier // ensure all threads are in while loop before resetting tol
        tol = 0.0;

        // run inner grid iterations
        #pragma omp for ordered(3)
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    tmp = u1[i][j][k];
                    #pragma omp ordered depend(sink:i-1, j-1, k-1) //depend( i+1, j+1, k+1)
                    u1[i][j][k] = oo6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                    #pragma omp ordered depend(source)
                    tmp -= u1[i][j][k];
                    tol += tmp * tmp;
                }
            }
        }

        // increment iteration
        #pragma omp single
        {
        iter++;
        // printf("TOL: %lf\n",tol);
        }

        // sqrt frobenius norm
        // tol = sqrt(tol);
        
    }
    } /* end pragma parallel */
    // printf("SUM: %lf\n",sum);
    printf("Iterations: %d\n",iter);
}

