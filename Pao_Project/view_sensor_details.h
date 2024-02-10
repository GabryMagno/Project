#ifndef VIEW_SENSOR_DETAILS_H
#define VIEW_SENSOR_DETAILS_H
#include<QWidget>
#include<QPushButton>
#include<QString>
#include<QLabel>
#include<string>
#include"sensore.h"

class View_Sensor_Details : public QWidget{
    Q_OBJECT
protected:
    Sensore* snsr;
    QLabel* image;
    QLabel* name;
    QPushButton* pass_to_modify;
public:
    View_Sensor_Details(Sensore* =nullptr,QWidget* =nullptr);
    virtual ~View_Sensor_Details() =default;
    virtual Sensore* Nuovo(const std::string,const std::string) const =0;
};

#endif // VIEW_SENSOR_DETAILS_H
