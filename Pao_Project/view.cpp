#include "view.h"
#include<QApplication>

View::View(Model* l, QWidget*):model(l)
{
    //MENU

    this->setWindowTitle("SENSORI");
    this->setGeometry(1000,1000,1000,1000);
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));

    QMenu* file=menuBar()->addMenu("&File");
    apri_file=new QAction(QIcon(":/Immagini/Apri.jpg"),"Apri File",file);
    salva=new QAction(QIcon(":/Immagini/Salva.jpg"),"Salva",file);
    salva_come=new QAction(QIcon(":/Immagini/Save_as.jpg"),"Salva_Come",file);
    chiudi=new QAction(QIcon(":/Immagini/Esci.png"),"Chiudi",file);
    file->addAction(apri_file);
    file->addAction(salva);
    file->addAction(salva_come);
    file->addAction(chiudi);
    QMenu* Sensori=menuBar()->addMenu("&Sensori");
    Aggiungi=new QAction(QIcon(":/Immagini/Aggiungi.png"),"Aggiungi Sensore",Sensori);
    Sensori->addAction(Aggiungi);

    //TOOLBAR

    tbar=addToolBar("&ToolBar");
    tbar->setMovable(false);
    tbar->addAction(apri_file);
    tbar->addSeparator();
    tbar->addAction(salva);
    tbar->addSeparator();
    tbar->addAction(salva_come);
    tbar->addSeparator();
    tbar->addAction(chiudi);
    tbar->addSeparator();
    tbar->addAction(Aggiungi);

    //PARTE PRINCIPALE
    not_saved=false;
    filters=new View_Filters(this);
    widget_list=new View_List_Sensor(model,this);
    widget_list->setContentsMargins(1,1,1,1);
    main=new QHBoxLayout;
    main->addWidget(filters);
    main->addWidget(widget_list);
    main_Widget=new QWidget;
    main_Widget->setLayout(main);
    this->setCentralWidget(main_Widget);
    connect(apri_file,SIGNAL(triggered()),this,SLOT(Load()));
    connect(salva,SIGNAL(triggered()),this,SLOT(Salva()));
    connect(salva_come,SIGNAL(triggered()),this,SLOT(Salva()));
    connect(chiudi,SIGNAL(triggered()),this,SLOT(close()));
    connect(filters,SIGNAL(Researching(std::string)),widget_list,SLOT(Update_Filetrs(std::string)));
    connect(Aggiungi,SIGNAL(triggered()),widget_list,SLOT(Add_Sensor_Widget()));
    connect(widget_list,SIGNAL(Change()),this,SLOT(Aggiorna()));
    this->setBackgroundRole(QPalette::Midlight);
}

void View::Load(){
    QString path="./../Project/Pao_Project/Salvataggi/";
    QString name=QFileDialog::getOpenFileName(this,tr("Load a JSON File"),path,"JSON files *.json");
    if(!name.isEmpty()){
        model=file->read(name);
    }
    View_List_Sensor* new_widget_list=widget_list;
    widget_list=new View_List_Sensor(model,this);
    widget_list->Ricerca("Sensore");
    main->addWidget(widget_list);
    this->setCentralWidget(main_Widget);
    connect(filters,SIGNAL(Researching(std::string)),widget_list,SLOT(Update_Filetrs(std::string)));
    connect(Aggiungi,SIGNAL(triggered()),widget_list,SLOT(Add_Sensor_Widget()));
    connect(widget_list,SIGNAL(Change()),this,SLOT(Aggiorna()));
    delete new_widget_list;
}

void View::Aggiorna(){
    not_saved=true;
}

void View::Salva(){
    QString path="./../Project/Pao_Project/Salvataggi/";
    QString name=QFileDialog::getSaveFileName(this,tr("Save on JSON File"),path,tr("JSON (*.json)"));
    if(!name.isEmpty()){
        file->write(model,name);
    }
}

void View::close(){
    if(not_saved==true){
        QMessageBox::StandardButton scegliere;
        scegliere=QMessageBox::question(this,"Modifiche_non_salvate",
                                          "Sicuro di voler uscire senza salvare le modifiche apportate?",
                                          QMessageBox::Yes | QMessageBox::No);
        if(scegliere==QMessageBox::Yes) QApplication::quit();
    }else QApplication::quit();
}
void View::closeEvent(QCloseEvent *event){
    close();
    event->ignore();
}
