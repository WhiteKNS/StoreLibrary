#pragma once
#include "StoreItem.h"

class Purchase
{
public:
	Purchase();
	bool DoWork(const ns::StoreItem& item);

private:
	void PrintReceipt(const ns::StoreItem& item);

	ns::StoreItem m_item;
};

