#include"view_sensor_details.h"
#include"Sensore_Inquinamento.h"
#include"sensore_profondita.h"
#include"sensore_ph.h"
#include"sensore_temperatura.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPixmap>
#include<QString>
#include<QMessageBox>

QFrame* View_Sensor_Details::Separator(){
    QFrame* aux=new QFrame();
    aux->setFrameStyle(QFrame::Sunken | QFrame::HLine);
    return aux;
}

View_Sensor_Details::View_Sensore_Details(Sensore* snsr0,QWidget* p):snsr(snsr0),QWidget(p){

    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Dettagli_Sensore");
    this->setMinimumSize(QSize(600,400));
    this->setMaximumSize(QSize(700,600));
    this->setAttribute(Qt::WA_QuitOnClose,false);

    QVBoxLayout* info=new QVBoxLayout;

    QHBoxLayout* button=new QHBoxLayout;
    pass_to_modify=new QPushButton(QIcon(":/Immagini/Modifica.jpg"),"Modifica");
    button->addWidget(pass_to_modify);
    button->setAlignment(Qt::AlignRight | Qt::AlignTop);

    info->addLayout(button);

    name=new QLabel("NOME: "+QString::fromStdString(snsr->Get_Nome()));
    name->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    image=new QLabel();
    image->setPixmap(QPixmap(QString::fromStdString(snsr->Get_Img_Path())).scaled(110,110,Qt::AspectRatioMode::KeepAspectRatio));
    image->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    info->addWidget(image);

    QVBoxLayout* info_snsr=new QVBoxLayout;
    info_snsr->addWidget(name);

    if(dynamic_cast<Sensore_Profondità*>(snsr)){

        QLabel* type=new QLabel("TIPO: SENSORE_DI_PROFONDITA'");
        type->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString zona=QString::fromStdString((static_cast<Sensore_Profondità*>(snsr))->GetWaterArea());
        QLabel* zone=new QLabel("ZONA : "+zona);
        zone->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val=QString::number((static_cast<Sensore_Profondità*>(snsr))->Get_Profondità_Max());
        QLabel* max_depth=new QLabel("MAX  PROFONDITA'  REGISTABILE: "+val+" m");
        max_depth->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val1=QString::number((static_cast<Sensore_Profondità*>(snsr))->Get_Profondità());
        QLabel* depth=new QLabel("PROFONDITA'  REGISTRATA: "+val1+" m");
        depth->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString report=QString::fromStdString((static_cast<Sensore_Profondità*>(snsr))->Info());
        rapporto=new QLabel("RAPPORTO_SENSORE: "+report);
        rapporto->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        info_snsr->addWidget(Separator());
        info_snsr->addWidget(type);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(zone);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(max_depth);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(depth);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(rapporto);
    }
    if(dynamic_cast<Sensore_Inquinamento*>(snsr)){
        QLabel* type=new QLabel("TIPO: SENSORE_DI_INQUINAMENTO");
        type->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val1=QString::number((static_cast<Sensore_Inquinamento*>(snsr))->Get_PM_2_5());
        QLabel* pm2_5=new QLabel("QUANTITA'  PM_2,5  REGISTRATA: "+val1+" µg/m3");
        pm2_5->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val2=QString::number((static_cast<Sensore_Inquinamento*>(snsr))->Get_PM_10());
        QLabel* pm10=new QLabel("QUANTITA'  PM_10  REGISTRATA: "+val2+" µg/m3");
        pm10->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString report=QString::fromStdString((static_cast<Sensore_Inquinamento*>(snsr))->Info());
        rapporto=new QLabel("RAPPORTO_SENSORE: "+report);
        rapporto->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        info_snsr->addWidget(Separator());
        info_snsr->addWidget(type);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(pm2_5);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(pm10);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(rapporto);
    }
    if(dynamic_cast<Sensore_Temperatura*>(snsr)){

        QLabel* type=new QLabel("TIPO: SENSORE_DI_TEMPERATURA");
        type->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val_min0=QString::number((static_cast<Sensore_Temperatura*>(snsr))->Get_Temperatura_Min());
        QLabel* val_min=new QLabel("MIN  TEMPERATURA  REGISTABILE: "+val_min0+" °C");
        val_min->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val_max0=QString::number((static_cast<Sensore_Temperatura*>(snsr))->Get_Temperatura_Max());
        QLabel* val_max=new QLabel("MAX  TEMPERATURA  REGISTABILE: "+val_max0+" °C");
        val_max->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val0=QString::number((static_cast<Sensore_Temperatura*>(snsr))->Get_Temperatura());
        QLabel* val=new QLabel("TEMPERATURA  ATTUALMENTE  REGISTRATA: "+val0+" °C");
        val->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString report=QString::fromStdString((static_cast<Sensore_Temperatura*>(snsr))->Info());
        rapporto=new QLabel("RAPPORTO_SENSORE: "+report);
        rapporto->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        info_snsr->addWidget(Separator());
        info_snsr->addWidget(type);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val_min);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val_max);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(rapporto);

    }
    if(dynamic_cast<Sensore_pH*>(snsr)){


        QLabel* type=new QLabel("TIPO: SENSORE_PH");
        type->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString zona=QString::fromStdString((static_cast<Sensore_Profondità*>(snsr))->GetWaterArea());
        QLabel* zone=new QLabel("ZONA : "+zona);
        zone->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val_min0=QString::number((static_cast<Sensore_pH*>(snsr))->Get_pH_Min());
        QLabel* val_min=new QLabel("MIN  PH  REGISTABILE: "+val_min0);
        val_min->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val_max0=QString::number((static_cast<Sensore_pH*>(snsr))->Get_pH_Max());
        QLabel* val_max=new QLabel("MAX  PH  REGISTABILE: "+val_max0);
        val_max->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString val0=QString::number((static_cast<Sensore_pH*>(snsr))->Get_pH());
        QLabel* val=new QLabel("PH  ATTUALMENTE  REGISTRATO: "+val0);
        val->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QString report=QString::fromStdString((static_cast<Sensore_pH*>(snsr))->Info());
        rapporto=new QLabel("RAPPORTO_SENSORE: "+report);
        rapporto->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        info_snsr->addWidget(Separator());
        info_snsr->addWidget(type);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(zone);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val_min);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val_max);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(val);
        info_snsr->addWidget(Separator());
        info_snsr->addWidget(rapporto);

    }
    info->addLayout(info_snsr);
    this->setLayout(info);

    connect(pass_to_modify,SIGNAL(clicked()),this,SIGNAL(To_Modify()));
}
