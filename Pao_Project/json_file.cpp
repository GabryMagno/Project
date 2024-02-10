#include "json_file.h"
#include"visitor_json.h"
#include<QJsonArray>
#include<QByteArray>
#include"sensore.h"

Json_File& Json_File::write(Model* model,QString name){
    QJsonArray sensors;
    for (int i=0;i<model->Get_Numero_Sensori();i++){
        Visitor_Json visitor;
        (model->Get_Sensore(i))->Accept(&visitor);
        sensors.push_back(visitor.Get_Obj());
    }
    QJsonDocument doc(sensors);
    QFile json_file(name);
    json_file.open(QFile::WriteOnly);
    json_file.write(doc.toJson());
    json_file.close();
    return *this;
}

Model* Json_File::read(const QString& path){
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray json_items = document.array();
    Model* m=new Model();
    for(const QJsonValue& record : json_items){
        QJsonObject json_object=record.toObject();
        QJsonValue tipo =json_object.value("Tipo");
        Sensore* snsr;
        if(tipo.toString().compare("Sensore_pH")==0) snsr=new Sensore_pH;
        else if(tipo.toString().compare("Sensore_Inquinamento")==0) snsr=new Sensore_Inquinamento;
        else if(tipo.toString().compare("Sensore_Temperatura")==0) snsr=new Sensore_Temperatura;
        else snsr=new Sensore_Profondità;
        m->Aggiungi_Sensore(snsr->FromJson(json_object));
    }
    return m;
}
