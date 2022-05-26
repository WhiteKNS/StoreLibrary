#pragma once

#include "DatabaseStorage.h"

class DatabaseWorker
{
	// update once per 100 milliseconds
	const int m_update_after_ms = 100;
	std::mutex m_mutex;

public:
	DatabaseWorker() {}
	void Update();
};