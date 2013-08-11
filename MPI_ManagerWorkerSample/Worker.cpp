#include "Worker.h"

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
    char input_file_buffer[1024];
    topo_synthesis_work_t work;
    MPI_Status status;

    // Determine current rank
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_rank);
    cout << "[Worker #" << worker_rank << "] starting work" << endl;
    
    // Receive the input file
    MPI_Bcast(input_file_buffer, 1024, MPI_CHAR, 0, MPI_COMM_WORLD);
    cout << "[Worker #" << worker_rank << "] received input file: " << input_file_buffer << endl;

    // Receive work to be processed
    MPI_Recv(&work, sizeof(topo_synthesis_work_t), MPI_BYTE, 0, 100, MPI_COMM_WORLD, &status);
    cout << "[Worker #" << worker_rank << "] received work index #" << work.topology_index << endl;

    // Perform the work
    int result_calculation = work.topology_index * 2;
    stringstream result_stringstream;
    result_stringstream << "Result! " << result_calculation << endl;

    // Execute external program
    execute_command("SimpleFileProcessor.exe text_to_count.txt", result_stringstream);
    
    // Get C-string as a result
    string mid = result_stringstream.str();
    const char *result_string = mid.c_str();        

    // Send back result length and then the result itself
    MPI_Send((char *)result_string, strlen(result_string) + 1, MPI_CHAR, 0, 100, MPI_COMM_WORLD);

    cout << "[Worker #" << worker_rank << "] Sent result: " << result_string << endl;
}

void Worker::execute_command(char *command, iostream &output_stream)
{
    FILE *output_handle = _popen(command, "r");
    while(!feof(output_handle))
    {
        char buffer[128];
        if (fgets(buffer, 128, output_handle) != NULL)
        {   
            output_stream << buffer;
        }
    }

    fclose(output_handle);
}
