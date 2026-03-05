#include "Weapon.hpp"
#include "Armor.hpp"
#include "Consumable.hpp"
#include "Money.hpp"
#include <vector>
#include <memory>


inline std::vector<std::shared_ptr<Item>> tier1;

void tier1_init();
void items_init();

std::shared_ptr<Item> tier1_item(size_t slotNum);
std::shared_ptr<Item> tier1_item_by_id(int id);