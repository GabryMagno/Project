#ifndef SENSOR_VISITOR_H
#define SENSOR_VISITOR_H

class Sensore_Inquinamento;
class Sensore_pH;
class Sensore_Profondità;
class Sensore_Temperatura;

class Sensor_Visitor{
public:
    virtual ~Sensor_Visitor() =default;
    virtual void Visit(const Sensore_Inquinamento&) =0;
    virtual void Visit(const Sensore_Profondità&) =0;
    virtual void Visit(const Sensore_Temperatura&) =0;
    virtual void Visit(const Sensore_pH&) =0;
};

#endif // SENSOR_VISITOR_H
