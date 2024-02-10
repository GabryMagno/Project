#ifndef SENSORE_ACQUATICO_H
#define SENSORE_ACQUATICO_H
#include "sensore.h"
#include<QString>

class Sensore_Acquatico : public Sensore{
private:
    std::string zona;
public:
    explicit Sensore_Acquatico(std::string ="OCEANO");
    Sensore_Acquatico(std::string,std::string);
    std::string GetWaterArea() const;
    void SetWaterArea(std::string);
};

#endif // SENSORE_ACQUATICO
