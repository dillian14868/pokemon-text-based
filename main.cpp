#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include "pokemon.cpp"
#include "person.cpp"
#include "item.cpp"
#include "town.cpp"
using namespace std;

string coin_tail =                                                                                        
"                            ████████████\n"                                               
"                        ██████      ████████\n"                                           
"                      ████              ████\n"                                           
"                     ██    ████████████   ████\n"                                          
"                   ████         ██           ███\n"                                          
"                   ██           ██           ███\n"                                        
"                   ██           ██           ███\n"                                                                              
"                   ████         ██          ███\n"                                          
"                     ██                    ████\n"                                                                                  
"                       ███████      ████████\n"                                            
"                           ████████████\n";  

string coin_head =                                                                                        
"                            ████████████\n"                                               
"                        ██████      ████████\n"                                           
"                      ████              ████\n"                                           
"                     ██    ███      ███   ████\n"                                          
"                   ████    ███      ███     ███\n"                                          
"                   ██      ████████████      ███\n"                                        
"                   ██      ███      ███      ███\n"                                                                              
"                   ████    ███      ███     ███\n"                                          
"                     ██                    ███\n"                                                                                  
"                       ███████      ████████\n"                                            
"                           ████████████\n"; 
                                                                                                                                                                                                                                            

/*
Alternates between whether the player or the pokemon attack
*/
void battle_turns(Pokemon& enemy_pok, Pokemon& your_pok, bool same,  Player& player, bool first, bool gym_battle) {
    while ((enemy_pok.get_health() > 0 && your_pok.get_health() > 0)){
        string attack;
        if(same) {
            cout<<"\nYour choices when it is your turn are to run(a), choose an attack (b), or catch a pokemom(c)" << endl;
            cout<<"Type a, b, or c. If you type none of the choices you will be automatically fight. You can't choose run your first battle." << " \nAnd, if you choose (a) during a gym battle you will be able to pick different pokemon." << endl;
            cin >> attack;
            if(attack == "a" && first == false) {
                return;
            } else if(attack == "c" && !gym_battle) {
                cout << "Your items." << endl;
                cout << player.get_items() << endl;
                if(player.catch_pokemon(enemy_pok)) {
                    return;
                };
            } else {
                std::cout << your_pok.get_attacks() << endl;
                your_pok.attack(attack, enemy_pok, true);
                same = false;
            }
        } else {
            enemy_pok.attack(attack, your_pok, false);
            same = true;
        }
    }
}

/*
Gets a pokemon from any map and returns it by reference
*/
Pokemon& get_pok_by_name(std::map<std::string, Pokemon>& map) {
    while(true) {
        std::cout << "Which of your pokemon will fight?" << endl;
        std::cout << "Your choices are the following: " << endl;
        cout << map;
        string answer;
        cin >> answer;
        
        auto choice = map.find(answer);
        if(choice != cend(map)) {  
            std::cout << "You chose the pokemon with the following stats " << endl;
            cout << choice->second << endl;  
            return choice->second;
        }
        cout << "Didn't choose a pokemon you had." << endl;
    }
}

/*
Outputs whether you won, caught the pokemon, lost, or ran away.
Also drops items, money or evolves your pokemon.
*/
void battle_end(Pokemon& enemy_pok, Pokemon& your_pok, bool same,  Player& player, bool first, bool gym_battle) {
    int health_at_start = enemy_pok.get_health();
    unsigned long start_size = player.get_pokemon().size();
    battle_turns(enemy_pok, your_pok, same, player, first, gym_battle); 
    if(enemy_pok.get_health() <= 0) {
        cout << "YOU WON" << endl;
        cout << "\n" << endl;
        enemy_pok.drop_money(player, health_at_start);
        enemy_pok.drop_item(player);
        your_pok.evolve();
    } else if (your_pok.get_health() <= 0) {
        cout << "Your pokemon fainted in battle. Please use a Revival or Potion to heal it." << endl;
    } else if(start_size + 1 == player.get_pokemon().size()) {
        cout << "You used Red Pokeball"  << endl;
    }
    else {
        cout << "You ran away!" << endl;
    }
}

