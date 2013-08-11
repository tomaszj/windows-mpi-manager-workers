#include "stdafx.h"
#include <mpi.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "TopoSynthesisWork.h"

#pragma once
class JobManager
{
    char *m_input_filename;
    int m_world_size;

public:
	JobManager(char *input_filename);
	~JobManager(void);

	void manage_processes(void);

private:
    std::string read_input_file(char *filename);
};

