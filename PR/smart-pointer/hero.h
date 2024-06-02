#ifndef HERO_H 
#define HERO_H 

#include <iostream> 
#include <map>
#include "hero_info.h" 
#include "monster.h"

class Hero {
private:
    unsigned id; 
    std::string name; 
    Hero_Class hero_class; 
    Hero_Species hero_species; 
    unsigned level; 
    unsigned max_hp; 
    unsigned current_hp; 
    std::map<std::string, unsigned> abilities; 
    static unsigned next_id; 	
    
public: 
    Hero(std::string name, Hero_Class hero_class, Hero_Species hero_species,
         unsigned max_hp, const std::map<std::string,unsigned>& abilities)
        : id{next_id}, 
          name{name}, 
          hero_class{hero_class}, 
          hero_species{hero_species}, 
          level{1}, 
          max_hp{max_hp}, 
          current_hp{max_hp}, 
          abilities{abilities}
    {
        if (name == "")throw std::runtime_error("Name cannot be empty"); 
      	if (level>20||level<0) throw std::runtime_error("Invalid level"); 
      	for(auto& x: abilities){
        if(x.first!="Strength"&&x.first!="Dexterity"&&x.first!="Constitution"&&x.first!="Intelligence"&&x.first!="Wisdom"&&x.first!="Charisma") throw std::runtime_error("Invalid name"); 
        if(x.second<=0||x.second>=21) throw std::runtime_error("Invalid skillpoints"); 
        }
      	if(abilities.size()<6) throw std::runtime_error("Missing abilities"); 
        increase_id(); 
    } 
    
    void increase_id() {
        next_id++; 
    }
    
    unsigned level_up() {
        if (level < 20) {
            level++; 
        } 
        return level; 
    }
    
   

bool fight(Monster& m) {
    while (current_hp > 0 && m.get_health() > 0) {
        unsigned MaxAbility=0;
        for (const auto& x : abilities) {
            if (x.second > MaxAbility) {
                MaxAbility = x.second;
            }
        }
        unsigned damage = level * MaxAbility;
        m.take_damage(damage);
        if (m.is_dead()) {
            return true;
        }
        if (current_hp > m.get_attack()) {
            current_hp -= m.get_attack();
        } else {
            current_hp = 0;
        }
    }
    return current_hp > 0;
}

    // Getter functions
    unsigned get_id() const { return id; }
    std::string get_name() const { return name; }
    Hero_Class get_hero_class() const { return hero_class; }
    Hero_Species get_hero_species() const { return hero_species; }
    unsigned get_level() const { return level; }
    unsigned get_max_hp() const { return max_hp; }
    unsigned get_current_hp() const { return current_hp; }
    std::map<std::string, unsigned> get_abilities() const { return abilities; }

}; 

inline std::ostream& operator<<(std::ostream& o, const Hero& obj) {
    o << "["  << obj.get_id() << ", " << obj.get_name() << ", (" << obj.get_hero_class() 
      << ", " << obj.get_hero_species()
      << ", " << obj.get_level() << "), {" << obj.get_abilities()["Charisma"]
      << ", " << obj.get_abilities()["Constitution"] << ", " << obj.get_abilities()["Dexterity"]
      << ", " << obj.get_abilities()["Intelligence"] << ", " << obj.get_abilities()["Strength"]
      << ", " << obj.get_abilities()["Wisdom"] 
      << "}, ("  << obj.get_current_hp() << "/" << obj.get_max_hp() << ") HP]";
    return o; 
}

#endif
