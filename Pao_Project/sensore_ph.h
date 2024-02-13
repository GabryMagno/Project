#ifndef SENSORE_PH_H
#define SENSORE_PH_H
#include "sensore_acquatico.h"

class Sensore_pH : public Sensore_Acquatico{
private:
    float ph_min;
    float ph_max;
    float ph;
public:
    Sensore_pH(float =5.0,float =8.9,float =8.0);
    Sensore_pH(std::string,std::string,float,float,float);
    std::string Get_Nome() const override;
    float Get_pH_Min() const;
    float Get_pH_Max() const;
    float Get_pH() const;
    std::string Get_Img_Path() const override;
    virtual Sensore_pH* clone() const override;
    void Set_pH_Min(float);
    void Set_pH_Max(float);
    void Set_pH(float);
    void Accept(Sensor_Visitor* v)const override;
    std::string Info() const override;
    Sensore_pH* FromJson(const QJsonObject&) override;
};

#endif // SENSORE_PH_H
