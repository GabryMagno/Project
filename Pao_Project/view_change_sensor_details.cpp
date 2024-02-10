#include"view_change_sensor_details.h"
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"
#include<QString>
#include<QPixmap>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFormLayout>

QFrame* View_Change_Sensor_Details::addSeparator(){
    QFrame* div=new QFrame;
    div->setFrameStyle(QFrame::Sunken | QFrame::HLine);
    return div;
}

View_Change_Sensor_Details::View_Change_Sensor_Details(Sensore * sensore, QWidget * p):QWidget(p),snsr(sensore){

    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Modifiche_Dettagli_Sensore");
    this->setMaximumSize(700,600);
    this->setMinimumSize(500,400);
    this->setAttribute(Qt::WA_QuitOnClose,false);

    pass_to_details=new QPushButton(QIcon(":/Immagini/Visita.jpg"),"Dettagli_Sensore");
    QVBoxLayout* button=new QVBoxLayout;
    button->addWidget(pass_to_details);
    button->setAlignment(Qt::AlignRight| Qt::AlignTop);

    nome=new QLabel("NOME:  "+QString::fromStdString(snsr->Get_Nome()));
    nome->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    immagine=new QLabel();
    immagine->setPixmap(QPixmap(QString::fromStdString(snsr->Get_Img_Path())).scaled(110,110,Qt::AspectRatioMode::KeepAspectRatio));
    immagine->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QFormLayout* modifiche=new QFormLayout;

    if(dynamic_cast<Sensore_Profondità*>(snsr)){

        type=new QLabel("TIPO:  SENSORE_DI_PROFONDITA'");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);

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

        modifiche->addRow(zone->text(),zona);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(max_depth->text(),max_profondità);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(depth->text(),profondità);

    }
    if(dynamic_cast<Sensore_Inquinamento*>(snsr)){

        type=new QLabel("TIPO:  SENSORE_INQUINAMENTO'");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QLabel* pm_2_5=new QLabel("QUANTITA' PM_2,5 REGISTATA: ");
        pm_2_5->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* pm_10=new QLabel("QUANTITA' PM_10 REGISTATA: ");
        pm_10->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        PM2_5=new QLineEdit;
        PM2_5->setPlaceholderText("Inserire un valore");

        PM_10=new QLineEdit;
        PM_10->setPlaceholderText("Inserire un numero valore");

        modifiche->addWidget(addSeparator());
        modifiche->addRow(pm_2_5->text(),PM2_5);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(pm_10->text(),PM_10);

    }
    if(dynamic_cast<Sensore_Temperatura*>(snsr)){

        this->setMinimumSize(600,500);

        type=new QLabel("TIPO:  SENSORE_TEMPERATURA'");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QLabel* min_temp=new QLabel("MIN  TEMPERATURA  REGISTRABILE:");
        min_temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* max_temp=new QLabel("MAX  TEMPERATURA REGISTABILE: ");
        max_temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        QLabel* temp=new QLabel("TEMPERATURA  REGISTRATA: ");
        temp->setAlignment(Qt::AlignCenter | Qt::AlignTop);

        min_temperatura=new QLineEdit;
        min_temperatura->setPlaceholderText("Inserire un numero N : -30°C<=N<60°C");

        max_temperatura=new QLineEdit;
        max_temperatura->setPlaceholderText("Inserire un numero N : MIN_TEMPERATURA<N<=60°C");

        temperatura=new QLineEdit;
        temperatura->setPlaceholderText("Inserire un numero N : MIN_TEMPERATURA<N<=MAX_TEMPERATURA");

        modifiche->addRow(min_temp->text(),min_temperatura);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(max_temp->text(),max_temperatura);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(temp->text(),temperatura);

    }
    if(dynamic_cast<Sensore_pH*>(snsr)){

        type=new QLabel("TIPO:  SENSORE_PH'");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);

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

        modifiche->addRow(zone->text(),zona);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(min_ph->text(),min_pH);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(max_ph->text(),max_pH);
        modifiche->addWidget(addSeparator());
        modifiche->addRow(ph->text(),pH);

    }
    QVBoxLayout* details=new QVBoxLayout;
    details->addWidget(nome);
    details->addWidget(type);
    QHBoxLayout* top=new QHBoxLayout;
    top->addLayout(details);
    top->addLayout(button);
    top->setAlignment(Qt::AlignTop);
    QVBoxLayout* first=new QVBoxLayout;
    first->addLayout(top);
    first->addWidget(immagine);

    accept=new QPushButton(QIcon(":/Immagini/Accept.jpg"),"Conferma_Modifiche");
    decline=new QPushButton(QIcon(":/Immagini/Decline.png"),"Annulla_Modifiche");

    QHBoxLayout* buttons=new QHBoxLayout;
    buttons->addWidget(accept);
    buttons->addWidget(decline);

    QVBoxLayout* final=new QVBoxLayout;
    final->addLayout(first);
    final->addLayout(modifiche);
    final->addLayout(buttons);
    this->setLayout(final);

    connect(pass_to_details,SIGNAL(clicked()),this,SIGNAL(To_Details()));
    connect(accept,SIGNAL(clicked()),this,SLOT(Confirms()));
    connect(decline,SIGNAL(clicked()),this,SLOT(Decline()));
}

