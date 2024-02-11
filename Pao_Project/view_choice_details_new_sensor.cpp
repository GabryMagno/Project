#include "view_choice_details_new_sensor.h"
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"
#include<QIcon>
#include<QFormLayout>
#include<QMessageBox>

QHBoxLayout* View_Choice_Details_New_Sensor::Layout_Top(){

    QVBoxLayout* general_info=new QVBoxLayout;
    general_info->addWidget(nome);
    general_info->addWidget(type);
    general_info->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QHBoxLayout* top=new QHBoxLayout;
    top->addLayout(general_info);
    top->addWidget(immagine);
    top->setAlignment(Qt::AlignTop);

    return top;
}
View_Choice_Details_New_Sensor::View_Choice_Details_New_Sensor(Sensore* s, QWidget* p):QWidget(p),snsr(s) {
    if(s!=nullptr){

        this->setAttribute(Qt::WA_QuitOnClose,false);
        this->setWindowIcon(QIcon(":/Immagini/Aggiungi.png"));
        this->setWindowTitle("New_Sensor");
        this->setMinimumSize(550,300);

        nome=new QLabel("NOME :  "+QString::fromStdString(s->Get_Nome()));

        immagine=new QLabel;
        immagine->setPixmap(QPixmap(QString::fromStdString(s->Get_Img_Path())).scaled(100,100,Qt::KeepAspectRatio));
        immagine->setAlignment(Qt::AlignRight | Qt::AlignTop);

        accept=new QPushButton(QIcon(":/Immagini/Accept.jpg"),"Conferma");
        decline=new QPushButton(QIcon(":/Immagini/Decline.png"),"Annulla");

        if(dynamic_cast<Sensore_Profondità*>(snsr)){
            type=new QLabel("TIPO :  SENSORE_DI_PROFONDITA'");

            QHBoxLayout* top=Layout_Top();

            QLabel* zone=new QLabel("ZONA:");
            zone->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* max_depth=new QLabel("MAX  PROFONDITA'  REGISTABILE: ");
            max_depth->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* depth=new QLabel("PROFONDITA'  REGISTRATA: ");
            depth->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            oceano=new QRadioButton("OCEANO");
            mare=new QRadioButton("MARE");
            lago=new QRadioButton("LAGO");
            fiume=new QRadioButton("FIUME");

            zona=new QHBoxLayout;
            zona->addWidget(oceano);
            zona->addWidget(mare);
            zona->addWidget(lago);
            zona->addWidget(fiume);


            max_profondità=new QLineEdit;
            max_profondità->setPlaceholderText("Inserire un numero N: 1200 <= N <= 12000 ");

            profondità=new QLineEdit;
            profondità->setPlaceholderText("Inserire un numero N <= max profondità");

            QFormLayout* center=new QFormLayout;
            center->addRow(zone,zona);
            center->addRow(max_depth,max_profondità);
            center->addRow(depth,profondità);
            center->setAlignment(Qt::AlignCenter | Qt::AlignCenter);


            QHBoxLayout* buttons=new QHBoxLayout;
            buttons->addWidget(accept);
            buttons->addWidget(decline);
            buttons->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

            QVBoxLayout* final=new QVBoxLayout;
            final->addLayout(top);
            final->addLayout(center);
            final->addLayout(buttons);

            this->setLayout(final);

        }
        if(dynamic_cast<Sensore_Inquinamento*>(s)){

            type=new QLabel("TIPO :  SENSORE_INQUINAMENTO");

            QHBoxLayout* top=Layout_Top();

            QLabel* pm_2_5=new QLabel("QUANTITA' PM_2,5 REGISTATA: ");
            pm_2_5->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* pm_10=new QLabel("QUANTITA' PM_10 REGISTATA: ");
            pm_10->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            PM2_5=new QLineEdit;
            PM2_5->setPlaceholderText("Inserire un valore");

            PM_10=new QLineEdit;
            PM_10->setPlaceholderText("Inserire un numero valore");

            QFormLayout* center=new QFormLayout;
            center->addRow(pm_2_5,PM2_5);
            center->addRow(pm_10,PM_10);
            center->setAlignment(Qt::AlignCenter | Qt::AlignCenter);


            QHBoxLayout* buttons=new QHBoxLayout;
            buttons->addWidget(accept);
            buttons->addWidget(decline);
            buttons->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

            QVBoxLayout* final=new QVBoxLayout;
            final->addLayout(top);
            final->addLayout(center);
            final->addLayout(buttons);

            this->setLayout(final);

        }
        if(dynamic_cast<Sensore_Temperatura*>(s)){

            type=new QLabel("TIPO :  SENSORE_DI_TEMPERATURA");

            QHBoxLayout* top=Layout_Top();

            QLabel* min_temp=new QLabel("MIN  TEMPERATURA  REGISTRABILE:");
            min_temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* max_temp=new QLabel("MAX  TEMPERATURA REGISTABILE: ");
            max_temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* temp=new QLabel("TEMPERATURA  REGISTRATA: ");
            temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            min_temperatura=new QLineEdit;
            min_temperatura->setPlaceholderText("Inserire un numero N : -30°C<=N<=60°C");

            max_temperatura=new QLineEdit;
            max_temperatura->setPlaceholderText("Inserire un numero N : MIN_TEMPERATURA<N<=60°C");

            temperatura=new QLineEdit;
            temperatura->setPlaceholderText("Inserire un numero N : MIN_TEMPERATURA<N<=MAX_TEMPERATURA");

            QFormLayout* center=new QFormLayout;
            center->addRow(min_temp,min_temperatura);
            center->addRow(max_temp,max_temperatura);
            center->addRow(temp,temperatura);
            center->setAlignment(Qt::AlignCenter | Qt::AlignCenter);


            QHBoxLayout* buttons=new QHBoxLayout;
            buttons->addWidget(accept);
            buttons->addWidget(decline);
            buttons->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

            QVBoxLayout* final=new QVBoxLayout;
            final->addLayout(top);
            final->addLayout(center);
            final->addLayout(buttons);

            this->setLayout(final);

        }
        if(dynamic_cast<Sensore_pH*>(s)){

            type=new QLabel("TIPO :  SENSORE_PH");

            QHBoxLayout* top=Layout_Top();

            QLabel* zone=new QLabel("ZONA:");
            zone->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* min_ph=new QLabel("MIN  PH  REGISTRABILE:");
            min_ph->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* max_ph=new QLabel("MAX  PH REGISTABILE: ");
            max_ph->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            QLabel* ph=new QLabel("PH  REGISTRATO: ");
            ph->setAlignment(Qt::AlignCenter | Qt::AlignTop);

            oceano=new QRadioButton("OCEANO");
            mare=new QRadioButton("MARE");
            lago=new QRadioButton("LAGO");
            fiume=new QRadioButton("FIUME");

            zona=new QHBoxLayout;
            zona->addWidget(oceano);
            zona->addWidget(mare);
            zona->addWidget(lago);
            zona->addWidget(fiume);

            min_pH=new QLineEdit;
            min_pH->setPlaceholderText("Inserire un numero N : 5.0<=N<8.9");

            max_pH=new QLineEdit;
            max_pH->setPlaceholderText("Inserire un numero N : MIN_PH<N<=8.9");

            pH=new QLineEdit;
            pH->setPlaceholderText("Inserire un numero N : MIN_PH<=N<=MAX_PH");

            QFormLayout* center=new QFormLayout;
            center->addRow(zone,zona);
            center->addRow(min_ph,min_pH);
            center->addRow(max_ph,max_pH);
            center->addRow(ph,pH);
            center->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

            QHBoxLayout* buttons=new QHBoxLayout;
            buttons->addWidget(accept);
            buttons->addWidget(decline);
            buttons->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

            QVBoxLayout* final=new QVBoxLayout;
            final->addLayout(top);
            final->addLayout(center);
            final->addLayout(buttons);

            this->setLayout(final);


        }
        connect(accept,SIGNAL(clicked()),this,SLOT(Add_New()));
        connect(decline,SIGNAL(clicked()),this,SLOT(No_Add()));
    }else this->close();
}

