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
    int Nm1 = N-1;
    int iter = 0;

    double ***u3;

    double tmp,sum;
    double tol = 2.0 * tolerance;
    // double gs = 2.0 / (N - 1.0);
    double oo6 = 1.0 / 6.0;

    #pragma omp parallel \
    schedule(dynamic)
    // num_threads(1)
    {
    while (tol > tolerance && iter < max_iter) {

        tol = 0.0;

        // run inner grid iterations
        for (i = 1; i < Nm1; i++){
            #pragma omp for \
            shared(u1, u2, f, Nm1, oo6, i) \
            private(j, k, tmp) \
            reduction(+ : tol)
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    tmp = oo6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                    u2[i][j][k] = tmp;
                    tmp -= u1[i][j][k];
                    tol += tmp * tmp;
                }
            }
        }
        // swap pointers
        u3 = u1; 
        u1 = u2;
        u2 = u3;

        // increment iteration
        iter++;

        // sqrt frobenius norm
        tol = sqrt(tol);
        
    }
    } /* end pragma parallel */
    printf("TOL: %lf\n",tol);
    printf("Iterations: %d\n",iter);
}
