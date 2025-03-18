#include <iostream> 
#include <algorithm> 
#include <cctype>
#include "player.h"
#include "hero_info.h"
void printsomething(){
    std::cout << "this is print" << std::endl;
}
void herocreation(){
    std::string name;
    std::string hero_class;
    std::string hero_species;
    unsigned max_hp
    std::cout << "This is going to be your herobuilding walkthrough!\n";
    std::cout << "Please input your heroes name first, soldier:\n"; 
    std::cin >> name;
    std::cout << "\n";
    std::cout << "I am very pleased to meet you " << name << "\n\n\n";
    std::cout << "The existing classes are as follows:";
    std::cout << "\nBARBARIAN \nBARD \nCLERIC \nDRUID \nFIGHTER \nMONK \nPALADIN \nRANGER \nROGUE \nSORCERER \nWARLOCK \nWIZARD\n\n";
    std::cout << "Tell me, what class do you want to be? \n"; 
    std::cin >> hero_class;
    std::cout << "\n";
    std::string hero_class_tmp=hero_class;
    std::transform(hero_class_tmp.begin(), hero_class_tmp.end(), hero_class_tmp.begin(), ::tolower);
    std::cout << "It is nice to have another fellow " << hero_class_tmp << "!\n\n\n";
    std::cout << "The existing species are as follows:";
    std::cout << "\nDRAGONBORN \nDWARF \nELF \nGNOME \nHALF_ELF \nHALFLING \nHALF_ORC \nHUMAN \nTIEFLING\n\n";
    std::cout << "Tell me, what species do you want to be? \n";
    std::cin >> hero_species; 
    std::cout << "\n"; 
    std::string hero_species_tmp=hero_species; 
    std::transform(hero_species_tmp.begin(), hero_species_tmp.end(), hero_species_tmp.begin(), ::tolower);
    std::cout << "It is nice to get more " << hero_species_tmp << "s down here, we were running out!\n\n\n";

    
}
int main(){
    int status=0;
    std::unique_ptr<Player> player= std::make_unique<Player>("Aron", "Tinkl");
    printsomething();
    herocreation();
    return 0;
}
