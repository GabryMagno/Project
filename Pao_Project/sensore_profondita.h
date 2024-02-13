#ifndef SENSORE_PROFONDITA_H
#define SENSORE_PROFONDITA_H
#include"sensore_acquatico.h"

class Sensore_Profondità : public Sensore_Acquatico{
private:
    int profondità_max;
    int profondità;
public:
    Sensore_Profondità(int =10000,int =1000);
    Sensore_Profondità(std::string,std::string,int,int);
    int Get_Profondità() const;
    int Get_Profondità_Max() const;
    std::string Get_Nome() const override;
    std::string Get_Img_Path() const override;
    virtual Sensore_Profondità* clone() const override;
    void Set_Profondità(int);
    void Set_Profondità_Max(int);
    void Accept(Sensor_Visitor* v) const override;
    std::string Info() const override;
    Sensore_Profondità* FromJson(const QJsonObject&) override;
};

#endif // SENSORE_PROFONDITA_H
