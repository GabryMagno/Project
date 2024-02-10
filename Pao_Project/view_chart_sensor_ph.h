#ifndef VIEW_CHART_SENSOR_PH_H
#define VIEW_CHART_SENSOR_PH_H
#include"view_chart_sensor.h"
#include"sensore_ph.h"

class View_Chart_Sensor_pH : public View_Chart_Sensor{
    Q_OBJECT
private:
    Sensore_pH* snsr;
public:
    View_Chart_Sensor_pH(Sensore_pH*);
    void Constructor() override;
public slots:
    void Update() override;
    void New_Simulation() override;
};

#endif // VIEW_CHART_SENSOR_PH_H
