#ifndef HERO_INFO_H
#define HERO_INFO_H
#include <iostream> 
enum class Hero_Class{ BARBARIAN, BARD, CLERIC, DRUID, FIGHTER, MONK, PALADIN,
RANGER, ROGUE, SORCERER, WARLOCK, WIZARD};
enum class Hero_Species{ DRAGONBORN, DWARF, ELF, GNOME, HALF_ELF, HALFLING,
HALF_ORC, HUMAN, TIEFLING};
inline std::ostream& operator<<(std::ostream& o, Hero_Class m){
	switch(m){
		case Hero_Class::BARBARIAN: o << "Barbarian"; return o; 
		case Hero_Class::BARD: o << "Bard"; return o; 
		case Hero_Class::CLERIC: o << "Cleric"; return o; 
		case Hero_Class::DRUID: o << "Druid"; return o; 
		case Hero_Class::FIGHTER: o << "Fighter"; return o; 
		case Hero_Class::MONK: o << "Monk"; return o; 
		case Hero_Class::PALADIN: o << "Paladin"; return o; 
		case Hero_Class::RANGER: o << "Ranger"; return o; 
		case Hero_Class::ROGUE: o << "Rogue"; return o; 
		case Hero_Class::SORCERER: o << "Sorcerer"; return o; 
		case Hero_Class::WARLOCK: o << "Warlock"; return o; 
		case Hero_Class::WIZARD: o << "Wizard"; return o; 
		default: return o; 
	}
}
inline std::ostream& operator<<(std::ostream& o, Hero_Species m){
	switch(m){
		case Hero_Species::DRAGONBORN: o << "Dragonborn"; return o; 
		case Hero_Species::DWARF: o << "Dwarf"; return o; 
		case Hero_Species::ELF: o << "Elf"; return o; 
		case Hero_Species::GNOME: o << "Gnome"; return o; 
		case Hero_Species::HALF_ELF: o << "Half-Elf"; return o; 
		case Hero_Species::HALFLING: o << "Halfling"; return o; 
		case Hero_Species::HALF_ORC: o << "Half-Orc"; return o; 
		case Hero_Species::HUMAN: o << "Human"; return o; 
		case Hero_Species::TIEFLING: o << "Tiefling"; return o; 
	}

}
#endif
