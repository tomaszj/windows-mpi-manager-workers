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
    // Execute external program
    system("SimplePrinter.exe");

    int result_calculation = work_number * 2;
    stringstream result_stringstream;
    result_stringstream << "Result! " << result_calculation;
    string mid = result_stringstream.str();
    const char *result_string = mid.c_str();        

    // Send back result length and then the result itself
    MPI_Send((char *)result_string, strlen(result_string) + 1, MPI_CHAR, 0, 100, MPI_COMM_WORLD);

    cout << "[Worker #" << worker_rank << "] Sent result: " << result_string << endl;
}
