#ifndef VIEW_CHART_SENSOR_POLLUTION_H
#define VIEW_CHART_SENSOR_POLLUTION_H
#include"view_chart_sensor.h"
#include"sensore_inquinamento.h"

class View_Chart_Sensor_Pollution : public View_Chart_Sensor{
    Q_OBJECT
private:
    Sensore_Inquinamento* snsr;
    QChart* second_chart;
    QChartView* second_view;
public:
    View_Chart_Sensor_Pollution(Sensore_Inquinamento*);
    void Constructor() override;
public slots:
    void Update() override;
    void New_Simulation() override;
};

#endif // VIEW_CHART_SENSOR_POLLUTION_H
