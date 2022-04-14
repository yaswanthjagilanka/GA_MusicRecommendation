#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --partition=general-compute
#SBATCH --qos=general-compute
#SBATCH --exclusive
#SBATCH --output=genetic_algo_n16.stdout
#SBATCH --error=genetic_algo_n16.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="Genetic-Algo"
#SBATCH --nodes=16
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:15:00

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
echo "Sample Size = 5000"
srun --mpi=pmi2 /user/yjagilan/genetic_algo/a1 5000