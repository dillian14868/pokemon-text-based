#ifndef TOWN_HPP
#define TOWN_HPP
#include "pokemon.hpp"
#include "item.hpp"
#include <set>

/*
Town class which is in charge of buying items and generating pokemon in the fields.
Member variables are items to buy.
*/
class Town {
    private:
        std::map<std::string, Pokemon> m_pokemons = {
        {"Mudkip", Pokemon("Mudkip", "water", std::map<std::string, int>({{"Melee", 10}, {"Melee2", 5}, {"Melee3", 10}}))}, 
        {"Luxray", Pokemon("Luxray", "electric", std::map<std::string, int>({{"Melee", 10}, {"Melee2", 5}, {"Melee3", 10}}))}, 
        {"Eevee", Pokemon("Eevee", "normal", std::map<std::string, int>({{"Melee", 10}, {"Melee2", 5}, {"Melee3", 10}}))}, 
        {"Typhlosion", Pokemon("Typhlosion", "fire", std::map<std::string, int>({{"Melee", 10}, {"Melee2", 5}, {"Melee3", 10}}))}, 
        {"Flygon", Pokemon("Flygon", "ground", std::map<std::string, int>({{"Melee", 10}, {"Melee2", 5}, {"Melee3", 10}}))}};

        std::map<std::string, std::unique_ptr<Item>> m_items_to_buy;

    public:

        Town() {
            m_items_to_buy["Red Pokeball"] = std::make_unique<Pokeball>("Red Pokeball");
            m_items_to_buy["Potion"] = std::make_unique<Potion>("Potion");
            m_items_to_buy["Revival"] = std::make_unique<Revival>("Revival");
        }

        Pokemon generate_pokemon();

        std::ostream& introduce_enemy(std::ostream& os, Pokemon& pok);

        void buy(Player& player, std::string name);

};

#endif // TOWN_HPP