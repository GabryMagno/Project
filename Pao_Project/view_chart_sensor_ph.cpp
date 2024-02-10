#include"view_chart_sensor_ph.h"
#include<QScatterSeries>
#include<QLineSeries>
#include<qrandom.h>
#include<QLabel>
#include<QValueAxis>
#include<QBarCategoryAxis>
#include<QCategoryAxis>
#include<QFont>
#include<QMessageBox>
#include<QDate>

View_Chart_Sensor_pH::View_Chart_Sensor_pH(Sensore_pH* s):snsr(s) {
    this->setWindowIcon(QIcon(":/Immagini/Icon.jpg"));
    this->setWindowTitle("Grafico_Sensore_pH");
    this->setMinimumSize(1200,700);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    main=new QVBoxLayout;
}

void View_Chart_Sensor_pH::Constructor(){
    while(main->count() != 0){
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
    choice4->setText("Qt");

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

    QScatterSeries* series=new QScatterSeries;
    series->setName("pH_Registrato");
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    double ph=0.0;
    QStringList hours;
    for(int i=0;i<24;i++){
        qreal y=(snsr->Get_pH());
        series->append(QPointF(i,y));
        ph+=snsr->Get_pH();
        series->setPointsVisible(true);
        series->setPointSelected(i,true);
        snsr->Set_pH(QRandomGenerator::global()->generateDouble()*snsr->Get_pH_Max());
        if(i<10) hours<<"0"+QString::number(i)+":00";
        else hours<<QString::number(i)+":00";
    }
    snsr->Set_pH(ph/12);

    QFont* font=new QFont();
    font->setUnderline(true);
    font->setBold(true);

    QLabel* rapporto=new QLabel();
    rapporto->setText("RAPPORTO SENSORE:\nIl pH medio giornaliero calcolato è :"+QString::fromStdString(snsr->Info()).toLower()+"\npH Medio="+QString::number(snsr->Get_pH()));
    rapporto->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    rapporto->setFont(*font);

    QDate day=QDate::currentDate();
    QBarCategoryAxis* axisX=new QBarCategoryAxis();
    axisX->append(hours);
    axisX->setTitleText("Day : "+day.toString());
    QValueAxis* axisY=new QValueAxis;
    axisY->setRange(snsr->Get_pH_Min(),snsr->Get_pH_Max());
    axisY->setLabelFormat("%.3f");
    auto axisY2=new QCategoryAxis;
    axisY2->setRange(snsr->Get_pH_Min(),snsr->Get_pH_Max());
    axisY2->setTickCount(0);
    axisY2->append("pH_Acido",snsr->Get_pH_Min()+(snsr->Get_pH_Max()-snsr->Get_pH_Min())/4);
    axisY2->append("ph_Neutro",snsr->Get_pH_Min()+((snsr->Get_pH_Max()-snsr->Get_pH_Min())/4)*3);
    axisY2->append("pH_Basico",snsr->Get_pH_Min()+(snsr->Get_pH_Max()-snsr->Get_pH_Min()));
    axisY2->setLinePenColor(Qt::black);
    axisY2->setGridLinePen((series->pen()));

    chart=new QChart();
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignRight);
    chart->addAxis(axisY2,Qt::AlignLeft);
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(2500);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setTitle("PH_SENSOR_CHART");

    series->attachAxis(axisX);
    series->attachAxis(axisY2);
    series->attachAxis(axisY);

    view=new QChartView;
    view->setChart(chart);

    main=new QVBoxLayout;
    main->addLayout(buttons);
    main->addWidget(rapporto);
    main->addWidget(view);

    connect(accept,SIGNAL(clicked()),this,SLOT(Update()));
    connect(start,SIGNAL(clicked()),this,SLOT(New_Simulation()));

    this->setLayout(main);
    this->show();
}

void View_Chart_Sensor_pH::Update(){
    if(choice1->isChecked()) chart->setTheme(QChart::ChartThemeBlueCerulean);
    if(choice2->isChecked()) chart->setTheme(QChart::ChartThemeDark);
    if(choice3->isChecked()) chart->setTheme(QChart::ChartThemeHighContrast);
    if(choice4->isChecked()) chart->setTheme(QChart::ChartThemeQt);
}

void View_Chart_Sensor_pH::New_Simulation(){
    QMessageBox::StandardButton new_simulation;
    new_simulation=QMessageBox::question(this,"Nuova_Simulazione",
                                           "Sicuro di voler avviare una nuova simulazione ?",
                                           QMessageBox::Yes | QMessageBox::No);
    if(new_simulation==QMessageBox::Yes){
        Constructor();
    }
}
