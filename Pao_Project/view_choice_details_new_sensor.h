#ifndef VIEW_CHOICE_DETAILS_NEW_SENSOR_H
#define VIEW_CHOICE_DETAILS_NEW_SENSOR_H
#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QRadioButton>
#include<QHBoxLayout>
#include<QFrame>
#include"sensore.h"

class View_Choice_Details_New_Sensor : public QWidget{
    Q_OBJECT
private:
    Sensore* snsr;

    QLabel* immagine;
    QLabel* nome;
    QLabel* type;

    QPushButton* accept;
    QPushButton* decline;

    QHBoxLayout* zona;
    QRadioButton* oceano;
    QRadioButton* mare;
    QRadioButton* lago;
    QRadioButton* fiume;

    QLineEdit* max_profondità;
    QLineEdit* profondità;

    QLineEdit* PM2_5;
    QLineEdit* PM_10;

    QLineEdit* min_temperatura;
    QLineEdit* max_temperatura;
    QLineEdit* temperatura;

    QLineEdit* min_pH;
    QLineEdit* max_pH;
    QLineEdit* pH;

public:
    View_Choice_Details_New_Sensor(Sensore* =nullptr, QWidget* =nullptr);
    QHBoxLayout* Layout_Top();
public slots:
    void Add_New();
    void No_Add();
signals:
    void Add(Sensore*);
};

#endif // VIEW_CHOICE_DETAILS_NEW_SENSOR_H
