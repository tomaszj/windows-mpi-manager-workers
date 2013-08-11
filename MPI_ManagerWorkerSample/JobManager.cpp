#include "JobManager.h"

using namespace std;

JobManager::JobManager(char *input_filename)
{
    m_input_filename = input_filename;
    m_world_size = 1;
}


JobManager::~JobManager(void)
{
}

void JobManager::manage_processes(void)
{
	int current_rank;

	// Find the amount of processes available
	MPI_Comm_size(MPI_COMM_WORLD, &m_world_size);
    cout << "[Master] Starting managing workers in pool of " << m_world_size << endl;

    // Setup the file and send it
    string file_input_string = read_input_file(m_input_filename);
    const char *input_data = file_input_string.c_str();
    MPI_Bcast((char *)input_data, strlen(input_data) + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    cout << "[Master] Sent input file: " << file_input_string << endl;

    // Setup and send the work for each node
	for (current_rank = 1; current_rank < m_world_size; current_rank++)
	{
        topo_synthesis_work_t work;
        work.topology_index = current_rank;

        MPI_Send(&work, sizeof(topo_synthesis_work_t), MPI_BYTE, current_rank, 100, MPI_COMM_WORLD);        
        cout << "[Manager] Sent work with index #" << work.topology_index << " to " << current_rank << endl;
	}

    // Wait for the result for each node
    for (current_rank = 1; current_rank < m_world_size; current_rank++)
    {
        char received_work_string[1024];
        MPI_Status status;

        MPI_Recv(received_work_string, 1024, MPI_CHAR, current_rank, 100, MPI_COMM_WORLD, &status);
        cout << "[Manager] Received " << received_work_string << " from #" << status.MPI_SOURCE << endl;
    }

    system("pause");
}

string JobManager::read_input_file(char *filename)
{
    stringstream result_stream;

    // Open file input stream
    ifstream file_stream(filename);
    assert(file_stream); // "Opening input file failed!"

    result_stream << file_stream.rdbuf();
    file_stream.close();

    // Convert the result
    string result_string = result_stream.str();
    cout << "[Master] Input file read: " << result_string << endl; 

    return result_string;
}
