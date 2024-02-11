#ifndef SENSORE_H
#define SENSORE_H
#include<string>
#include<ctime>
#include<cstdlib>
#include"sensor_visitor.h"
#include<QJsonObject>

class Sensore{
protected:
    std::string nome;
    std::string img_path;
public:
    Sensore(std::string name ="");
    virtual ~Sensore() =default;
    virtual std::string Get_Nome() const =0;
    virtual std::string Get_Img_Path() const =0;
    virtual Sensore* clone() const =0;
    virtual void Accept(Sensor_Visitor* v) const =0;
    virtual std::string Info() const =0;
    virtual Sensore* FromJson(const QJsonObject&) =0;
};

#endif // SENSORE_H
