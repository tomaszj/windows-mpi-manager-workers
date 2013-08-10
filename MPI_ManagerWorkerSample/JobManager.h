#include "stdafx.h"
#include <mpi.h>

#pragma once
class JobManager
{
public:
	JobManager(void);
	~JobManager(void);

	void manage_processes(void);
};

