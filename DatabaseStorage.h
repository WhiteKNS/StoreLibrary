#pragma once
#include <list>
#include <mutex>
#include <atomic>

#include "StoreItem.h"

class DatabaseStorage
{
private:
    /* Private constructor to prevent instancing. */
    DatabaseStorage();

public:
    /* Static access method. */
    static DatabaseStorage* getInstance();

private:
    std::list<ns::StoreItem> stored_items;

private:
    const std::string db_path = "../Server/assets/store.json";

private:
    void AddStoreItem(const ns::StoreItem& item);
    void DeleteStoreItem(const ns::StoreItem& item);

public:
    const std::list<ns::StoreItem>& GetStoredItems();
    const std::string GetDBPath();
    bool UpdateItem(const ns::StoreItem& item);
};

