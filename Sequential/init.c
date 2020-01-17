#include <math.h>
#include <stdio.h>


void
zeros(double ***m, int N)
{
    int i,j,k;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            for (k = 0; k < N; k++){
                m[i][j][k] = 0.0;
            }
        }
    }
}

void
full(double ***m, int N, double start_t)
{
    int i,j,k;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            for (k = 0; k < N; k++){
                m[i][j][k] = start_t;
            }
        }
    }
}


void
boundary(double ***m, int N)
{
    int i, j, k, Nm1;
    Nm1 = N - 1;

    for (i = 0; i < N; i++){
        for (k = 0; k < N; k++){
            m[i][0][k] = 0.0;
        }
    }

    for (i = 0; i < N; i++){
        for (k = 0; k < N; k++){
            m[i][Nm1][k] = 20.0;
        }
    }

    for (j = 0; j < N; j++){
        for (k = 0; k < N; k++){
            m[0][j][k] = 20.0;
            m[Nm1][j][k] = 20.0;
        }
    }

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            m[i][j][0] = 20.0;
            m[i][j][Nm1] = 20.0;
        }
    }
}


void
source(double ***m, int N)
{
    int i, j, k;
    int xl, xu, yl, yu, zl, zu;

    double gs;

    // compute boundaries
    xl = 0;
    xu = 5 * N / 16;
    yl = 0;
    yu = N / 4;
    zl = N / 6;
    zu = N / 2;

    gs = 200.0 * (2.0 / (N - 1.0)) * (2.0 / (N - 1.0));

    for (i = xl; i < xu; i++){
        for (j = yl; j < yu; j++){
            for (k = zl; k < zu; k++){
                m[i][j][k] = gs;
            }
        }
    }
}

void
initialize(double ***u1, double ***u2, double ***f, int N, double start_t)
{
    full(u1, N, start_t);
    full(u2, N, start_t);
    zeros(f, N);

    boundary(u1, N);
    boundary(u2, N);
    source(f, N);
}