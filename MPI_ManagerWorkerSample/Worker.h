#include "stdafx.h"
#include <mpi.h>

#pragma once
class Worker
{
public:
	Worker(void);
	~Worker(void);

	void start_work(void);
};

