#ifndef VIEW_SENSORE_DETAILS_H
#define VIEW_SENSORE_DETAILS_H
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QFrame>
#include"sensore.h"

class View_Sensore_Details : public QWidget{
    Q_OBJECT
private:

    Sensore* snsr;
    QLabel* image;
    QLabel* name;
    QLabel* rapporto;
    QPushButton* pass_to_modify;

public:
    View_Sensore_Details(Sensore* =nullptr,QWidget* =nullptr);
    ~View_Sensore_Details() =default;
    void Imposta_Specifiche(Sensore*);
    QFrame* Separator();
signals:
    void To_Modify();
};

#endif // VIEW_SENSORE_DETAILS_H
