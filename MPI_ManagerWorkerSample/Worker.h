#include "stdafx.h"
#include <mpi.h>
#include <string>
#include <sstream>

#pragma once
class Worker
{
public:
	Worker(void);
	~Worker(void);

	void start_work(void);
};

