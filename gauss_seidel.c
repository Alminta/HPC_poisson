/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>


void
gauss_seidel(double ***u, double ***f, int N, int max_iter, double tolerance) 
{
    int i, j, k;
    int Nm1 = N-1;
    int iter = 0;

    double tmp, tmp2;
    double tol = 2.0 * tolerance;
    double div6 = 1.0 / 6.0;

    while (tol > tolerance && iter < max_iter) {

        tol = 0.0;

        // run inner grid iterations
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    tmp = u[i][j][k];
                    u[i][j][k] = div6 * (u[i-1][j][k] + u[i+1][j][k] + u[i][j-1][k] + u[i][j+1][k] + u[i][j][k-1] + u[i][j][k+1] + f[i][j][k]);
                    tmp -= u[i][j][k];
                    tol += tmp * tmp;
                }
            }
        }

        // increment iteration
        iter++;

        // sqrt frobenius norm
        tol = sqrt(tol);
        
    }
    printf("Gauss: N = %d \tIterations = %d \t Tolerance = %lf\n",N, iter, sqrt(tol));
    // printf("TOL: %lf\n",tol);
    // printf("SUM: %lf\n",sum);
    // printf("Iterations: %d\n",iter);
}


/*
void
gauss_seidel(double ***u, double ***f, int N, int max_iter, double tolerance) 
{
    int i, j, k;
    int Nm1 = N - 1;
    int iter = 0;

    double tmp, tmp2, tol_min;
    tol_min = tolerance * tolerance;
    double tol = 2.0 * tol_min;
    double div6 = 1.0 / 6.0;


    // initialize parallel
    #pragma omp parallel \
    shared(u, f, Nm1, div6, iter, tol_min, max_iter, tol) \
    private(i, j, k, tmp) 
    {

    // run iterations
    for (iter = 0 ; iter < max_iter; ) {

        #pragma omp for ordered(2)
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
            #pragma omp ordered \
            depend(sink:i-1,j) \
            depend(sink:i, j-1)
                for (k = 1; k < Nm1; k++){
                    u[i][j][k] = div6 * (u[i-1][j][k] + u[i+1][j][k] + u[i][j-1][k] + u[i][j+1][k] + u[i][j][k-1] + u[i][j][k+1] + f[i][j][k]);
                }
            #pragma omp ordered depend(source)
            }
        }

        #pragma omp single
        {
            iter++;
        }
    }
    } // end pragma parallel
}
*/

// printf("Iterations: %d\n",iter);
// printf("ITER: %d\n",iter);