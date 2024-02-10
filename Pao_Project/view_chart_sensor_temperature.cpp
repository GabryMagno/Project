#include"view_chart_sensor_temperature.h"
#include<QBarSeries>
#include<QBarSet>
#include<QRandomGenerator>
#include<QBarCategoryAxis>
#include<QLabel>
#include<QMessageBox>
#include<QFont>

View_Chart_Sensor_Temperature::View_Chart_Sensor_Temperature(Sensore_Temperatura* s):snsr(s) {
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Grafico_Sensore_Temperatura");
    this->setMinimumSize(700,900);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    main=new QVBoxLayout;
}

void View_Chart_Sensor_Temperature::Constructor(){
    while(main->count() != 0){ //cancello cosa c'è attualmente nel layout
        auto item = main->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete main;

    QBarSet* t_min=new QBarSet("Temperatura_Minima: ("+QString::number(snsr->Get_Temperatura_Min())+"°C)");
    QBarSet* t_max=new QBarSet("Temperatura_Massima: ("+QString::number(snsr->Get_Temperatura_Max())+"°C)");
    QBarSet* t=new QBarSet("Temperature_Registrate");

    int media=0;
    for(int i=0;i<7;i++){
        if(snsr->Get_Temperatura_Min()<0 && snsr->Get_Temperatura_Max()>0){
            *t_min<<-snsr->Get_Temperatura_Min();
            *t_max<<snsr->Get_Temperatura_Max()-snsr->Get_Temperatura_Min();
            if(snsr->Get_Temperatura()<=0){
                *t<<-snsr->Get_Temperatura()-(snsr->Get_Temperatura_Min());
            }else{
                *t<<snsr->Get_Temperatura()-(snsr->Get_Temperatura_Min());
            }
        }else if(snsr->Get_Temperatura_Min()>=0){
            if(snsr->Get_Temperatura_Min()==0){
                *t_min<<0.5;
            }else{
                *t_min<<snsr->Get_Temperatura_Min();
            }
            *t_max<<snsr->Get_Temperatura_Max();
            *t<<snsr->Get_Temperatura();
        }else if (snsr->Get_Temperatura_Max()<=0){
            *t_min<<-snsr->Get_Temperatura_Min();
            if(snsr->Get_Temperatura_Max()<0){
                *t_max<<-(snsr->Get_Temperatura_Max()+snsr->Get_Temperatura_Min());
            }else{
                *t_max<<-2*(snsr->Get_Temperatura_Min());
            }
            *t<<-(snsr->Get_Temperatura()+snsr->Get_Temperatura_Min());
        }
        media+=snsr->Get_Temperatura();
        snsr->Set_Temperatura(QRandomGenerator::global()->bounded(snsr->Get_Temperatura_Min(),snsr->Get_Temperatura_Max()));
    }

    QBarSeries* bar=new QBarSeries;
    bar->append(t_min);
    bar->append(t);
    bar->append(t_max);

    QStringList time;
    time<<"Lun"<<"Mar"<<"Mer"<<"Gio"<<"Ven"<<"Sab"<<"Dom";

    QBarCategoryAxis* axisX=new QBarCategoryAxis();
    axisX->append(time);

    chart=new QChart();
    chart->addSeries(bar);
    chart->setTitle("TEMPERATURE_SENSOR_CHART");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(2500);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeLight);

    view=new QChartView();
    view->setChart(chart);

    start=new QPushButton(QIcon(QPixmap(":/Immagini/New_Simulation.png")),"Nuova_Simulazione");
    choice1=new QRadioButton("Light");
    choice2=new QRadioButton("Blue_Celurean");
    choice3=new QRadioButton("Qt");
    choice4=new QRadioButton("Blue_Icy");
    QPushButton* accept=new QPushButton(QIcon(QPixmap(":/Immagini/Accept.jpg")),"Conferma");

    QHBoxLayout* buttons=new QHBoxLayout;
    buttons->addWidget(start);
    buttons->addWidget(choice1);
    buttons->addWidget(choice2);
    buttons->addWidget(choice3);
    buttons->addWidget(choice4);
    buttons->addWidget(accept);
    buttons->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    QFont* font=new QFont();
    font->setUnderline(true);
    font->setBold(true);

    QLabel* rapporto=new QLabel();
    snsr->Set_Temperatura(media/7);
    rapporto->setText("RAPPORTO_SENSORE: Il clima medio rilevato è "+QString::fromStdString(snsr->Info()).toLower()+"("+QString::number(snsr->Get_Temperatura())+"°C)");
    rapporto->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    rapporto->setFont(*font);

    main=new QVBoxLayout;
    main->addLayout(buttons);
    main->addWidget(rapporto);
    main->addWidget(view);

    connect(accept,SIGNAL(clicked()),this,SLOT(Update()));
    connect(start,SIGNAL(clicked()),this,SLOT(New_Simulation()));

    this->setLayout(main);
    this->show();
}

void View_Chart_Sensor_Temperature::Update(){
    if(choice1->isChecked()) chart->setTheme(QChart::ChartThemeLight);
    if(choice2->isChecked()) chart->setTheme(QChart::ChartThemeBlueCerulean);
    if(choice3->isChecked()) chart->setTheme(QChart::ChartThemeQt);
    if(choice4->isChecked()) chart->setTheme(QChart::ChartThemeBlueIcy);
}

void View_Chart_Sensor_Temperature::New_Simulation(){
    QMessageBox::StandardButton new_simulation;
    new_simulation=QMessageBox::question(this,"Nuova_Simulazione",
                                           "Sicuro di voler avviare una nuova simulazione ?",
                                           QMessageBox::Yes | QMessageBox::No);
    if(new_simulation==QMessageBox::Yes){
        Constructor();
    }

}
