#ifndef VISITOR_JSON_H
#define VISITOR_JSON_H
#include<QJsonObject>
#include"sensor_visitor.h"
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"

class Visitor_Json : public Sensor_Visitor{
private:
    QJsonObject obj;
public:
    QJsonObject Get_Obj() const;
    void Visit(const Sensore_Inquinamento&);
    void Visit(const Sensore_Profondità&);
    void Visit(const Sensore_Temperatura&);
    void Visit(const Sensore_pH&);
};

#endif // VISITOR_JSON_H
