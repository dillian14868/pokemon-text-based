
#include "person.hpp"
#include "item.hpp"
#include <vector>
using namespace std;

/*
Returns the name of the person.
*/
std::string Person::get_player() {
    return m_name;
}

/*
Sets the name of the person to something else.
*/
void Person::set_player(std::string n) { 
    m_name = n;
}

/*
Gets the map of pokemon.
*/
std::map<std::string, Pokemon>& Person::get_pokemon() {
    return m_map_of_pokemon;
}

/*
Checks if there is a pokeball then if the pokemon is caught adds it to collected pokemon. 
And displays your pokedex of all collected pokemon and your items.
*/
bool Player::catch_pokemon(Pokemon& pok) {
    auto it = find_if(this->get_items().begin(), this->get_items().end(), [](auto& item) {return item->get_name() == "Red Pokeball";}); 
    auto in_set = this->get_pokemon().find(pok.get_name());
    if( in_set == cend(this->get_pokemon()) && it != this->get_items().end() && (*it)->use(*this, pok)) {  
        m_map_of_pokemon.insert({pok.get_name(), pok});
        pokedex.obtained += 1;
        this->see_pokedex();
        cout << this->get_items() << endl;
        return true;
    } 

    cout << "You don't have a pokeball, the pokemons health is not under 20, the probability wasn't high enough, or you already have that pokemon. Sorry." << endl;
    return false;
}

/*
Add one of three starter pokemon to users pokemon map based on input.
*/
void Player::add_pokemon(string str) {
    if(str == "a") {
        Pokemon pok("Bulbasaur", "Ground", map<std::string, int>({{"Vine Whip", 10}, {"Razor Leaf", 20}}));
        m_map_of_pokemon.insert({pok.get_name(), pok.obtain()});
        cout << "You chose Bulbasaur" << endl;
        
    } else if (str == "b") {
        Pokemon pok("Squirtle", "Water", map<std::string, int>({{"Water Gun", 10}, {"Water Pulse", 20}}));
        m_map_of_pokemon.insert({pok.get_name(), pok.obtain()});
        cout << "You chose Squirtle" << endl;
    } else {
        map<std::string, int> map{{"Ember", 10}, {"Flamethrower", 20}};
        Pokemon pok("Charmander", "Fire",  std::map<std::string, int>({{"Ember", 10}, {"Flamethrower", 20}}));
        m_map_of_pokemon.insert({pok.get_name(), pok.obtain()});
        cout << "You chose Charmander" << endl;
    }
}

/*
Shows the pokemon you have and their stats. Plus the amount obtained.
*/
void Player::see_pokedex() {
    cout << endl;
    cout << "These are the pokemon you have." << endl;

    for(auto const& pokes :  m_map_of_pokemon) {
        cout << pokes.second;
    }

    cout << "Amount of Pokemon you have: " << pokedex.obtained << endl;
    cout << endl;
}

/*
Returns the number of pokemon obtained.
*/
int Player::pokedex_stats_obtained() {
    return pokedex.obtained;
}

/*
Adds item to your list of items.
*/
void Player::add_item(unique_ptr<Item> ball) {
    m_items.push_back(move(ball));
}

/*
Adds money to total of players money.
*/
void Player::take_money(int money) {
    m_money += money;
}

/*
Gets players money.
*/
int Player::get_money() const {
    return m_money;
}

/*
Subtracts from players money.
*/
void Player::buy_item(int money) {
    m_money -= money;
}

/*
True or false if you have that pokemon in map.
*/
bool Player::have_pok(Pokemon& pok) const {
    auto found = this->m_map_of_pokemon.find(pok.get_name());
    if(found != cend(this->m_map_of_pokemon)) {
        return true;
    }
    return false;
}

/*
Allows us to compare/order a set of pokemon by name (alphebetical order)
*/
bool Person::PokemonCompare::operator()(const Pokemon& pok, const std::string& name) const {
    return pok.get_name() > name;
}

/*
Allows us to compare/order a set of pokemon by name (alphebetical order)
*/
bool Person::PokemonCompare::operator()(const std::string& name, const Pokemon& pok) const {
    return name > pok.get_name();
}

/*
Allows us to compare/order a set of pokemon by name (alphebetical order)
*/
bool Person::PokemonCompare::operator()(const Pokemon& pok_left, const Pokemon& pok_right) const {
    return pok_left.get_name() > pok_right.get_name();
}

/*
Gets the items a player has
*/
std::vector<std::unique_ptr<Item>>& Player::get_items(){
    return m_items;
}


