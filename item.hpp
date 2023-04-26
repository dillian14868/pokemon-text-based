#ifndef ITEM_HPP
#define ITEM_HPP
#include "pokemon.hpp"
class Player;

/*
Item class for different pokemon items.
Member variables are name.
*/
class Item { 
    private:
        std::string m_name;
        
    public:
       Item(const std::string& name): m_name(name){};

       virtual bool use(Player& player, Pokemon& pok) = 0;

       virtual ~Item() {}

       std::string get_name() const;
};

/*
Pokeball is a type of Item.
Member variables are probability.
*/
class Pokeball: public Item {
    private:
        int m_probability; 

    public:
        Pokeball(const std::string& name) : Item(name), m_probability(3) {};

        bool use(Player& player, Pokemon& pok);

};

/*
Potion is a type of Item  
*/
class Potion: public Item {
    private:

    public:
        Potion(const std::string& name) : Item(name) {};

        bool use(Player& player, Pokemon& pok);

};

/*
Revival is a type of Item  
*/
class Revival: public Item {
    private:

    public:
        Revival(const std::string& name) : Item(name) {};

        bool use(Player& player, Pokemon& pok);

};

#endif 

