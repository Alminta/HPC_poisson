#!/bin/bash
#
#BSUB -J tyr_3_gauss_seq
#BSUB -o tyr_3_gauss_seq_%J.out
#BSUB -q hpcintro
#BSUB -n 1
#BSUB -R "rusage[mem=1024]"
#BSUB -W 4
#BSUB -R "span[hosts=1]"

module load studio

# executable
EXECUTABLE=poisson_gs

# args
N="50 100"
ITER="10000"
TOL="0.05"
START_T="0"
OUT="4"

# environment variables
export OMP_NUM_THREADS=1

# start the collect command with the above settings
# ./$EXECUTABLE $N $ITER $TOL $START_T $OUT

for n in $N
do
    ./$EXECUTABLE $n $ITER $TOL $START_T $OUT
done

# counter=1
# while [ $counter -le 200 ]
# do
#     collect -o $EXPOUT $HWCOUNT ./$EXECUTABLE $PERM $MKN $counter
#     ((counter++))
# done

# array=( 1 2 4 8 16 32 64 128 256 )
# for i in "${array[@]}"
# do
#     collect -o $EXPOUT $HWCOUNT ./$EXECUTABLE $PERM $MKN $i
#     ((counter++))
# done