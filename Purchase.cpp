#include "pch.h"

#include "Purchase.h"
#include "DatabaseStorage.h"
#include <fstream>

Purchase::Purchase()
{

}

bool Purchase::DoWork(const ns::StoreItem& item)
{
	DatabaseStorage* db_in_memory = DatabaseStorage::getInstance();
	bool success = db_in_memory->UpdateItem(item);

	if (success)
		PrintReceipt(item);

	return success;
}

void Purchase::PrintReceipt(const ns::StoreItem& item)
{
	std::ofstream outfile;

	outfile.open("receipt.txt", std::ios_base::app);
	outfile << "Item was purchased " << m_item.family + " " + m_item.name + " " + std::to_string(m_item.price);
}
