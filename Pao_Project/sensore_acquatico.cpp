#include "sensore_acquatico.h"

Sensore_Acquatico::Sensore_Acquatico(std::string water):zona(water){}

Sensore_Acquatico::Sensore_Acquatico(std::string name,std::string water):Sensore(name),zona(water){}

std::string Sensore_Acquatico::GetWaterArea() const{
    return zona;
}

void Sensore_Acquatico::SetWaterArea(std::string water){
    zona=water;
}
