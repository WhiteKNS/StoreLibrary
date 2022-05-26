#pragma once
#include "StoreItem.h"

class Purchase
{
public:
	Purchase(const ns::StoreItem& item);
	bool DoWork();

private:
	void PrintReceipt();

	ns::StoreItem m_item;
};

