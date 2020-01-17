#!/bin/bash
#
#BSUB -J tyr_3_x_test_clang
#BSUB -o tyr_3_x_test_clang_%J.out
#BSUB -q hpcintro
#BSUB -n 24
#BSUB -R "rusage[mem=1024]"
#BSUB -W 10
#BSUB -R "span[hosts=1]"

module load studio
module load clang/9.0.0
# module swap clang/9.0.0

# executable
EXECUTABLE=poisson_gs

# args
N="25 50 100 200"
ITER="2000"
TOL="0.05"
START_T="0"
OUT="0"

# environment variables
# export OMP_NUM_THREADS=12
export OMP_PROC_BIND=close

# THREADS="1 2 4 8 12"
THREADS="16 20 24"

# start the collect command with the above settings
# ./$EXECUTABLE $N $ITER $TOL $START_T $OUT

for n in $N
do
    for T in $THREADS
    # echo "N=$n T=$T"
    do
        time OMP_NUM_THREADS=$T ./$EXECUTABLE $n $ITER $TOL $START_T $OUT
    done
done

# for n in $N
# do
#     time ./$EXECUTABLE $n $ITER $TOL $START_T $OUT
# done

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