#include "view_chart_sensor_depth.h"
#include<QtCharts/QSplineSeries>
#include<qrandom.h>
#include<QValueAxis>
#include<QImage>
#include<QLabel>
#include<QDateTimeAxis>
#include<QPushButton>
#include<QIcon>
#include<QPixmap>
#include<QMessageBox>
#include<QGraphicsEffect>
#include<QFont>
#include<QGridLayout>

View_Chart_Sensor_Depth::View_Chart_Sensor_Depth(Sensore_Profondità* s):snsr(s) {
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Grafico_Sensore_Profondità");
    this->setMinimumSize(1200,700);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    main=new QVBoxLayout;
}

void View_Chart_Sensor_Depth::Constructor(){
    while(main->count() != 0){ //cancello cosa c'è attualmente nel layout
        auto item = main->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete main;

    choice1=new QRadioButton;
    choice1->setText("Blue_Cerulean");

    choice2=new QRadioButton;
    choice2->setText("Dark");

    choice3=new QRadioButton;
    choice3->setText("High_Contrast");

    choice4=new QRadioButton;
    choice4->setText("Blue_Icy");

    QPushButton* accept=new QPushButton(QIcon(QPixmap(":/Immagini/Accept.jpg")),"Conferma");
    start=new QPushButton(QIcon(QPixmap(":/Immagini/New_Simulation.png")),"Nuova_Simulazione");

    QHBoxLayout* buttons=new QHBoxLayout;
    buttons->addWidget(start);
    buttons->addWidget(choice1);
    buttons->addWidget(choice2);
    buttons->addWidget(choice3);
    buttons->addWidget(choice4);
    buttons->addWidget(accept);
    buttons->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    QLineSeries* series=new QLineSeries();
    series->setName("Profondità_Rilevate_Dal_Sensore_In_24_Ore");

    //QGridLayout* dates=new QGridLayout(2,)
    int media=0;
    for(int i=0;i<24;i++){
        qreal y=-(snsr->Get_Profondità())/1000;
        if(y>0){
            series->append(QPointF(i,y));
        }else{
            qreal k=QRandomGenerator::global()->bounded(10);
            series->append(QPointF(i,y+k));
        }
        media+=snsr->Get_Profondità();
        series->setPointsVisible(true);
        series->setPointSelected(i,true);
        int x=QRandomGenerator::global()->bounded(snsr->Get_Profondità_Max());
        snsr->Set_Profondità(x);
    }
    snsr->Set_Profondità(media/24);

    QFont* font=new QFont();
    font->setUnderline(true);
    font->setBold(true);

    QLabel* rapporto=new QLabel();
    rapporto->setText("RAPPORTO_SENSORE :  Mediamente "+QString::fromStdString(snsr->Info()).toLower()+"(ZONA : "+QString::fromStdString(snsr->GetWaterArea())+")");
    rapporto->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    rapporto->setFont(*font);

    QValueAxis* axisX=new QValueAxis();
    axisX->setRange(0,24);
    axisX->setTickCount(0);
    axisX->setLabelFormat("%.2f");
    axisX->setTitleText("Time (h)");
    QValueAxis* axisY=new QValueAxis();
    qreal y=-((snsr->Get_Profondità_Max())/1000);
    axisY->setRange(y, 0.0);
    axisY->setTickCount(1);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Depth (Km)");

    chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("DEPTH_SENSOR_CHART");
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(2500);
    chart->addAxis(axisX,Qt::AlignTop);
    chart->addAxis(axisY,Qt::AlignLeft);

    view=new QChartView(chart);
    view->setRenderHints(QPainter::Antialiasing);
    view->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    view->setParent(this);

    main=new QVBoxLayout;
    main->addLayout(buttons);
    main->addWidget(rapporto);
    main->addWidget(view);

    connect(accept,SIGNAL(clicked()),this,SLOT(Update()));
    connect(start,SIGNAL(clicked()),this,SLOT(New_Simulation()));

    this->setLayout(main);
    this->show();
}

void View_Chart_Sensor_Depth::Update(){
    if(choice1->isChecked()) chart->setTheme(QChart::ChartThemeBlueCerulean);
    if(choice2->isChecked()) chart->setTheme(QChart::ChartThemeDark);
    if(choice3->isChecked()) chart->setTheme(QChart::ChartThemeHighContrast);
    if(choice4->isChecked()) chart->setTheme(QChart::ChartThemeBlueIcy);
}

void View_Chart_Sensor_Depth::New_Simulation(){
    QMessageBox::StandardButton new_simulation;
    new_simulation=QMessageBox::question(this,"Nuova_Simulazione",
                                           "Sicuro di voler avviare una nuova simulazione ?",
                                           QMessageBox::Yes | QMessageBox::No);
    if(new_simulation==QMessageBox::Yes){
        Constructor();
    }

}
