#ifndef VIEW_ADD_SENSOR_H
#define VIEW_ADD_SENSOR_H
#include<QWidget>
#include<QRadioButton>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include"view_choice_details_new_sensor.h"

class View_Add_Sensor : public QWidget{
    Q_OBJECT
private:
    View_Choice_Details_New_Sensor* add_new;
    QVBoxLayout* main;
    QHBoxLayout* buttons;
    QHBoxLayout* confirm;
    QLabel* info;
    QRadioButton* profondità;
    QRadioButton* inquinamento;
    QRadioButton* temperatura;
    QRadioButton* ph;
    QLabel* img;
    QPushButton* accept;

public:
    View_Add_Sensor(QWidget* =nullptr);
public slots:
    void New();
signals:
    void New_Sensor(Sensore*);
};

#endif // VIEW_ADD_SENSOR_H
