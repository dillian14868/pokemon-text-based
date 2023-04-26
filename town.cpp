#include "town.hpp"
#include "pokemon.hpp"
using namespace std;

/*
Generates random pokemon from map of pokemon in the town
*/
Pokemon Town::generate_pokemon(){ 
    auto r = rand() % m_pokemons.size(); 
    auto it = std::begin(m_pokemons);
    std::advance(it,r);
    return (*it).second;
}

/*
Introduces the user to the pokemon they are fighting
*/
std::ostream& Town::introduce_enemy(std::ostream& os, Pokemon& pok) {
    os << "You are fighting " << pok.get_name() << endl;
    os << pok << endl;
    return os;
}

/*
Buys items, adds item to vector of items, reports what you have bought, and what items you currently have.
*/
void buy_helper(Player& player, string name, unique_ptr<Item> item, int num){
    player.buy_item(num);
    player.add_item(move(item));   
    cout << "You bought a " << name << "!" << endl; 
    cout << "You have $" << player.get_money() << " dollars left." << endl;
    cout << "You have the following items:" << endl;
    cout << player.get_items();
}

/*
Simulates a store. Depending on if the item is in the store and if the user has the money, the item can be bought.
*/
void Town::buy(Player& player, string name){
    while(true) {
        auto found = this->m_items_to_buy.find(name);
        if(player.get_money() >= 10 && found->first == "Potion") {
            buy_helper(player, name, make_unique<Potion>("Potion"), 10);  
            return;
        } else if(player.get_money() >= 30 && found->first == "Red Pokeball") {
            buy_helper(player, name, make_unique<Pokeball>("Red Pokeball"), 30); 
            return;
        } else if(player.get_money() >= 100 && found->first == "Revival") {
            buy_helper(player, name, make_unique<Revival>("Revival"), 100); 
            return;
        } else if(player.get_money() < 10) {
            cout << "You don't have enough money." << endl;
            return;
        } else if(name == "exit") {
            cout << "Leaving the store." << endl;
            return;
        } else {
            cout << "You didn't type any of the choices try again or you don't have enough money to buy that item." << endl;
            getline(cin, name);
        } 
    }
}