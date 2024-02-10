#ifndef JSON_FILE_H
#define JSON_FILE_H

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include "model.h"

class Json_File{
private:
    std::string path;
    Model* model;
public:
    explicit Json_File() =delete;
    explicit Json_File(const Json_File&) =delete;
    Json_File&  write(Model*,QString);
    Model* read(const QString&);
};

#endif // JSON_FILE_H
