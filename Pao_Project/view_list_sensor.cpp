#include"view_list_sensor.h"
#include"sensore_profondita.h"
#include"sensore_inquinamento.h"
#include"sensore_temperatura.h"
#include"sensore_ph.h"
#include"view_sensor.h"
#include<QString>

void View_List_Sensor::Filter(unsigned int i){
    QFrame* divisore=new QFrame();
    divisore->setFrameShape(QFrame::HLine);

    Sensor_View* sensore=new Sensor_View(model->Get_Sensore(i),this,divisore);
    sensor=sensore;

    Box_List_Widget->addWidget(sensore);


    connect(sensore,SIGNAL(Delete(Sensore*)),this,SLOT(Delete_Sensor(Sensore*)));
    connect(sensore,SIGNAL(Changed()),this,SLOT(Modified()));

    list.push_back(sensore);
    Box_List_Widget->addWidget(divisore);

    if(i==model->Get_Numero_Sensori()-1) sensore->Set_Div(false);
}

View_List_Sensor::View_List_Sensor(Model *m, QWidget* p):QWidget(p),model(m){

    add=new View_Add_Sensor;

    searching_bar=new QLineEdit();
    searching_bar->setPlaceholderText("Cerca");
    searching_bar->setText("SNSR-");

    searched=new QPushButton(QIcon(":/Immagini/Cerca.png"),"");
    new_sensor=new QPushButton(QIcon(":/Immagini/Aggiungi.png"),"Aggiungi Sensore");

    QHBoxLayout* search_plus_add_sensor=new QHBoxLayout;
    search_plus_add_sensor->addWidget(searching_bar);
    search_plus_add_sensor->addWidget(searched);
    search_plus_add_sensor->addWidget(new_sensor);

    Box_List_Widget=new QVBoxLayout;
    for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
        Filter(i);
    }
    Box_List_Widget->addStretch(1);

    QWidget* ausiliario=new QWidget();
    ausiliario->setLayout(Box_List_Widget);

    scroll=new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setWidget(ausiliario);

    vista_ricerca_sensori=new QVBoxLayout;
    vista_ricerca_sensori->addLayout(search_plus_add_sensor);
    vista_ricerca_sensori->addWidget(scroll);

    this->setLayout(vista_ricerca_sensori);

    connect(new_sensor,SIGNAL(clicked()),this,SLOT(Add_Sensor_Widget()));
    connect(sensor,SIGNAL(Changed()),this,SLOT(Modified()));
    connect(searched,SIGNAL(clicked()),this,SLOT(Searched()));
    connect(add,SIGNAL(New_Sensor(Sensore*)),this,SLOT(Add_Sensor(Sensore*)));
    connect(add,SIGNAL(New_Sensor(Sensore*)),this,SIGNAL(Change()));
    connect(searching_bar,SIGNAL(returnPressed()),this,SLOT(Searched()));
}

void View_List_Sensor::Delete_Sensor(Sensore* snsr){
    model->Elimina_Sensore(snsr);
    emit Change();
}

void View_List_Sensor::Modified(){
    emit Change();
}

void View_List_Sensor::Ricerca(std::string s){
    while(Box_List_Widget->count() != 0){ //cancello cosa c'è attualmente nel layout
        auto item = Box_List_Widget->takeAt(0);
        delete item->widget();
        delete item;
    }

    if(s=="Sensore"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_Terrestre"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_Terrestre*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_Acquatico"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_Acquatico*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_Profondità"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_Profondità*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_Inquinamento"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_Inquinamento*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_Temperatura"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_Temperatura*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
    if(s=="Sensore_pH"){
        for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
            if(dynamic_cast<Sensore_pH*>(model->Get_Sensore(i))){
                Filter(i);
            }
        }
    }
}

void View_List_Sensor::Update_Filetrs(std::string s){
    list.clear();
    Ricerca(s);
}

void View_List_Sensor::Add_Sensor_Widget(){
    int i=0;
    if(i==0){
        add->show();
        i++;
    }
    add->activateWindow();
}

void View_List_Sensor::Searched(){
    list.clear();
    while(Box_List_Widget->count() != 0){
        auto item = Box_List_Widget->takeAt(0);
        delete item->widget();
        delete item;
    }

    QString s0=searching_bar->text().toUpper();
    for(unsigned int i=0;i<model->Get_Numero_Sensori();i++){
        QString s1=QString::fromStdString(model->Get_Sensore(i)->Get_Nome());
        if(s1.contains(s0)){
            Filter(i);
        }
    }
}

void View_List_Sensor::Add_Sensor(Sensore* snsr){
    model->Aggiungi_Sensore(snsr);
    list.clear();
    while(Box_List_Widget->count() != 0){
        auto item = Box_List_Widget->takeAt(0);
        delete item->widget();
        delete item;
    }
    Ricerca("Sensore");
    emit Change();
}
