// MPI_ManagerWorkerSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[])
{
	// Start the MPI environment in current process
	MPI_Init(&argc, &argv);

	// Kill the MPI environment
	MPI_Finalize();

	system("pause");
	return 0;
}

