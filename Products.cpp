#include "pch.h"
#include <vector>

#include "Products.h"
#include "Purchase.h"
#include "DatabaseStorage.h"


char* ConvertStringToCharArray(const std::string& str)
{
    char* cstr = new char[str.length() + 1];
    strcpy_s(cstr, str.length() + 1, str.c_str());

    return cstr;
}


// Fetch the list of all product families
char* GetAllProductFamilies()
{
    std::string results;

    DatabaseStorage* dbStorage = DatabaseStorage::getInstance();

    std::vector<std::string> all_families;

    const std::list<ns::StoreItem>& stored_items = dbStorage->GetStoredItems();
    for (auto it : stored_items)
    {
        if (std::find(all_families.begin(), all_families.end(), it.family) == all_families.end())
        {
            all_families.push_back(it.family);
            results += it.family + " ";
        }
    }

    return ConvertStringToCharArray(results);
}

// Fetch all products in the store for a given product family
char* GetAllProducts(const char* product_family)
{
    // reading from the database is thread safe
    DatabaseStorage* dbStorage = DatabaseStorage::getInstance();
    const std::list<ns::StoreItem>& stored_items = dbStorage->GetStoredItems();

    std::string results;

    for (auto it : stored_items)
    {
        if (it.family == product_family)
            results += ns::to_string(it) + " ";
    }

    return ConvertStringToCharArray(results);
}

// Fetch the information of a specific product given its ID
char* GetProductInformation(const char* id)
{
    std::string results;
    // reading from the database is thread safe
    DatabaseStorage* dbStorage = DatabaseStorage::getInstance();
    const std::list<ns::StoreItem>& stored_items = dbStorage->GetStoredItems();

    for (auto it : stored_items)
    {
        if (it.id == id)
        {
            results += ns::to_string(it) + " ";
        }
    }

    return ConvertStringToCharArray(results);
}

// Purchase a product
bool PurchaseProduct(const char* id)
{
    DatabaseStorage* dbStorage = DatabaseStorage::getInstance();
    const std::list<ns::StoreItem>& stored_items = dbStorage->GetStoredItems();

    bool result = false;

    for (auto it : stored_items)
    {
        if (it.id == id)
        {
            Purchase purchase;
            result = purchase.DoWork(it);
        }
    }

    return result;
}