#ifndef VIEW_CHART_SENSOR_H
#define VIEW_CHART_SENSOR_H
#include<QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QRadioButton>
#include<QtCharts/QChartView>

class View_Chart_Sensor : public QWidget{
    Q_OBJECT
protected:
    QPushButton* start;
    QVBoxLayout* main;

    QRadioButton* choice1;
    QRadioButton* choice2;
    QRadioButton* choice3;
    QRadioButton* choice4;

    QChart* chart;
    QChartView* view;
public:
    View_Chart_Sensor() =default;
    virtual void Constructor() =0;
public slots:
    virtual void Update() =0;
    virtual void New_Simulation() =0;
};

#endif // VIEW_CHART_SENSOR_H
