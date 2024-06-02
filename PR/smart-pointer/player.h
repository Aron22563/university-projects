#ifndef PLAYER_H 
#define PLAYER_H

//Libraries 
#include <iostream> 
#include <memory> 
#include <map>
#include "hero.h" 
#include "campaign.h" 
#include "monster.h"
class Player{
	public: 
	private:
	std::string first_name; 
	std::string last_name; 
	std::map<unsigned, std::shared_ptr<Hero>> heroes; 
	std::unique_ptr<Campaign> campaign; 	
	public:
       //Constructor	
	Player(std::string first_name, std::string last_name): 
	first_name{first_name}, last_name{last_name}{
  if(first_name=="") throw std::runtime_error("First name can not be empty"); 
  if(last_name=="") throw std::runtime_error("Last name can not be empty"); 
  }
	//Create hero function
	unsigned create_hero(const std::string& name, Hero_Class hero_class,
		       	Hero_Species hero_species, unsigned max_hp,
		       	const std::map<std::string, unsigned>& abilities)
	{
		std::shared_ptr<Hero> hero= std::make_shared<Hero>
			(name, hero_class, hero_species, max_hp, abilities);  

		heroes.insert(std::make_pair(hero->get_id(), hero)); 
	return hero->get_id(); 
	}
	std::string get_first_name()const{ return first_name;}
	std::string get_last_name()const{ return last_name;}
	std::map<unsigned, std::shared_ptr<Hero>> get_heroes()const{return heroes;}
	
	void create_campaign(std::string name, unsigned min_level, unsigned id) {
	    auto it = heroes.find(id);
	    if (it != heroes.end()) {
		campaign = std::make_unique<Campaign>(name, min_level);
		campaign->add_hero(it->second);    
	    }
	    else { 
		throw std::runtime_error("No hero found with the provided id.");
	    }
	}
		
	void join_friends_campaign(Player& pfriend, unsigned id) {
	    if (pfriend.campaign) {
		auto it = heroes.find(id);
		if (it != heroes.end()) {
		    pfriend.campaign->add_hero(it->second);
		} else {
		    throw std::runtime_error("Hero not in List");
		}
	    } else {
		throw std::runtime_error("Friend has no campaign");
	    }
	}
	
	void transfer_campaign(Player& pfriend) {
	    if (campaign){
		pfriend.campaign = std::make_unique<Campaign>(*campaign);
		campaign.reset(); 
	    } else {
		throw std::runtime_error("No campaign to transfer");
	    }
	}
	unsigned remove_dead(){
	unsigned RemoveCounter{0}; 
	for(auto i= heroes.begin(); i!= heroes.end(); ){
		auto hero_ptr= i->second; 
		if(!hero_ptr||hero_ptr->get_current_hp() ==0){
			i=heroes.erase(i); 
			RemoveCounter++; 
		}
		else{
			i++; 
		}
	}
	return RemoveCounter; 
	}
	std::ostream& print_campaign(std::ostream& o)const {
		if(campaign){
			o << *campaign;
			return o; 
		}
		else{
			o << "[]"; 
			return o; 
		}
	}
	friend std::ostream& operator<<(std::ostream& o, const Player& p){
	bool first=true; 
	o << "[" << p.get_first_name() << " " << p.get_last_name() << ", {"; 
	for(auto x: p.get_heroes()){
		if(first){
		o << *x.second; 
		first=false; 
		}
    else{
		o << ", " << *x.second; 
    }
	} 
	o << "}, ";
	p.print_campaign(o); 
  o << "]"; 
	return o; 
	}
}; 
#endif
