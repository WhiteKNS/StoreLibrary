#pragma once

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace ns {
    struct StoreItem {
        std::string id;
        std::string family;
        std::string name;
        int amountAvailable;
        int amountSold;
        double  price;
    };

    inline bool operator==(const StoreItem& lhs, const StoreItem& rhs)
    {
        return lhs.id == rhs.id;;
    }

    inline std::string to_string(const StoreItem& item)
    {
        std::string result = "\n{\nid: " + item.id + "\nFamily: " + item.family + "\nItem Name: " + item.name + "\nAmount Available: " + std::to_string(item.amountAvailable) + "\nAmount Sold: " + std::to_string(item.amountSold) + "\nAmount Price: " + std::to_string(item.price) + "\n},\n\n";
        return result;
    }

    inline void to_json(json& j, const StoreItem& item) {
        j = json{ {"id", item.id}, {"family", item.family}, {"name", item.name}, {"amountAvailable", item.amountAvailable}, {"amountSold", item.amountSold},{"price", item.price} };
    }

    inline void from_json(const json& j, StoreItem& p) {
        j.at("id").get_to(p.id);
        j.at("family").get_to(p.family);
        j.at("name").get_to(p.name);
        j.at("amountAvailable").get_to(p.amountAvailable);
        j.at("amountSold").get_to(p.amountSold);
        j.at("price").get_to(p.price);
    }
}