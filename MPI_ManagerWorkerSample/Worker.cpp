#include "Worker.h"
#include "Work.h"

using namespace std;

Worker::Worker(void)
{
}


Worker::~Worker(void)
{
}

void Worker::start_work(void)
{
    int worker_rank;
    int work_number;
    MPI_Status status;

    // Determine current rank
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_rank);
    cout << "[Worker #" << worker_rank << "] starting work" << endl;
    
    // Receive work to be processed
    MPI_Recv(&work_number, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
    cout << "[Worker #" << worker_rank << "] received: " << work_number << endl;

    // Perform the work
    int result_work_number = work_number * 2;

    // Send back results
    MPI_Send(&result_work_number, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
}
