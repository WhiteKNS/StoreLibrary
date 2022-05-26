#include "pch.h"

#include <fstream>
#include <iostream>

#include "DatabaseWorker.h"
#include "DatabaseStorage.h"


const std::list<ns::StoreItem>& DatabaseStorage::GetStoredItems()
{
    return stored_items;
}

void DatabaseStorage::AddStoreItem(const ns::StoreItem& item)
{
    stored_items.push_back(item);
}

void DatabaseStorage::DeleteStoreItem(const ns::StoreItem& item)
{
    stored_items.remove(item);
}

const std::string DatabaseStorage::GetDBPath()
{
    return db_path;
}

void RunDatabaseSheduler()
{
    DatabaseWorker db_worker;

    db_worker.Update();
}

static std::atomic<DatabaseStorage*> m_instance;
static std::mutex m_dbmutex;

DatabaseStorage* DatabaseStorage::getInstance()
{
    // thread safe database
    DatabaseStorage* sin = m_instance.load(std::memory_order_acquire);
    if (!sin) {
        std::lock_guard<std::mutex> lock(m_dbmutex);

        sin = m_instance.load(std::memory_order_relaxed);
        if (!sin) {
            sin = new DatabaseStorage();
            m_instance.store(sin, std::memory_order_release);

            std::thread db_thread(RunDatabaseSheduler);
            db_thread.detach();
        }
    }

    return sin;
}

DatabaseStorage::DatabaseStorage()
{
    std::ifstream ifstr(db_path, std::ifstream::binary);
    json j;
    ifstr >> j;

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        AddStoreItem(*it);
    }
}

bool DatabaseStorage::UpdateItem(const ns::StoreItem& item)
{
    std::lock_guard<std::mutex> lock(m_dbmutex);

    if (item.amountAvailable == 0)
    {
        std::cerr << "No items available" << std::endl;
        return false;
    }

    std::list<ns::StoreItem>::iterator it = std::find(stored_items.begin(), stored_items.end(), item);

    if (it == stored_items.end())
    {
        std::cerr << "Item doesn't exaist" << std::endl;
        return false;
    }

    it->amountSold++;
    it->amountAvailable--;

    return true;
}
