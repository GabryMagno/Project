#include "sensore_ph.h"

Sensore_pH::Sensore_pH(float ph0,float ph1,float p):
    ph_min((ph0<5.0 || ph0>=8.9) ? 5.0 : ph0),
    ph_max((ph1<=ph_min || ph1>8.9) ? 8.9 : ph1),
    ph((p<ph_min || p>ph_max) ? 8 : p)
{
    nome="SNSR-PH-";
    for(int i=0;i<3;i++){
        nome+=rand()%9+48;
    }
}

Sensore_pH::Sensore_pH(std::string name, std::string water, float ph0, float ph1, float p):
    Sensore_Acquatico(name,water),
    ph_min((ph0<0 || ph0>=8.9) ? 5.0 : ph0),
    ph_max((ph1<ph_min || ph1>8.9) ? 8.9 : ph1),
    ph((p<ph_min||p>ph_max) ? 8.0 : p){}

float Sensore_pH::Get_pH_Min() const{return ph_min;}

float Sensore_pH::Get_pH_Max() const{return ph_max;}

float Sensore_pH::Get_pH() const{return ph;}

std::string Sensore_pH::Get_Nome() const{return nome;}

std::string Sensore_pH::Get_Img_Path() const{return ":/Immagini/pH_Acqua.jpg";}

Sensore_pH* Sensore_pH::clone() const{return new Sensore_pH(*this);}

void Sensore_pH::Set_pH_Min(float ph0){((ph0<5.0 || ph0>=ph_max) ? ph_min=5.0 : ph_min=ph0);}

void Sensore_pH::Set_pH_Max(float ph0){((ph0<=ph_min || ph0>8.9) ? ph_max=8.9 : ph_max=ph0);}

void Sensore_pH::Set_pH(float p){((p<ph_min || p>ph_max) ? ph=(ph_max+ph_min)/2 : ph=p);}

void Sensore_pH::Accept(Sensor_Visitor* v) const{v->Visit(*this);}

std::string Sensore_pH::Info() const{
    if(GetWaterArea()=="OCEANO"){
        if(ph<7.8) return "Livello di ph dell'acqua dell'oceano non abbastanza basico.";
        if(ph>8.3) return "Livello di ph dell'acqua dell'oceano troppo basico.";
        return "Livello di ph dell'acqua dell'oceano nella norma(valore ~basico).";
    }
    if(GetWaterArea()=="MARE"){
        if(ph<7.8) return "Livello di ph dell'acqua del mare non abbastanza basico.";
        if(ph>8.4) return "Livello di ph dell'acqua del mare troppo basico.";
        return "Livello di ph dell'acqua del mare nella norma(valore ~basico).";
    }
    if(GetWaterArea()=="LAGO"){
        if(ph<6.0) return "Livello di ph dell'acqua del lago troppo acido.";
        if(ph>8.0) return "Livello di ph dell'acqua del lago troppo basico.";
        return "Livello di ph dell'acqua del lago nella norma(valore ~neutro).";
    }
    if(GetWaterArea()=="FIUME"){
        if(ph<7.0) return "Livello di ph dell'acqua del fiume troppo acido.";
        if(ph>=8.0) return "Livello di ph dell'acqua del fiume troppo basico.";
        return "Livello di ph dell'acqua del fiume nella norma(valore ~neutro).";
    }
    return "Dati non disponibili";
}

Sensore* Sensore_pH::FromJson(const QJsonObject& obj){
    return new Sensore_pH(
        obj.value("Nome").toString().toStdString(),
        obj.value("Zona").toString().toStdString(),
        obj.value("Min_pH").toInt(),
        obj.value("Max_pH").toInt(),
        obj.value("pH").toInt()
        );
}