/*
Picks whether the player goes first based on whether they chose heads or tails
*/
void battle(Pokemon& enemy_pok, std::map<std::string, Pokemon>& map, Player& player, bool first, bool gym_battle) {
    string answer;
    std::cout << "This is a battle! Type heads or tails (if you pick neither you will automatically be heads)" << endl;
    cin >> answer;         
    std::system("clear");
    auto heads_or_tails = std::rand() % 2; 
    if(answer == "heads" && heads_or_tails == 1) {
        cout << coin_head << endl;
        std::cout << "You chose heads and the coin flipped heads" << endl;
        std::cout << "You get to go first!" << endl;
        battle_end(enemy_pok, get_pok_by_name(map), true, player, first, gym_battle);
    } else if(answer == "tails" && heads_or_tails == 0) {
        cout << coin_tail << endl;  //
        std::cout << "You chose tails and the coin flipped tails" << endl;
        std::cout << "You get to go first!" << endl;
        battle_end(enemy_pok, get_pok_by_name(map), true, player, first, gym_battle);
    } else if(answer == "tails" && heads_or_tails == 1) {
        cout << coin_head << endl;
        std::cout << "You chose tails and the coin flipped heads" << endl;
        std::cout << "They get to go first!" << endl;
        battle_end(enemy_pok, get_pok_by_name(map), false, player, first, gym_battle);
    } else {
        cout << coin_tail << endl;
        std::cout << "You chose heads and the coin flipped tails" << endl;
        std::cout << "They get to go first!" << endl;
        battle_end(enemy_pok, get_pok_by_name(player.get_pokemon()), false, player, first, gym_battle);
    }
}

/*
Finds the health of the bench
*/
int health_of_bench(std::map<std::string, Pokemon>& bench) {
    int health = 0;
    for (auto& pok : bench) {
        health += pok.second.get_health();
    }
    return health;
}

/*
Starts the gym battle with three enemy pokemon, you choose three of your own pokemon to fight as well
(Needs improvement, long and sloppy function)
*/
bool gym(Player& player) {
    if(player.get_pokemon().size() >= 3) {
        cout << "This is a gym battle!!!" << endl;
        cout << "You will fight three of gym leader Scar's pokemon" << endl;
        cout << "You need to choose three of your own pokemon." << endl;
        Person gym_leader;
        string answer;
        Pokemon& pok1 = get_pok_by_name(player.get_pokemon());
        Pokemon& pok2 = get_pok_by_name(player.get_pokemon());
        Pokemon& pok3 = get_pok_by_name(player.get_pokemon());

        std::map<std::string, Pokemon> bench = {{pok1.get_name(), pok1},
        {pok2.get_name(), pok2}, {pok3.get_name(), pok3}};

        auto it = gym_leader.get_pokemon().begin();  
        auto first_pok = it->second;
        auto second_pok = std::next(it, 1)->second;
        auto third_pok = std::next(it, 2)->second;

        while(bench.size() != 3) {
            cout << "You probaby chose two of the same pokemon. Pick a different one." << endl;
            bench.insert({get_pok_by_name(player.get_pokemon()).get_name(), get_pok_by_name(player.get_pokemon())});
        }

        cout << "Great! Now it is time for your first gym battle" << endl;
        while (first_pok.get_health() > 0) {
            if(health_of_bench(bench) <= 0) {  
                return false;
            }
            battle(first_pok, bench, player, false, true);
        }

        cout << "You did it! Now it is time for your second battle." << endl;
        cout << "You can only run away in between battles. Type a to run away or b to stay. Any other response you stay." << endl;
        cin >> answer;
        if(answer == "a") {
            return false;
        } 

        while (second_pok.get_health() > 0) {
            if(health_of_bench(bench) <= 0) {
                return false;
            }
            battle(second_pok, bench, player, false, true);
        }

        cout << "You did it! Now it is time for your third battle." << endl;
        cout << "You can only run away in between battles. Type a to run away or b to stay. Any other response you stay." << endl;
        cin >> answer;
        if(answer == "a") {
            return false;
        } 

        while (third_pok.get_health() > 0) {
            if(health_of_bench(bench) <= 0) {
                return false;
            }
            Pokemon pok = get_pok_by_name(bench);
            battle(third_pok, bench,player, false, true);
        }

        if(health_of_bench(bench) <= 0 || health_of_bench(bench) <= 0) {
            cout << "You lost the battle try again" << endl;
            return false;
        } 

        cout << "Congrats you won!!!" << endl;
        return true;

    } else {
        cout << "Sorry! You don't have enough pokemon to fight in a gym battle yet. You must have at least 3." << endl;

    }
    return true;
}

