#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Request
{
	int customer_id;
	std::string method;
	std::string command;
	std::string args;
	//json item;
}
customerRequest;


// Request Structure:
// id, (customer id)
// method, (POST, GET, PUT)
// command (GetAllFamilies)
// args (args for the command)
// item (item_to_buy)


