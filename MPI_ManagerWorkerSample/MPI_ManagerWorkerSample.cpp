// MPI_ManagerWorkerSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>

#include "JobManager.h"
#include "Worker.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Start the MPI environment in current process
	MPI_Init(&argc, &argv);

	// Determine the process ID to determine if the node should be master or slave
	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0)
    {
        JobManager job_manager;
        job_manager.manage_processes();
    }
    else
    {
        Worker worker;
        worker.start_work();
    }

	// Kill the MPI environment
	MPI_Finalize();

    return 0;
}

