#ifndef VIEW_CHART_SENSOR_DEPTH_H
#define VIEW_CHART_SENSOR_DEPTH_H
#include"view_chart_sensor.h"
#include"sensore_profondita.h"

class View_Chart_Sensor_Depth : public View_Chart_Sensor{
    Q_OBJECT
private:
    Sensore_Profondità* snsr;
public:
    View_Chart_Sensor_Depth(Sensore_Profondità*);
    void Constructor() override;
public slots:
    void Update() override;
    void New_Simulation() override;
};

#endif // VIEW_CHART_SENSOR_DEPTH_H
