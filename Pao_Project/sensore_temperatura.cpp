#include "sensore_temperatura.h"

Sensore_Temperatura::Sensore_Temperatura(std::string name,int min,int max,int temperature):
    Sensore_Terrestre(name),
    temperatura_min((min<-30||min>=60) ? -30 : min),
    temperatura_max((max<=temperatura_min||max>60) ? 60 : max),
    temperatura((temperature<temperatura_min||temperature>temperatura_max) ? (temperatura_min+temperatura_max)/2 : temperature){}

Sensore_Temperatura::Sensore_Temperatura(int min,int max,int temperature):
    temperatura_min((min<-30||min>=60) ? -30 : min),
    temperatura_max((max<=temperatura_min||max>60) ? 60 : max),
    temperatura((temperature<temperatura_min||temperature>temperatura_max) ? (temperatura_min+temperatura_max)/2 : temperature)
{
    nome="SNSR-TMPR-";
    for(int i=0;i<3;i++){
        nome+=rand()%9+48;
    }
}

std::string Sensore_Temperatura::Get_Nome() const{return nome;}

int Sensore_Temperatura::Get_Temperatura() const{return temperatura;}

int Sensore_Temperatura::Get_Temperatura_Min() const{return temperatura_min;}

int Sensore_Temperatura::Get_Temperatura_Max() const{return temperatura_max;}

std::string Sensore_Temperatura::Get_Img_Path() const{return ":/Immagini/Temperatura.png";}

Sensore_Temperatura* Sensore_Temperatura::clone() const{return new Sensore_Temperatura(*this);}

void Sensore_Temperatura::Set_Temperatura(int temp){((temp<temperatura_min || temp>temperatura_max) ? temperatura=(temperatura_min+temperatura_max)/2 : temperatura=temp);}

void Sensore_Temperatura::Set_Temperatura_Min(int t_min){((t_min>=temperatura_max||t_min<-30) ? temperatura_min=-30 : temperatura_min=t_min);}

void Sensore_Temperatura::Set_Temperatura_Max(int t_max){((t_max<=temperatura_min||t_max>60) ? temperatura_max=60 : temperatura_max=t_max);}

void Sensore_Temperatura::Accept(Sensor_Visitor* v) const{v->Visit(*this);}

std::string Sensore_Temperatura::Info() const{
    if(temperatura<=0) return "Molto freddo";
    if(temperatura<=18) return "Freddo";
    if(temperatura>=38) return "Molto caldo";
    if(temperatura>28) return "Caldo";
    return "Temperatura ambiente";
}

Sensore_Temperatura* Sensore_Temperatura::FromJson(const QJsonObject& obj){
    return new Sensore_Temperatura(
        obj.value("Nome").toString().toStdString(),
        obj.value("Min_Temperatura").toInt(),
        obj.value("Max_Temperatura").toInt(),
        obj.value("Temperatura").toInt()
        );
}
