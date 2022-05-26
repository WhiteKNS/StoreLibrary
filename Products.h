#pragma once

#ifdef SERVER_EXPORTS
#define STORELIBRARY_API __declspec(dllexport)
#else // STORELIBRARY_EXPORTS
#define STORELIBRARY_API __declspec(dllimport)
#endif // STORELIBRARY_API

// Fetch the list of all product families
extern "C" STORELIBRARY_API char* GetAllProductFamilies();

// Fetch all products in the store for a given product family
extern "C" STORELIBRARY_API char* GetAllProducts(const char* product_family);

// Fetch the information of a specific product given its ID
extern "C" STORELIBRARY_API char* GetProductInformation(const char* id);

// Purchase a product
extern "C" STORELIBRARY_API bool PurchaseProduct(const char* id);
