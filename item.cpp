#include "item.hpp"
#include "person.hpp"
using namespace std;

/*
Gets name of item.
*/
string Item::get_name() const{
    return m_name;
}

/*
Finds the revival item in the players map, erases it, and then heals the pokemon.
*/
bool Revival::use(Player& player, Pokemon& pok) {
    auto revival = find_if(player.get_items().begin(), player.get_items().end(), [](auto& obj) {return obj->get_name() == "Revival";});
    player.get_items().erase(revival); 
    pok.heal_revival();
    return true;
}

/*
Finds the potion item in the players map, erases it, and then heals the pokemon.
*/
bool Potion::use(Player& player, Pokemon& pok) {
    auto potion = find_if(player.get_items().begin(), player.get_items().end(), [](auto& obj) {return obj->get_name() == "Potion";});
    player.get_items().erase(potion); 
    pok.heal_potion();
    return true;
}

/*
Finds the pokeball item in the players map, erases it, and then catches the pokemon.
Uses probability and health to decide if the pokemon will be caught.
*/
bool Pokeball::use(Player& player, Pokemon& pok) {
    auto r = std::rand() % 10; 
    auto ball = find_if(player.get_items().begin(), player.get_items().end(), [](auto& obj) {return obj->get_name() == "Red Pokeball";});
    if(r >= m_probability && pok.get_health() <= 20){
        std::cout << "You caught " <<  pok.get_name() << "! Congratulations!" << std::endl;
        player.get_items().erase(ball);
        return true;
    } else {
        player.get_items().erase(ball);
        std::cout << "You didn't catch " << pok.get_name() << ". Sorry." << std::endl;
    }     
    return false;
}