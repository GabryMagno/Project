#ifndef VIEW_CHANGE_SENSOR_DETAILS_H
#define VIEW_CHANGE_SENSOR_DETAILS_H
#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QRadioButton>
#include<QHBoxLayout>
#include<QFrame>
#include"sensore.h"

class View_Change_Sensor_Details : public QWidget{
    Q_OBJECT
private:
    Sensore* snsr;

    QLabel* immagine;
    QLabel* nome;
    QLabel* type;

    QPushButton* pass_to_details;
    QPushButton* accept;
    QPushButton* decline;

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

    QHBoxLayout* zona;
    QRadioButton* oceano;
    QRadioButton* mare;
    QRadioButton* lago;
    QRadioButton* fiume;

public:
    View_Change_Sensor_Details(Sensore* =nullptr,QWidget* =nullptr);
    QFrame* addSeparator();
public slots:
    void Confirms();
    void Decline();
signals:
    void To_Details();
    void Update();
};

#endif // VIEW_CHANGE_SENSOR_DETAILS_H
