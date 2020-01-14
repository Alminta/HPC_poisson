/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <math.h>


void
jacobi(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance)
{
    int i, j, k;
    int Nm1 = N-1;
    int iter = 0;

    double ***u3;

    double tmp;
    double tol = tolerance + 1;
    double gs = 2 / (N - 1);
    double oo6 = 1 / 6;

    while (tol > tolerance && iter < max_iter) {

        tol = 0.0;

        // run inner grid iterations
        for (i = 1; i < Nm1; i++){
            for (j = 1; j < Nm1; j++){
                for (k = 1; k < Nm1; k++){
                    tmp = oo6 * (u1[i-1][j][k] + u1[i+1][j][k] + u1[i][j-1][k] + u1[i][j+1][k] + u1[i][j][k-1] + u1[i][j][k+1] + f[i][j][k]);
                    u2[i][j][k] = tmp;
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
}
