// MPI_ManagerWorkerSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>

#include "JobManager.h"
#include "Worker.h"

using namespace std;

/*
 * Main entry point to the application.
 *
 * Accepts one argument:
 * - input file name, which will be used as input to the topology synthesis calculations
 */
int main(int argc, char* argv[])
{
	// Start the MPI environment in current process
	MPI_Init(&argc, &argv);

	// Determine the process ID to determine if the node should be master or slave
	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    if (process_rank == 0)
    {
        char *input_file_name;

        if (argc >= 2)
        {
            input_file_name = argv[1];
        }
        else
        {
            input_file_name = "test_file.in";
        }

        JobManager job_manager(input_file_name);
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

