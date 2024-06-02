#ifndef MONSTER_H 
#define MONSTER_H
#include <iostream> 
class Monster{
	public: 
	private: 
	std::string name; 
	unsigned health; 
	unsigned attack; 
	public:
        Monster(std::string name, unsigned health, unsigned attack):
	       	name{name}, health{health}, attack{attack}{
          if(name=="") throw std::runtime_error("Name of monster cannot be empty"); 
  				if(health==0) throw std::runtime_error("Health can not be 0");
  				if(attack==0) throw std::runtime_error("Attack can not be 0"); 
          }
	virtual ~Monster(){}
	virtual unsigned calculate_damage(unsigned dmg) const=0;
	virtual std::string additional_information() const=0; 
	void take_damage(unsigned dmg){
		if(health>=calculate_damage(dmg)){
			health=health-calculate_damage(dmg);
		}
		else{
			health=0; 
		}
	}
	bool is_dead() const{
	return health==0; 
	}
	friend std::ostream& operator<<(std::ostream& o, const Monster& h){
	o << "[" << h.name << ", " << h.health << " HP, " << h.attack 
		 << " ATK" << h.additional_information() << "]"; 
	return o; 
	}
	std::string get_name() const{return name;}
	unsigned get_attack() const{return attack;}
	unsigned get_health() const{return health;}
	
}; 
class Elite_Monster: public Monster{
	public: 
	private:
	unsigned defense; 	
	public: 
	Elite_Monster(std::string name, unsigned health, unsigned attack, unsigned defense):        Monster(name, health, attack), defense{defense}{}
	unsigned calculate_damage(unsigned dmg)const{
		if(defense>dmg){
		return 0; 
		}
		else{
		return dmg-defense; 
		}
	}
	std::string additional_information() const{
	       std::string answer= ", " + std::to_string(defense) + " DEF"; 
	       return answer; 	
	}
};
class Standard_Monster: public Monster{
	public: 
	private: 
	public: 
	Standard_Monster(std::string name, unsigned health, unsigned attack): 
		Monster(name, health, attack){}
	unsigned calculate_damage(unsigned dmg) const{
	return dmg; 
	}
	std::string additional_information()const{
	return ""; 
	}
}; 
#endif
