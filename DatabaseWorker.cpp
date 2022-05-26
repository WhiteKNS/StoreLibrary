#include "pch.h"

#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

#include "DatabaseWorker.h"
#include "DatabaseStorage.h"


typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds Milliseconds;

// update database (in a separate thread)
void DatabaseWorker::Update()
{
	DatabaseStorage* db_in_memory = DatabaseStorage::getInstance();

	auto previous_clock = Clock::now() - Milliseconds(m_update_after_ms);

	while (true)
	{
		auto t1 = Clock::now();
		auto elapsed_time = std::chrono::duration_cast<Milliseconds>(t1 - previous_clock);
		auto duration = Milliseconds(m_update_after_ms);

		// Update the database if the time elapsed
		if (elapsed_time < duration)
		{
			std::this_thread::sleep_for(duration - elapsed_time);
		}
		else
		{
			const std::lock_guard<std::mutex> lock(m_mutex);

			json j = db_in_memory->GetStoredItems();
			std::ofstream o(db_in_memory->GetDBPath(), std::ofstream::binary);
			o << j;

			previous_clock = t1;
		}
		
	}
}
