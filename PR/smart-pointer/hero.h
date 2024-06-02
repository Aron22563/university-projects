#ifndef HERO_H 
#define HERO_H 

//Libraries 
#include<iostream> 

class Hero{
	public: 
	private:
        unsigned id; 
	std::string name; 
	Hero_Class hero_class; 
	Hero_Species hero_species; 
	unsigned level; 
	unsigned max_hp; 
	unsigned current_hp; 
	map<std::string, unsigned> abilities; 
	static unsigned next_id{0}; 	
	public: 
	Hero(std::string name, Hero_Class hero_class, Hero_Species hero_species,
		   	unsigned max_hp, const map<std::string,unsigned>& abilities)
	      : name{name}, 
		id{next_id}, 
		hero_class{hero_class}, 
		hero_species{hero_species}, 
		level{1}, 
		max_hp{max_hp}, 
		current_hp{max_hp}, 
		abilities{abilities}{
			if(name==""){
			throw std::runtime_error("Name can not be empty"); 
			}
			Hero::increase_id();
		} 
	void increase_id(){
		next_id++; 
	}
	unsigned level_up(){
		if(level<20){
			level++; 
		} 
		else{
			std::cout << "Your level is " << level << std::endl;
		       	throw std::runtime_error("Maximum level reached"); 
		}
	return level; 
	}
	bool fight(Monster& m){
		if(current_hp<0){
			std::cout << "Du hast " << current_hp << " Leben, Kampf verloren"; 
		return false;
		}
	}
	std::ostream& operator<<(std::ostream& o, const Hero& obj){
	o << "["  << obj.id << ", " << obj.name << ", (" << obj.hero_class 
	  << ", " << obj.hero_species
	  << ", " << obj.level << "), {" << obj.abilities.charisma 
	  << ", " << obj.abilities.constitution << ", " << obj.abilities.dexterity 
	  << ", " << obj.abilities.strength << ", " << obj.abilities.intelligence 
	  << ", " << obj.abilities.wisdom 
	  << "}, ("  << obj.current_hp << "/" << obj.max_hp << ") HP]"; 
	return o; 
	}
}; 

#endif 
