#include "pokemon.hpp"
#include "item.hpp"
#include "person.hpp"
using namespace std;

/*
You choose the attack you want to inflict on the enemy pokemon 
Or if it isn't your turn they choose a random attack from their map attacks.
*/
void Pokemon::attack(string attack, Pokemon& other_pokemon, bool players) {
    if(players) {
        fflush(stdin);
        while(true == players) {  
            std::cout << "Which attack do you want to use?" << endl;
            getline(cin, attack);
            std::system("clear");
            auto iter = m_attacks.find(attack);
            if(iter != cend(m_attacks)) {
                other_pokemon.m_health -= iter->second;  
                cout << "\n" << attack << " was successful. " << other_pokemon.get_name() << " health is "
                << other_pokemon.get_health() << endl;
                break;
            } else {
                cout << attack << " not valid try again" << endl;
            }
        }
    } else {
        auto r = std::rand() % m_attacks.size(); 
        auto iter = std::next(m_attacks.begin(), r);
            if(iter != cend(m_attacks)) {
                other_pokemon.m_health -= iter->second; 
                cout << "Now it is " << this->get_name() << " 's turn" << endl;
                cout << "Their " << iter->first << " was successful. Your pokemon's health is " << other_pokemon.get_health() << endl;
            }
    }
} 

/*
Set the pokemon to obtained and return a reference it.
*/
Pokemon& Pokemon::obtain() {
    m_obtained = true;  
    return *this;
}

/*
Get the const health of the pokemon.
*/
int Pokemon::get_health() const {
    return m_health;  
}

/*
Get the const attacks of a pokemon.
*/
const std::map<std::string, int>& Pokemon::get_attacks() const {
    return m_attacks;
}

/*
Get the const name of a pokemon.
*/
string Pokemon::get_name() const {
    return m_name;
}

/*
Get the const level of a pokemon.
*/
int Pokemon::get_evolve_level() const {
    return m_evolve_level;
}

/*
Get the const type of a pokemon.
*/
string Pokemon::get_type() const {
    return m_type;
}

/*
Pokeball is dropped if the random number obtained is higher than 7
*/
void Pokemon::drop_item(Player& player) const{  
    auto r = std::rand() % 10; 
    int PROB_NUM = 7; 

    if(r > PROB_NUM){
        player.add_item(make_unique<Pokeball>("Red Pokeball")); 
        cout << "You gained a Red Pokeball" << endl;
        cout << player.get_items();
    }
}

/*
Amount of money obtained is dependent on health of enemy pokemon at the start
*/
void Pokemon::drop_money(Player& player, int health_at_start) const{   
    if(health_at_start <= 50) {
        player.take_money(10);
        cout << "You gained $" << 10 << ". Your total is now $" << player.get_money() << endl;
    } else if(health_at_start <= 80) {
        player.take_money(20);
        cout << "You gained $" << 20 << ". Your total is now $" << player.get_money() << endl;
    } else if(health_at_start <= 100) {
        player.take_money(50);
        cout << "You gained $" << 50 << ". Your total is now $" << player.get_money() << endl;
    }
}

/*
Amount of experience increases after each sucessful battle.
Evolves by increasing evolve level, health, max health, and adding an attack.
*/
void Pokemon::evolve() {
    m_experience += 20;
    if(m_experience >= 250) { 
        m_evolve_level = 2;
        m_health = 80;
        m_max_health = 80;
        m_attacks.insert({"Evolve2", 30});
        cout << "Health of this pokemon is now " << m_health << endl;
        cout << "Evolve level of this pokemon is now " << m_evolve_level << endl;
    } else if (m_experience >= 100) {
        m_evolve_level = 3;
        m_health = 120;
        m_max_health = 120;
        m_attacks.insert({"Evolve3", 60});
        cout << m_attacks;
        cout << "Health of this pokemon is now " << m_health << endl;
        cout << "Evolve level of this pokemon is now " << m_evolve_level << endl;
    }
    cout << "Experience level of this pokemon is " << m_experience << endl;
}

/*
Gets experience points
*/
int Pokemon::get_XP() const {
    return m_experience;
}

/*
Sets health back to the max health
*/
void Pokemon::heal_revival() {
    m_health = m_max_health;
}

/*
Adds 20 to health or caps it to max health when using a potion
*/
void Pokemon::heal_potion() {
    if(m_health + 20 > m_max_health) {
        m_health = m_max_health;
    } else {
        m_health += 20;
    }
}