/*
Introduces the player to the game and allows them to choose the first pokemon
*/
void intro(Player& player) {
    string answer;
    cout << "Welcome to Lavender town!" << endl;
    cout << "What is your name?" << endl;
    cin >> answer; 
    player.set_player(answer);
    cout << "Hi " << player.get_player() << ". Now it is time to choose your starting pokemon." << endl;
    while(true) {
        cout << "Type a for Bulbasaur, type b for Squirtle, type c for Charmander" << endl;
        cin >> answer;
        if(answer == "a" || answer == "b" || answer == "c") {
            player.add_pokemon(answer);
            player.see_pokedex();
            break;
        } 
        cout << "You didn't choose a valid letter" << endl;
    }
}

/*
Initiates the first battle
*/
void first_battle(Player& player, Pokemon& enemy_pok) {
    std::cout << "Now it is time for your first battle" << endl; 
    battle(enemy_pok, player.get_pokemon(), player, true, false);
    std::cout << "Congrats you've completed your first battle! There are now five options you can choose from:" << endl;
}

/*
Prompts the user to buy something and then charges them
*/
void go_to_store(Player& player, Town& lavender) {
    string answer;
    fflush(stdin);
    cout << "What would you like to buy? Your choices are Potion ($10), Red Pokeball ($30), or Revival ($100)" << endl;
    cout << "You have $" << player.get_money() << " dollars to spend." << endl;
    cout << "Type Potion, Red Pokeball, Revival, and exit to leave." << endl;
    getline(cin, answer);
    cout << endl;
    lavender.buy(player, answer);
}

/*
Uses the item the user wanted and then on the pokemon the user chooses.
Reports the modified pokemon stats.
*/
void use_an_item(Player& player) {
    string answer;
    cout << "Which of your items would you like to use?" << endl;
    cout << "These are your chooses: " << endl;
    cout << player.get_items();
    fflush(stdin);
    getline(cin, answer);
    
    auto it = find_if(player.get_items().begin(), player.get_items().end(), [&answer](std::unique_ptr<Item>& b) 
    { return answer == b->get_name() ;});
    cout << endl;
    if(cend(player.get_items()) != it) {
        cout << "Which of your pokemon would you like to use?" << endl;
        cout << "These are your choices: " << endl;
        cout << player.get_pokemon();
        cin >> answer;
        cout << endl;
        auto pok = player.get_pokemon().find(answer);  
        if(cend(player.get_pokemon()) != pok) {
            (*it)->use(player, pok->second); 
            cout << "Modified stats: " << endl;
            cout << pok->second << endl;
        } 
    }
}

/*
Driver code.
Gives user options to go fight, gym battle, buy items, or quit.
*/
int main() {
    std::srand(3); //put here for testing, for randomized input replace with std::srand(time(0));
    std::system("clear"); 
    string answer;
    Player player("");
    Town lavender;
    bool gym_not_deafeated = true;
 
    intro(player);
    Pokemon enemy_pok = lavender.generate_pokemon();
    first_battle(player, enemy_pok);
    while(gym_not_deafeated) {
        std::cout << endl;
        std::cout << "Fighting more pokemon in the fields (a), going to the store to buy supplies (b), " << endl;
        std::cout << "trying to fight the gym boss (c), using an item(d), and quiting (quit)." << endl;
        std::cout << "Warning quiting doesn't save your progress. Type a, b, c, d or quit" << endl;
        cin >> answer;
        std::system("clear");
        if("a" == answer) {
            Pokemon enemy_pok = lavender.generate_pokemon();
            battle(enemy_pok, player.get_pokemon(), player, false, false);
        } else if("b" == answer) {
            go_to_store(player, lavender);
        } else if("c" == answer){
            gym_not_deafeated = gym(player);
        } else if("d" == answer){
            use_an_item(player);
        } else if(answer == "quit"){
            return 0;
        }
        else {
            std::cout << "Incorrect choice try again. Type a, b, c, d or quit." << endl;
        }
    }
}