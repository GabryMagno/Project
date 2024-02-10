#include "view_chart_sensor_pollution.h"
#include<QLabel>
#include<QMessageBox>
#include<QLineSeries>
#include<QRandomGenerator>
#include<QAreaSeries>
#include<QBarCategoryAxis>
#include<QFont>

View_Chart_Sensor_Pollution::View_Chart_Sensor_Pollution(Sensore_Inquinamento* s):snsr(s) {
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Grafico_Sensore_Inquinamento");
    this->setMinimumSize(1200,700);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    main=new QVBoxLayout;
}

void View_Chart_Sensor_Pollution::Constructor(){
    while(main->count() != 0){
        auto item = main->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete main;
    choice1=new QRadioButton;
    choice1->setText("High_Contrast");

    choice2=new QRadioButton;
    choice2->setText("Blue_Cerulean");

    choice3=new QRadioButton;
    choice3->setText("Qt");

    choice4=new QRadioButton;
    choice4->setText("Dark");

    QPushButton* accept=new QPushButton(QIcon(QPixmap(":/Immagini/Accept.jpg")),"Conferma");
    start=new QPushButton(QIcon(QPixmap(":/Immagini/New_Simulation.png")),"Nuova_Simulazione");

    QLineSeries* pm10=new QLineSeries();
    pm10->setName("Livelli PM_10 Registrati");
    QLineSeries* pm2_5=new QLineSeries();
    pm2_5->setName("Livelli PM_2,5 Registrati");
    QLineSeries* origin=new QLineSeries();

    for(int i=0;i<29;i++){
        pm10->append(QPointF(i,snsr->Get_PM_10()));
        pm2_5->append(QPointF(i,snsr->Get_PM_2_5()));
        origin->append(i,0);
        snsr->Set_PM_10(QRandomGenerator::global()->bounded(0,75));
        snsr->Set_PM_2_5(QRandomGenerator::global()->bounded(0,55));
    }

    QAreaSeries* area1=new QAreaSeries(pm10,origin);
    area1->setName("PM_10(in 28 giorni)");
    QAreaSeries* area2=new QAreaSeries(pm2_5,origin);
    area2->setName("PM_2,5(in 28 giorni)");

    chart=new QChart();
    chart->addSeries(area1);
    chart->createDefaultAxes();
    chart->setTitle("POLLUTION(PM_10)_SENSOR_CHART");
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    second_chart=new QChart();
    second_chart->addSeries(area2);
    second_chart->createDefaultAxes();
    second_chart->setTitle("POLLUTION(PM_2,5)_SENSOR_CHART");
    second_chart->setTheme(QChart::ChartThemeDark);
    second_chart->setAnimationOptions(QChart::SeriesAnimations);

    view=new QChartView();
    view->setRenderHints(QPainter::Antialiasing);
    view->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    view->setChart(chart);

    second_view=new QChartView();
    second_view->setRenderHints(QPainter::Antialiasing);
    second_view->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    second_view->setChart(second_chart);

    QFont* font=new QFont();
    font->setUnderline(true);
    font->setBold(true);

    QLabel* rapporto=new QLabel();
    rapporto->setText("RAPPORTO_SENSORE : Mediamente "+QString::fromStdString(snsr->Info()).toLower());
    rapporto->setFont(*font);
    rapporto->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    QVBoxLayout* charts=new QVBoxLayout;
    charts->addWidget(view);
    charts->addWidget(second_view);

    QHBoxLayout* buttons=new QHBoxLayout;
    buttons->addWidget(start);
    buttons->addWidget(choice1);
    buttons->addWidget(choice2);
    buttons->addWidget(choice3);
    buttons->addWidget(choice4);
    buttons->addWidget(accept);
    buttons->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    main=new QVBoxLayout;
    main->addLayout(buttons);
    main->addWidget(rapporto);
    main->addLayout(charts);

    connect(accept,SIGNAL(clicked()),this,SLOT(Update()));
    connect(start,SIGNAL(clicked()),this,SLOT(New_Simulation()));

    this->setLayout(main);
    this->show();
}

void View_Chart_Sensor_Pollution::Update(){
    if(choice1->isChecked()){
        chart->setTheme(QChart::ChartThemeHighContrast);
        second_chart->setTheme(QChart::ChartThemeHighContrast);
    }
    if(choice2->isChecked()){
        chart->setTheme(QChart::ChartThemeBlueCerulean);
        second_chart->setTheme(QChart::ChartThemeBlueCerulean);
    }
    if(choice3->isChecked()) {
        chart->setTheme(QChart::ChartThemeQt);
        second_chart->setTheme(QChart::ChartThemeQt);
    }
    if(choice4->isChecked()){
        chart->setTheme(QChart::ChartThemeDark);
        second_chart->setTheme(QChart::ChartThemeDark);
    }
}

void View_Chart_Sensor_Pollution::New_Simulation(){
    QMessageBox::StandardButton new_simulation;
    new_simulation=QMessageBox::question(this,"Nuova_Simulazione",
                                           "Sicuro di voler avviare una nuova simulazione ?",
                                           QMessageBox::Yes | QMessageBox::No);
    if(new_simulation==QMessageBox::Yes){
        Constructor();
    }
}