void View_Change_Sensor_Details::Confirms(){
    if(dynamic_cast<Sensore_Profondità*>(snsr)){
        if(oceano->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("OCEANO");
        if(mare->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("MARE");
        if(lago->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("LAGO");
        if(fiume->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("FIUME");
        if(max_profondità->text()!=""){
            QString max_prof=max_profondità->text();
            unsigned int max=max_prof.split(" ")[0].toInt();
            (static_cast<Sensore_Profondità*>(snsr))->Set_Profondità_Max(max);
        }
        if(profondità->text()!=""){
            QString prof=profondità->text();
            unsigned int depth=prof.split(" ")[0].toInt();
            (static_cast<Sensore_Profondità*>(snsr))->Set_Profondità(depth);
        }
        emit Update();
    }
    if(dynamic_cast<Sensore_Inquinamento*>(snsr)){
        if(PM2_5->text()!="){"){
            QString pm2_5=PM2_5->text();
            unsigned int max=pm2_5.split(" ")[0].toInt();
            (static_cast<Sensore_Inquinamento*>(snsr))->Set_PM_2_5(max);
        }
        if(PM_10->text()!=""){
            QString pm_10=PM_10->text();
            unsigned int depth=pm_10.split(" ")[0].toInt();
            (static_cast<Sensore_Inquinamento*>(snsr))->Set_PM_10(depth);
        }
        emit Update();
    }
    if(dynamic_cast<Sensore_Temperatura*>(snsr)){
        if(min_temperatura->text()!=""){
            QString min_temp=min_temperatura->text();
            int min=min_temp.split(" ")[0].toInt();
            (static_cast<Sensore_Temperatura*>(snsr))->Set_Temperatura_Min(min);
        }
        if(max_temperatura->text()!=""){
            QString max_temp=max_temperatura->text();
            int max=max_temp.split(" ")[0].toInt();
            (static_cast<Sensore_Temperatura*>(snsr))->Set_Temperatura_Max(max);
        }
        if(temperatura->text()!=""){
            QString temp=temperatura->text();
            int depth=temp.split(" ")[0].toInt();
            (static_cast<Sensore_Temperatura*>(snsr))->Set_Temperatura(depth);
        }
        emit Update();
    }
    if(dynamic_cast<Sensore_pH*>(snsr)){
        if(oceano->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("OCEANO");
        if(mare->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("MARE");
        if(lago->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("LAGO");
        if(fiume->isChecked())(static_cast<Sensore_Acquatico*>(snsr))->SetWaterArea("FIUME");
        if(min_pH->text()!=""){
            QString phmin=min_pH->text();
            unsigned int p0=phmin.split(" ")[0].toInt();
            (static_cast<Sensore_pH*>(snsr))->Set_pH_Min(p0);
        }
        if(max_pH->text()!=""){
            QString phmax=max_pH->text();
            unsigned int p1=phmax.split(" ")[0].toInt();
            (static_cast<Sensore_pH*>(snsr))->Set_pH_Max(p1);
        }
        if(pH->text()!=""){
            QString ph=pH->text();
            unsigned int p2=ph.split(" ")[0].toInt();
            (static_cast<Sensore_pH*>(snsr))->Set_pH_Min(p2);
        }
        emit Update();
    }
    this->close();
}

void View_Change_Sensor_Details::Decline(){

    if(dynamic_cast<Sensore_Profondità*>(snsr)){
        std::string s=static_cast<Sensore_Acquatico*>(snsr)->GetWaterArea();
        if(s=="OCEANO") oceano->setChecked(true);
        if(s=="MARE") mare->setChecked(true);
        if(s=="LAGO") lago->setChecked(true);
        if(s=="FIUME") fiume->setChecked(true);
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
        std::string s=static_cast<Sensore_Acquatico*>(snsr)->GetWaterArea();
        if(s=="OCEANO") oceano->setChecked(true);
        if(s=="MARE") mare->setChecked(true);
        if(s=="LAGO") lago->setChecked(true);
        if(s=="FIUME") fiume->setChecked(true);
        min_pH->setText("");
        max_pH->setText("");
        pH->setText("");
    }
}
