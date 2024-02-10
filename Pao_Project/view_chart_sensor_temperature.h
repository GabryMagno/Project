#ifndef VIEW_CHART_SENSOR_TEMPERATURE_H
#define VIEW_CHART_SENSOR_TEMPERATURE_H
#include"view_chart_sensor.h"
#include"sensore_temperatura.h"

class View_Chart_Sensor_Temperature : public View_Chart_Sensor{
    Q_OBJECT
private:
    Sensore_Temperatura* snsr;
public:
    View_Chart_Sensor_Temperature(Sensore_Temperatura*);
    void Constructor() override;
public slots:
    void Update() override;
    void New_Simulation() override;
};

#endif // VIEW_CHART_SENSOR_TEMPERATURE_H
