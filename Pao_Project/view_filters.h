#ifndef VIEW_FILTERS_H
#define VIEW_FILTERS_H
#include<QWidget>
#include<QRadioButton>
#include<QVBoxLayout>
#include<QComboBox>

class View_Filters : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* Type_search;
    QComboBox* search;
    QRadioButton* search_all_sensors;
    QRadioButton* search_water_sensors;
    QRadioButton* search_terrestrial_sensors;
    QRadioButton* search_Snsr_Temp;
    QRadioButton* search_Snsr_Depth;
    QRadioButton* search_Snsr_pH;
    QRadioButton* search_Snsr_pm;
public:
    View_Filters(QWidget* =nullptr);
public slots:
    void Annulla_Filtri();
    void Search_With_Filters();
signals:
    void Researching(std::string);
};

#endif // VIEW_FILTERS_H
