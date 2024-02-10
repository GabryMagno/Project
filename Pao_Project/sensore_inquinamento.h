#ifndef SENSORE_INQUINAMENTO_H
#define SENSORE_INQUINAMENTO_H
#include"sensore_terrestre.h"

class Sensore_Inquinamento : public Sensore_Terrestre{
    uint pm_2_5;
    uint pm_10;
public:
    Sensore_Inquinamento(uint =0,uint =0);
    Sensore_Inquinamento(std::string,uint =0,uint =0);
    virtual Sensore_Inquinamento* clone() const override;
    std::string Get_Nome() const override;
    std::string Get_Img_Path() const override;
    uint Get_PM_2_5() const;
    uint Get_PM_10() const;
    void Set_PM_2_5(uint);
    void Set_PM_10(uint);
    void Accept(Sensor_Visitor* v) const override;
    std::string Info() const override;
    Sensore* FromJson(const QJsonObject&) override;
};

#endif // SENSORE_INQUINAMENTO_H
