#!/usr/bin/env zsh

#SBATCH -p instruction
#SBATCH --time 00:01:00
#SBATCH --job-name=FirstSlurm
#SBATCH --cpus-per-task=2
#SBATCH --output=FirstSlurm.out
#SBATCH --error=FirstSlurm.err

echo "Host name of the machine running the job: $(hostname)"
