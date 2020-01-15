/* gauss_seidel.h - Poisson problem
 *
 */
#ifndef _GAUSS_SEIDEL_H
#define _GAUSS_SEIDEL_H

void gauss_seidel(double ***u1, double ***u2, double ***f, int N, int max_iter, double tolerance);

#endif
