#include "JobManager.h"
#include "Work.h"

using namespace std;

JobManager::JobManager(void)
{
}


JobManager::~JobManager(void)
{
}

void JobManager::manage_processes(void)
{
	int world_size;
	int current_rank;

	// Find the amount of processes available
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    cout << "Starting managing workers in pool of " << world_size << endl;

    // Setup and send the work for each node
	for (current_rank = 1; current_rank < world_size; current_rank++)
	{
        int work_number = 333;
        MPI_Send(&work_number, 1, MPI_INT, current_rank, 100, MPI_COMM_WORLD);        
        cout << "[Manager] Sent " << work_number << " to " << current_rank << endl;
	}

    // Wait for the result for each node
    for (current_rank = 1; current_rank < world_size; current_rank++)
    {
        int received_work_number;
        MPI_Status status;
        MPI_Recv(&received_work_number, 1, MPI_INT, MPI_ANY_SOURCE, 100, MPI_COMM_WORLD, &status);

        cout << "[Manager] Received " << received_work_number << " from #" << status.MPI_SOURCE << endl;
    }

    system("pause");
}