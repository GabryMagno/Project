#include"view_add_sensor.h"
#include<QIcon>
#include<QPixmap>
#include<QFont>
#include<QMessageBox>
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"

View_Add_Sensor::View_Add_Sensor(QWidget* p):QWidget(p){

    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setMinimumSize(600,200);
    this->setMaximumSize(650,250);
    this->setWindowTitle("Nuovo_Sensore");
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));

    info=new QLabel("Scegliere il tipo di sensore da aggiungere alla lista");
    QFont* font0=new QFont;
    font0->setUnderline(true);
    font0->setItalic(true);
    font0->setBold(true);
    info->setFont(*font0);
    info->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    profondità=new QRadioButton("Sensore_Profondità");
    inquinamento=new QRadioButton("Sensore_Inquinamento");
    temperatura=new QRadioButton("Sensore_Temperatura");
    ph=new QRadioButton("Sensore_pH");

    buttons=new QHBoxLayout;
    buttons->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    buttons->addWidget(profondità);
    buttons->addWidget(inquinamento);
    buttons->addWidget(temperatura);
    buttons->addWidget(ph);

    img=new QLabel();
    img->setPixmap(QPixmap(":/Immagini/Choice.png").scaled(80,80,Qt::AspectRatioMode::KeepAspectRatio));
    img->setAlignment(Qt::AlignCenter);

    accept=new QPushButton(QIcon(":/Immagini/Accept.jpg"),"Conferma");
    confirm=new QHBoxLayout;
    confirm->addWidget(accept);
    confirm->setAlignment(Qt::AlignCenter | Qt::AlignBottom);


    main=new QVBoxLayout;
    main->addWidget(info);
    main->addLayout(buttons);
    main->addWidget(img);
    main->addLayout(confirm);

    this->setLayout(main);

    connect(accept,SIGNAL(clicked()),this,SLOT(New()));
}

void View_Add_Sensor::New(){
    if(profondità->isChecked()==true || inquinamento->isChecked()==true || temperatura->isChecked()==true || ph->isChecked()==true){
        this->close();
        if(profondità->isChecked()==true){
            Sensore_Profondità* depth=new Sensore_Profondità;
            add_new=new View_Choice_Details_New_Sensor(depth);
            connect(add_new,SIGNAL(Add(Sensore*)),this,SIGNAL(New_Sensor(Sensore*)));
            add_new->show();
        }
        if(inquinamento->isChecked()==true){
            Sensore_Inquinamento* pollution=new Sensore_Inquinamento;
            add_new=new View_Choice_Details_New_Sensor(pollution);
            connect(add_new,SIGNAL(Add(Sensore*)),this,SIGNAL(New_Sensor(Sensore*)));
            add_new->show();
        }
        if(temperatura->isChecked()==true){
            Sensore_Temperatura* temp=new Sensore_Temperatura;
            add_new=new View_Choice_Details_New_Sensor(temp);
            connect(add_new,SIGNAL(Add(Sensore*)),this,SIGNAL(New_Sensor(Sensore*)));
            add_new->show();
        }
        if(ph->isChecked()==true){
            Sensore_pH* PH=new Sensore_pH;
            add_new=new View_Choice_Details_New_Sensor(PH);
            connect(add_new,SIGNAL(Add(Sensore*)),this,SIGNAL(New_Sensor(Sensore*)));
            add_new->show();
        }
    }else{
        QMessageBox::StandardButton scegliere;
        scegliere=QMessageBox::question(this,"Nuovo_Sensore",
                                          "Scegliere un tipo di sensore per continuare:",
                                          QMessageBox::Ok | QMessageBox::Close);
        if(scegliere==QMessageBox::Close) this->close();
    }
}
