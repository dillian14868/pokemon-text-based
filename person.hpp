#ifndef PERSON_HPP
#define PERSON_HPP
#include "pokemon.hpp"
#include <vector>
#include <set>
#include <map>
#include <typeinfo>

class Item;

/*
Person class for either a player or gym leader.
Member variables are name and map of pokemon.
*/
class Person {

    public:
        Person(const std::string& name): m_name(name), m_map_of_pokemon(std::map<std::string, Pokemon>()) {};
        Person(): m_name("Scare"), m_map_of_pokemon(
        {
        {"pok3", Pokemon("pok3", 3, "ground", 100, std::map<std::string, int>{{"attack1", 40}, {"attack2", 50}, {"attack3", 30}})},
        {"pok2", Pokemon("pok2", 3, "ground", 100, std::map<std::string, int>{{"attack1", 40}, {"attack2", 50}, {"attack3", 30}})},
        {"pok1", Pokemon("pok1", 3, "ground", 100, std::map<std::string, int>{{"attack1", 40}, {"attack2", 50}, {"attack3", 30}})}           
        }){};
        

        struct PokemonCompare {
            using is_transparent = void;
            bool operator()(const Pokemon& pok, const std::string& name) const;

            bool operator()(const std::string& name, const Pokemon& pok) const;

            bool operator()(const Pokemon& pok_left, const Pokemon& pok_right) const;
        }; 

        std::string get_player();

        void set_player(std::string n);

        std::map<std::string, Pokemon>& get_pokemon();



    protected:
        std::string m_name;
        std::map<std::string, Pokemon> m_map_of_pokemon;


};

/*
Player class which is the child class of Person.
Member variables vectors of items, money, and obtained pokemon in the pokedex. 
*/
class Player: public Person {
    private:
        std::vector<std::unique_ptr<Item>> m_items;
        struct Pokedex { 
            int obtained = 1;
        };
        int m_money = 150; 

        public:
            Pokedex pokedex; 
            Player(const std::string& name): Person(name) {};
            Player(): Person() {}; 

            bool catch_pokemon(Pokemon& pok);

            void add_pokemon(std::string str);

            void see_pokedex();

            int pokedex_stats_obtained();

            void add_item(std::unique_ptr<Item> ball);

            void take_money(int money);  

            int get_money() const;  

            void buy_item(int money);  

            std::vector<std::unique_ptr<Item>>& get_items(); 

            bool have_pok(Pokemon& pok) const;
};

/*
Prints out each of the players items name
*/
std::ostream& operator<<(std::ostream& os, const std::vector<std::unique_ptr<Item>>&  vect) {
    for(auto const& item : vect ) {
        os << item->get_name() << std::endl;
    }
    return os;
}

/*
Prints out the pokemon of each of the pokemon in the map
*/
std::ostream& operator<<(std::ostream& os, std::map<std::string, Pokemon> map) {
  for(auto const& pokes : map) {
        os << pokes.second;
    }
    return os;
}

/*
Prints out the items, pokemon and amount of obtained pokemon the player has
*/
std::ostream& operator<<(std::ostream& os, Player& player) {
    os << player.get_items();
    os << player.get_pokemon();
    os << std::to_string(player.pokedex.obtained) << std::endl;  
    return os;
}

#endif 