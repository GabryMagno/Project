#ifndef VIEW_SENSOR_H
#define VIEW_SENSOR_H
#include<QLabel>
#include<QPushButton>
#include<QFrame>
#include"sensore.h"
#include"view_sensore_details.h"
#include"view_change_sensor_details.h"
#include"view_chart_sensor.h"

class Sensor_View : public QWidget{
    Q_OBJECT
private:
    View_Sensore_Details* details;
    View_Change_Sensor_Details* modify_details;
    View_Chart_Sensor* graphic;

    QWidget* parent;
    QFrame* div;

    QLabel* nome;
    QPushButton* visita;
    QPushButton* modifica;
    QPushButton* cancella;
    QPushButton* grafico;

public:
    Sensore* snsr;
    Sensor_View() =default;
    Sensor_View(Sensore* ,QWidget* =nullptr,QFrame* =nullptr);
    Sensore* Get_Sensore() const;
    QFrame* Get_Div() const;
    View_Chart_Sensor* Right_Sensor(Sensore*);
    void Set_Div(bool);
    void mouseDoubleClickEvent(QMouseEvent *event) override;
public slots:
    void View_Details();
    void Modify_Details();
    void Close();
    void Modify();
    void Details();
    void Recharge();
    void Graphic();
signals:
    void Conferma();
    void Delete(Sensore*);
    void Changed();
};

#endif // VIEW_SENSOR_H