void View_Choice_Details_New_Sensor::Add_New(){
    QMessageBox::StandardButton new_sensor_added;
    new_sensor_added=QMessageBox::question(this,"Nuovo_Sensore",
                                             "Confermi di voler aggiungere il sensore:"+QString::fromStdString(snsr->Get_Nome())+"?",
                                             QMessageBox::Yes | QMessageBox::No);

    if(new_sensor_added==QMessageBox::Yes){

        if(dynamic_cast<Sensore_Profondità*>(snsr)){

            if(oceano->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("OCEANO");
            if(mare->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("MARE");
            if(lago->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("LAGO");
            if(fiume->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("FIUME");

            static_cast<Sensore_Profondità*>(snsr)->Set_Profondità_Max(QString(max_profondità->text()).toInt());
            static_cast<Sensore_Profondità*>(snsr)->Set_Profondità(QString(profondità->text()).toInt());

        }
        if(dynamic_cast<Sensore_Inquinamento*>(snsr)){

            static_cast<Sensore_Inquinamento*>(snsr)->Set_PM_2_5(QString(PM2_5->text()).toUInt());
            static_cast<Sensore_Inquinamento*>(snsr)->Set_PM_10(QString(PM_10->text()).toUInt());

        }
        if(dynamic_cast<Sensore_Temperatura*>(snsr)){

            static_cast<Sensore_Temperatura*>(snsr)->Set_Temperatura_Min(QString(min_temperatura->text()).toInt());
            static_cast<Sensore_Temperatura*>(snsr)->Set_Temperatura_Max(QString(max_temperatura->text()).toInt());
            static_cast<Sensore_Temperatura*>(snsr)->Set_Temperatura(QString(temperatura->text()).toInt());

        }
        if(dynamic_cast<Sensore_pH*>(snsr)){

            if(oceano->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("OCEANO");
            if(mare->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("MARE");
            if(lago->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("LAGO");
            if(fiume->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("FIUME");

            static_cast<Sensore_pH*>(snsr)->Set_pH_Min(min_pH->text().toFloat());
            static_cast<Sensore_pH*>(snsr)->Set_pH_Max(max_pH->text().toFloat());
            static_cast<Sensore_pH*>(snsr)->Set_pH(pH->text().toFloat());

        }
        emit Add(snsr);
        this->close();
    }
}

void View_Choice_Details_New_Sensor::No_Add(){
    if(dynamic_cast<Sensore_Profondità*>(snsr)){

        oceano->setChecked(true);
        max_profondità->setText("");
        profondità->setText("");

    }
    if(dynamic_cast<Sensore_Inquinamento*>(snsr)){

        PM2_5->setText("");
        PM_10->setText("");

    }
    if(dynamic_cast<Sensore_Temperatura*>(snsr)){

        min_temperatura->setText("");
        max_temperatura->setText("");
        temperatura->setText("");

    }
    if(dynamic_cast<Sensore_pH*>(snsr)){

        oceano->setChecked(true);
        min_pH->setText("");
        max_pH->setText("");
        pH->setText("");
    }
}
