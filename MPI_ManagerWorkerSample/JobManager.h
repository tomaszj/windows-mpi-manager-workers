#include "stdafx.h"
#include <mpi.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "Work.h"

#pragma once
class JobManager
{
    char *m_input_filename;

public:
	JobManager(char *input_filename);
	~JobManager(void);

	void manage_processes(void);

private:
    std::string read_input_file(char *filename);
};

