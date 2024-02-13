#ifndef SENSORE_TEMPERATURA_H
#define SENSORE_TEMPERATURA_H
#include"sensore_terrestre.h"


class Sensore_Temperatura : public Sensore_Terrestre{
private:
    int temperatura_min;
    int temperatura_max;
    int temperatura;
public:
    Sensore_Temperatura(int =-30,int =60,int =25);
    Sensore_Temperatura(std::string,int,int,int);
    virtual Sensore_Temperatura* clone() const override;
    std::string Get_Nome() const override;
    int Get_Temperatura() const;
    int Get_Temperatura_Max() const;
    int Get_Temperatura_Min() const;
    std::string Get_Img_Path() const override;
    void Set_Temperatura(int);
    void Set_Temperatura_Max(int);
    void Set_Temperatura_Min(int);
    void Accept(Sensor_Visitor* v) const override;
    std::string Info() const override;
    Sensore_Temperatura* FromJson(const QJsonObject&) override;
};

#endif // SENSORE_TEMPERATURA_
