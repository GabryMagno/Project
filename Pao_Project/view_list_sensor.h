#ifndef VIEW_LIST_SENSOR_H
#define VIEW_LIST_SENSOR_H
#include"model.h"
#include"view_sensor.h"
#include"view_add_sensor.h"
#include<QLineEdit>
#include<QWidget>
#include<QPushButton>
#include<QScrollArea>
#include<QList>
#include<QVBoxLayout>

class View_List_Sensor : public QWidget{
    Q_OBJECT
private:
    Model* model;
    Sensor_View* sensor;
    QList<Sensor_View*> list;
    View_Add_Sensor* add;
    QLineEdit* searching_bar;
    QPushButton* searched;
    QPushButton* new_sensor;
    QScrollArea* scroll;
    QVBoxLayout* Box_List_Widget;
    QVBoxLayout* vista_ricerca_sensori;

public:
    View_List_Sensor(Model* =nullptr,QWidget* =nullptr);
    void Ricerca(std::string);
    void Filter(unsigned int);
public slots:
    void Update_Filetrs(std::string);
    void Delete_Sensor(Sensore*);
    void Searched();
    void Add_Sensor(Sensore*);
    void Add_Sensor_Widget();
    void Modified();
signals:
    void Elimina_Sensore(Sensore*);
    void Change();
};

#endif // VIEW_LIST_SENSOR_H
