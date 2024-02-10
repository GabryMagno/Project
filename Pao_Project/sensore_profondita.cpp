#include "sensore_profondita.h"

Sensore_Profondità::Sensore_Profondità(int depth_max,int depth):
    profondità_max((depth_max>12000||depth_max<1200)? 10000 : depth_max),
    profondità(depth>profondità_max ? 1000 : depth)
{
    nome="SNSR-PRFD-";
    for(int i=0;i<3;i++){
        nome+=rand()%9+48;
    }
}

Sensore_Profondità::Sensore_Profondità(std::string name, std::string water,int max_depth,int depth):Sensore_Acquatico(name,water),profondità_max((max_depth>12000||max_depth<1200)? 10000 : max_depth),
    profondità(depth>profondità_max ? 1000 : depth){}

std::string Sensore_Profondità::Get_Nome() const{return nome;}

int Sensore_Profondità::Get_Profondità() const{return profondità;}

int Sensore_Profondità::Get_Profondità_Max() const{return profondità_max;}

std::string Sensore_Profondità::Get_Img_Path() const{return ":/Immagini/Profondita.png";}

Sensore_Profondità* Sensore_Profondità::clone() const{return new Sensore_Profondità(*this);}

void Sensore_Profondità::Set_Profondità(int deep){(deep>profondità_max ? profondità=profondità_max : profondità=deep);}

void Sensore_Profondità::Set_Profondità_Max(int depth_max){((depth_max<1200||depth_max>12000) ? profondità_max=10000 : profondità_max=depth_max);}

void Sensore_Profondità::Accept(Sensor_Visitor* v) const{v->Visit(*this);}

std::string Sensore_Profondità::Info() const{
    std::string s=std::to_string(profondità);
    if(profondità==0) return "Siamo sulla superficie dell'acqua.";
    if(profondità==profondità_max) return "Siamo sul fondale ad una profondità di "+s+" metri dalla superficie.";
    return "Siamo ad una profondità di "+s+" metri dalla superficie.";
}

Sensore* Sensore_Profondità::FromJson(const QJsonObject& obj){
    return new Sensore_Profondità(
        obj.value("Nome").toString().toStdString(),
        obj.value("Zona").toString().toStdString(),
        obj.value("Max_Profondità").toInt(),
        obj.value("Profondità").toInt()
        );
}
