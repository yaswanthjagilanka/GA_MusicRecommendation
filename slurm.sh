#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute
#SBATCH --exclusive
#SBATCH --output=/user/yjagilan/genetic_algo/output/genetic_algo_v1_n2_i5.stdout
#SBATCH --error=/user/yjagilan/genetic_algo/output/genetic_algo_v1_n2_i5.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="Genetic-Algo"
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=01:00:00

module unload gcc
module load gcc/9.3.0
module load intel-mpi/2019.5

# if using Intel MPI add need this
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so


echo "Sample Size = 500"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 500
echo "***********************************************************************"
echo "Sample Size = 1000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 1000
echo "***********************************************************************"
echo "Sample Size = 2000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 2000
echo "***********************************************************************"
echo "Sample Size = 4000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 4000
echo "***********************************************************************"
echo "Sample Size = 8000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 8000
echo "***********************************************************************"
echo "Sample Size = 16000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 16000
echo "***********************************************************************"
echo "Sample Size = 17100"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 17100