#include "sensore_inquinamento.h"

Sensore_Inquinamento::Sensore_Inquinamento(uint p2,uint p10):pm_2_5(p2),pm_10(p10){
    nome="SNSR-INQM-";
    for(int i=0;i<3;i++){
        nome+=rand()%9+48;
    }
}

Sensore_Inquinamento::Sensore_Inquinamento(std::string name,uint p2,uint p10):Sensore_Terrestre(name),pm_2_5(p2),pm_10(p10){}

std::string Sensore_Inquinamento::Get_Nome() const{return nome;}

std::string Sensore_Inquinamento::Get_Img_Path() const{return ":/Immagini/PM.png";}

uint Sensore_Inquinamento::Get_PM_2_5() const{return pm_2_5;}

uint Sensore_Inquinamento::Get_PM_10() const{return pm_10;}

Sensore_Inquinamento* Sensore_Inquinamento::clone() const{return new Sensore_Inquinamento(*this);}

void Sensore_Inquinamento::Set_PM_2_5(uint p2){pm_2_5=p2;}

void Sensore_Inquinamento::Set_PM_10(uint p10){pm_10=p10;}

void Sensore_Inquinamento::Accept(Sensor_Visitor* v) const{v->Visit(*this);}

std::string Sensore_Inquinamento::Info() const{
    if(pm_10>=50 && pm_2_5>=25) return "I livelli delle polveri sottili sono oltre il limite giornaliero consentito(pm_10>=50[µg/m3] e pm_2,5>=25[µg/m3])";
    else if(pm_10>=50) return "I livelli di PM_10 sono oltre il limite giornaliero consentito(pm_10>=50[µg/m3])";
    else if( pm_2_5>=25) return "I livelli di PM_2,5 sono oltre il limite giornaliero consentito(pm_2,5>=25[µg/m3])";
    else return "I livelli di polveri sottili sono nella norma";
}

Sensore* Sensore_Inquinamento::FromJson(const QJsonObject& obj){
    return new Sensore_Inquinamento(
        obj.value("Nome").toString().toStdString(),
        obj.value("PM_2,5").toInt(),
        obj.value("PM_10").toInt()
        );
}
