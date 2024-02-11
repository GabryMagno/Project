#include "model.h"
#include<iostream>
Model::~Model(){
    for(Lista_Sensori<Sensore*>::Iterator it= sensori.begin();it!=sensori.end();++it){
        delete *it;
    }
}

Sensore* Model::Get_Sensore(unsigned int i) const{
    return sensori[i];
}

void Model::Aggiungi_Sensore(Sensore* snsr){
    sensori.Insert_Front(snsr);
}

Lista_Sensori<Sensore*> Model::Get_ListaSensori(){
    return sensori;
}

void Model::Elimina_Sensore(Sensore* snsr){
    sensori.Erase(snsr);
}

unsigned int Model::Get_Numero_Sensori() const{
    return sensori.Size();
}
