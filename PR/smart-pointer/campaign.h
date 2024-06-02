#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <iostream> 
#include <memory>
#include <map>
#include "hero.h"

class Campaign {
private:
    std::string name; 
    std::map<unsigned, std::weak_ptr<Hero>> heroes; 
    unsigned min_level{1};	
    
public: 
    Campaign(std::string name, unsigned min_level): name{name}, min_level{min_level} {
      if(name=="") throw std::runtime_error("Campaign name empty"); 
      if(min_level<1) throw std::runtime_error("Minimum level must be min. 1"); 
    }
  
  
    
    void add_hero(std::shared_ptr<Hero> h) {
        std::weak_ptr<Hero> WeakHero = h;
        if(h->get_level() < min_level)	
            throw std::runtime_error("Level is too low"); 
        
        for(auto x : heroes) {
            if(x.second.lock() == h) {
                throw std::runtime_error("Hero is already in the campaign"); 
            }
        }
        heroes.insert(std::make_pair(h->get_id(), WeakHero)); 
    }
    
    void encounter_monster(unsigned id, Monster& m) {
        for(auto& x : heroes) {
            if(x.first == id) {
                auto hero_ptr = x.second.lock();
              	bool won = hero_ptr->fight(m); 
                if(won) 
                    hero_ptr->level_up(); 
            }
        }
    }

    unsigned remove_dead_and_expired() {
    unsigned RemoveCounter{0};
    for(auto i = heroes.begin(); i != heroes.end(); ) {
         if(i->second.expired()||i->second.lock()->get_current_hp()==0){
                i = heroes.erase(i);
                ++RemoveCounter; 	
            } 
            else {
                ++i;	
            }
        }
    return RemoveCounter;
}

    
    friend std::ostream& operator<<(std::ostream& o, const Campaign& p) {
    bool first = true; 
    o << "[" << p.name << " Campaign, Min_Level " << p.min_level << ", {"; 
    for(auto& x : p.heroes) {
        auto hero_ptr = x.second.lock();
        if(hero_ptr) {
            if(first) {
                o << *hero_ptr; 
                first = false; 
            } else {
                o << ", " << *hero_ptr; 
            }
        }
    }
    o << "}]";  
    return o; 
}
};

#endif
