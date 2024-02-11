#ifndef MODEL_H
#define MODEL_H
#include"lista_sensori.h"
#include"sensore.h"

class Model{
private:
    Lista_Sensori<Sensore*> sensori;
public:
    Model() =default;
    ~Model();
    Sensore* Get_Sensore(unsigned int i) const;
    void Aggiungi_Sensore(Sensore*);
    void Elimina_Sensore(Sensore*);
    Lista_Sensori<Sensore*> Get_ListaSensori();
    unsigned int Get_Numero_Sensori() const;
};

#endif // MODEL_H
