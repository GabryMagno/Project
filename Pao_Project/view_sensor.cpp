#include"view_sensor.h"
#include"view_sensore_details.h"
#include"view_chart_sensor_depth.h"
#include"view_chart_sensor_pollution.h"
#include"view_chart_sensor_temperature.h"
#include"view_chart_sensor_ph.h"
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"
#include<QString>
#include<QIcon>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPixmap>
#include<QMessageBox>

View_Chart_Sensor* Sensor_View::Right_Sensor(Sensore* s){
    if(dynamic_cast<Sensore_Profondità*>(s))return new View_Chart_Sensor_Depth(dynamic_cast<Sensore_Profondità*>(s));
    if(dynamic_cast<Sensore_Inquinamento*>(s))return new View_Chart_Sensor_Pollution(dynamic_cast<Sensore_Inquinamento*>(s));
    if(dynamic_cast<Sensore_Temperatura*>(s))return new View_Chart_Sensor_Temperature(dynamic_cast<Sensore_Temperatura*>(s));
    if(dynamic_cast<Sensore_pH*>(s))return new View_Chart_Sensor_pH(dynamic_cast<Sensore_pH*>(s));
    return nullptr;
}

Sensor_View::Sensor_View(Sensore* sensore, QWidget* p,QFrame* d):
    snsr(sensore),parent(p),div(d)
{
    details=new View_Sensore_Details(snsr);
    modify_details=new View_Change_Sensor_Details(snsr);
    graphic=Right_Sensor(snsr);
    QLabel* immagine=new QLabel();
    immagine->setPixmap(QPixmap(QString::fromStdString(sensore->Get_Img_Path())).scaled(110,110,Qt::AspectRatioMode::KeepAspectRatio));
    immagine->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    immagine->resize(50,50);
    immagine->setMaximumWidth(200);

    nome=new QLabel(QString::fromStdString(sensore->Get_Nome()));
    nome->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QVBoxLayout* det=new QVBoxLayout;
    det->addWidget(nome);
    det->addWidget(immagine);
    det->addStretch(1);

    visita=new QPushButton(QIcon(QPixmap(":/Immagini/Visita.jpg")),"");
    modifica=new QPushButton(QIcon(QPixmap(":/Immagini/Modifica.jpg")),"");
    cancella=new QPushButton(QIcon(QPixmap(":/Immagini/Elimina.jpg")),"");
    grafico=new QPushButton(QIcon(QPixmap(":/Immagini/Grafico.jpg")),"Simulazione");
    QHBoxLayout* buttons=new QHBoxLayout;
    buttons->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    buttons->addWidget(visita);
    buttons->addWidget(modifica);
    buttons->addWidget(cancella);
    QVBoxLayout* all_buttons=new QVBoxLayout;
    all_buttons->addLayout(buttons);
    all_buttons->addWidget(grafico);
    all_buttons->setAlignment(Qt::AlignCenter | Qt::AlignRight);

    QHBoxLayout* main=new QHBoxLayout;
    main->addLayout(det);
    main->addLayout(all_buttons);

    this->setLayout(main);

    connect(visita,SIGNAL(clicked()),this,SLOT(View_Details()));
    connect(modifica,SIGNAL(clicked()),this,SLOT(Modify_Details()));
    connect(cancella,SIGNAL(clicked()),this,SLOT(Close()));
    connect(grafico,SIGNAL(clicked()),this,SLOT(Graphic()));
    connect(details,SIGNAL(To_Modify()),this,SLOT(Modify()));
    connect(modify_details,SIGNAL(To_Details()),this,SLOT(Details()));
    connect(modify_details,SIGNAL(Update()),this,SLOT(Recharge()));
}

Sensore* Sensor_View::Get_Sensore() const{return &(*snsr);}

QFrame* Sensor_View::Get_Div() const{return div;}

void Sensor_View::Set_Div(bool b){ b? div->show() : div->hide();}

void Sensor_View::mouseDoubleClickEvent(QMouseEvent* event){
    details->show();
    QWidget::mouseDoubleClickEvent(event);
}

void Sensor_View::View_Details(){
    int i=0;
    if(i==0){
        details->show();
        i++;
    }
    details->activateWindow();
}

void Sensor_View::Close(){
    QMessageBox::StandardButton choice;
    choice=QMessageBox::question(this,"Eliminazione_Sensore",
                                   "Confermi di voler eliminare il sensore: "+QString::fromStdString(snsr->Get_Nome())+" ?",
                                   QMessageBox::Yes | QMessageBox::No);
    if(choice==QMessageBox::Yes){
        emit Delete(snsr);
        delete div;
        details->close();
        modify_details->close();
        this->close();
    }
}

void Sensor_View::Modify_Details(){
    int i=0;
    if(i==0){
        modify_details->show();
        i++;
    }
    modify_details->activateWindow();
}

void Sensor_View::Modify(){
    QMessageBox::StandardButton choice;
    choice=QMessageBox::question(this,"Modifica",
                                   "Sicuro di voler modificare il sensore: "+QString::fromStdString(snsr->Get_Nome())+" ?",
                                   QMessageBox::Yes | QMessageBox::No);
    if(choice==QMessageBox::Yes){
        details->close();
        modify_details->show();
        modify_details->activateWindow();
    }
}

void Sensor_View::Details(){
    details->show();
    details->activateWindow();
}

void Sensor_View::Recharge(){
    delete details;
    details=new View_Sensore_Details(snsr);
    connect(details,SIGNAL(To_Modify()),this,SLOT(Modify()));
    details->show();
    emit Changed();
}
void Sensor_View::Graphic(){
    QMessageBox::StandardButton simulation;
    simulation=QMessageBox::question(this,"Nuova_Simulazione",
                                       "Sicuro di voler avviare una nuova simulazione ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if(simulation==QMessageBox::Yes){
        int i=0;
        if(i==0){
            i++;
            graphic->Constructor();
        }else graphic->show();
        graphic->activateWindow();
    }
}
