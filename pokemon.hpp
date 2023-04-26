
#ifndef POKEMON_HPP
#define POKEMON_HPP
#include <map>
#include <string>
#include <iostream>
class Pokeball;
class Player;

/*
Pokemon class.
Member Variables are name, evolve level, type, health level, max health, attacks, whether it was obtained, and experience points.
*/
class Pokemon { 
    private:  
        std::string m_name;
        int m_evolve_level; 
        std::string m_type;
        int m_health;
        std::map<std::string, int> m_attacks; \
        bool m_obtained;
        int m_experience;
        int m_max_health;

    public:  
        Pokemon(const std::string& name): m_name(name), m_evolve_level(1), m_type("type"), m_health(50), m_attacks(std::map<std::string, int>({{"Melee", 10}})), 
        m_obtained(false), m_experience(0), m_max_health(50){};
        Pokemon(const std::string& name, const std::string& type, std::map<std::string, int> attacks): m_name(name), m_evolve_level(1), m_type(type), m_health(50), m_attacks(attacks), 
        m_obtained(false), m_experience(0), m_max_health(50){};
        Pokemon(const std::string& name,  int evolve_level, const std::string& type, int health, std::map<std::string, int> attacks): m_name(name), m_evolve_level(evolve_level),
        m_type(type), m_health(health), m_attacks(attacks), m_obtained(false), m_experience(0), m_max_health(health){};

        bool operator<(const Pokemon& rhs) const {
            return m_name < rhs.m_name;
        }

        void attack(std::string attack, Pokemon& other_pokemon, bool players);

        Pokemon& obtain();

        int get_health() const;

        const std::map<std::string, int>& get_attacks() const;

        std::string get_name() const;

        int get_evolve_level() const;

        std::string get_type() const;

        void drop_item(Player& player) const;

        void drop_money(Player& player, int health_at_start) const;

        void evolve();

        int get_XP() const;

        void heal_revival();

        void heal_potion();

};

/*
Prints out the name and other stats about the pokemon.
*/
std::ostream& operator<<(std::ostream& os, const Pokemon& pokemon) {
    os << "Pokemon Name: " << pokemon.get_name() << '\t' << "Evolve Level: " << 
    pokemon.get_evolve_level() << '\t' << "Type: " << pokemon.get_type() << " Health: " << pokemon.get_health() <<
    " XP: " << pokemon.get_XP() << std::endl;
    return os;
}

/*
Prints out the name of attacks and damage.
*/
std::ostream& operator<<(std::ostream& os, const std::map<std::string, int>& attacks) {
    os << "Your choices of attacks: " << std::endl;
    for(auto const&  attack : attacks) {
        os << "Name: " << attack.first << '\t' << "Damage: " << attack.second << std::endl;
    }
    return os;
}


#endif 