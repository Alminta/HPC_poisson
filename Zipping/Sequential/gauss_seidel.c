/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>

void
gauss_seidel(double ***u, double ***f, int N, int max_iter, double tolerance) 
{
    // initialize variables
    int i, j, k;
    int Nm1 = N-1;
    int iter = 0;

    double tmp, tmp2, tol_min;
    tol_min = tolerance * tolerance;
    
    double tol = 2.0 * tolerance;
    double div6 = 1.0 / 6.0;

    while (tol > tol_min && iter < max_iter) {

        // reset tolerance
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
    }
}