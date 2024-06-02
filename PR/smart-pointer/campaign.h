#ifndef CAMPAIGN_H
#define CAMPAIGN_H

//Libaries 
#include <iostream> 
#include <memory> 

class Campaign{
	public: 
	private:
	std::string name; 
	map<unsigned, weak_ptr<Hero>> heroes; 
	unsigned min_level{1}	
	public: 
	Campaign(std::string name, unsigned min_level): name{name}, min_level{min_level}{}
	void add_hero(shared_ptr<Hero> h){
	std::weak_ptr<Hero> WeakHero=h;
        if(h->level<min_level)	
		throw std::runtime_error("Level is too low"); 
	for(auto x:heroes){
		if(x.second.lock()==h){
			throw std::runtime_error("Hero is already in campaign"); 
		}
	}
	heroes.insert(std::make_pair(h->id, WeakHero)); 
	}
	void encounter_monster(unsigned id, Monster& m){
		for(auto& x: heroes){
			if(x.first()==id){
				auto hero_ptr=x.second.lock(); 
				bool won=hero_ptr->fight(m); 
				if(won) x.second.level_up(); 
			}
		}
	}

	unsigned remove_dead_and_expired() {
	    unsigned RemoveCounter{0};
	    for(auto i=heroes.begin(); i!=heroes.end()) {
		auto hero_ptr = i->second.lock();
		if(!hero_ptr||hero_ptr->current_hp==0) {
		    i=heroes.erase(i); //Assign i to the next valid iterator in heroes
		    RemoveCounter++; 	
		} 
		else {
		    i++;	
		}
	    }
	    return RemoveCounter;
	}
	std::ostream& operator<<(ostream& o, const Campaign& p){
	o << "[" << name << " Campaign, Min_Level " << min_level << ",{"; 
	for(auto x: heroes){
		if(first){
			o << *x.second.lock(); 
			first=false; 
		}
		o << ", " << *x.second.lock(); 
	}
	first=true; 
	o << "}]";  
	return o; 
	}

};
#endif
