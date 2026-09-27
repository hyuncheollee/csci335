/**
 * @file Inventory.cpp
 * @author Hyuncheol Lee
 * @date 2026/09/21
 * @brief Implements the Inventory class and its member functions
 */

#include "Inventory.hpp"
#include <utility>

Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped)
    : inventory_grid_(items), equipped_(equipped), weight_(0), item_count_(0) {
    for (const auto& row : inventory_grid_) {
        for (const auto& item : row) {
            if (item.type_ != NONE) {
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
}


Item* Inventory::getEquipped() const {
    return equipped_;
}

void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

void Inventory::discardEquipped() {
    if (equipped_ != nullptr) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

std::vector<std::vector<Item>> Inventory::getItems() const {
    return inventory_grid_;
}

float Inventory::getWeight() const {
    return weight_;
}

size_t Inventory::getCount() const {
    return item_count_;
}

Item Inventory::at(const size_t& row, const size_t& col) const {
    return inventory_grid_.at(row).at(col);
}

bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup) {
    Item& cell = inventory_grid_.at(row).at(col);

    if (cell.type_ != NONE) return false;
    cell = pickup;
    
    if (pickup.type_ != NONE) {
        weight_ += pickup.weight_;
        ++item_count_;
    }
    
    return true;
}

Inventory::Inventory(const Inventory& rhs)
    : inventory_grid_(rhs.inventory_grid_),
      equipped_(rhs.equipped_ ? new Item(*rhs.equipped_) : nullptr),
      weight_(rhs.weight_), item_count_(rhs.item_count_) {}

Inventory::Inventory(Inventory&& rhs)
    : inventory_grid_(std::move(rhs.inventory_grid_)), equipped_(rhs.equipped_),
      weight_(rhs.weight_), item_count_(rhs.item_count_) {
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
    rhs.inventory_grid_.clear();
}

Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        Item* newEquipped = rhs.equipped_ ? new Item(*rhs.equipped_) : nullptr;
        delete equipped_;

        inventory_grid_ = rhs.inventory_grid_;
        equipped_ = newEquipped;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
    }

    return *this;
}

Inventory& Inventory::operator=(Inventory&& rhs) {
    if (this != &rhs) {
        delete equipped_;

        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
        rhs.inventory_grid_.clear();
    }

    return *this;
}

Inventory::~Inventory() {
    delete equipped_;
}
