#include "visitor_json.h"

QJsonObject Visitor_Json::Get_Obj() const{
    return obj;
}

void Visitor_Json::Visit(const Sensore_Profondità& prf){
    QJsonObject profondità;
    profondità.insert("Tipo",QJsonValue::fromVariant("Sensore_Profondità"));
    profondità.insert("Nome",QJsonValue::fromVariant(QString::fromStdString(prf.Get_Nome())));
    profondità.insert("Image_Path",QJsonValue::fromVariant(QString::fromStdString(prf.Get_Img_Path())));
    profondità.insert("Zona",QJsonValue::fromVariant(QString::fromStdString(prf.GetWaterArea())));
    profondità.insert("Max_Profondità",QJsonValue::fromVariant(prf.Get_Profondità_Max()));
    profondità.insert("Profondità",QJsonValue::fromVariant(prf.Get_Profondità()));
    obj=profondità;
}

void Visitor_Json::Visit(const Sensore_Inquinamento& inq){
    QJsonObject inquinamento;
    inquinamento.insert("Tipo",QJsonValue::fromVariant("Sensore_Inquinamento"));
    inquinamento.insert("Nome",QJsonValue::fromVariant(QString::fromStdString(inq.Get_Nome())));
    inquinamento.insert("Image_Path",QJsonValue::fromVariant(QString::fromStdString(inq.Get_Img_Path())));
    inquinamento.insert("PM_2,5",QJsonValue::fromVariant(inq.Get_PM_2_5()));
    inquinamento.insert("PM_10",QJsonValue::fromVariant(inq.Get_PM_10()));
    obj=inquinamento;
}

void Visitor_Json::Visit(const Sensore_Temperatura& tmp){
    QJsonObject temperatura;
    temperatura.insert("Tipo",QJsonValue::fromVariant("Sensore_Temperatura"));
    temperatura.insert("Nome",QJsonValue::fromVariant(QString::fromStdString(tmp.Get_Nome())));
    temperatura.insert("Image_Path",QJsonValue::fromVariant(QString::fromStdString(tmp.Get_Img_Path())));
    temperatura.insert("Min_Temperatura",QJsonValue::fromVariant(tmp.Get_Temperatura_Min()));
    temperatura.insert("Max_Temperatura",QJsonValue::fromVariant(tmp.Get_Temperatura_Max()));
    temperatura.insert("Temperatura",QJsonValue::fromVariant(tmp.Get_Temperatura()));
    obj=temperatura;
}

void Visitor_Json::Visit(const Sensore_pH& ph){
    QJsonObject pH;
    pH.insert("Tipo",QJsonValue::fromVariant("Sensore_pH"));
    pH.insert("Nome",QJsonValue::fromVariant(QString::fromStdString(ph.Get_Nome())));
    pH.insert("Image_Path",QJsonValue::fromVariant(QString::fromStdString(ph.Get_Img_Path())));
    pH.insert("Zona",QJsonValue::fromVariant(QString::fromStdString(ph.GetWaterArea())));
    pH.insert("Min_pH",QJsonValue::fromVariant(ph.Get_pH_Min()));
    pH.insert("Max_pH",QJsonValue::fromVariant(ph.Get_pH_Max()));
    pH.insert("pH",QJsonValue::fromVariant(ph.Get_pH()));
    obj=pH;
}
