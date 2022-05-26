#include "pch.h"

#include "Purchase.h"
#include "DatabaseStorage.h"
#include <fstream>

Purchase::Purchase(const ns::StoreItem& item) : m_item(item)
{

}

bool Purchase::DoWork()
{
	DatabaseStorage* db_in_memory = DatabaseStorage::getInstance();
	bool success = db_in_memory->UpdateItem(m_item);

	if (success)
		PrintReceipt();

	return success;
}

void Purchase::PrintReceipt()
{
	std::ofstream outfile;

	outfile.open("receipt.txt", std::ios_base::app);
	outfile << "Item was purchased " << m_item.family + " " + m_item.name + " " + std::to_string(m_item.price);
}
