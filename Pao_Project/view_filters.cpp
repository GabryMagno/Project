#include "view_filters.h"
#include<QLabel>
#include<QPushButton>

View_Filters::View_Filters(QWidget* p):QWidget(p){

    QLabel* titolo1=new QLabel("FILTRI");
    titolo1->setAlignment(Qt::AlignCenter);

    QFont* font_title=new QFont();
    font_title->bold();
    font_title->setPixelSize(32);

    QFrame* divisor=new QFrame();
    divisor->setFrameShape(QFrame::HLine);
    divisor->setFrameShadow(QFrame::Raised);

    titolo1->setFont(*font_title);

    search_all_sensors=new QRadioButton("Tutti i Sensori");
    search_water_sensors=new QRadioButton("Sensori Acquatici");
    search_terrestrial_sensors=new QRadioButton("Sensori Terrestri");
    search_Snsr_pH=new QRadioButton("Sensori pH");
    search_Snsr_Depth=new QRadioButton("Sensori Profondità");
    search_Snsr_Temp=new QRadioButton("Sensori Temperatura");
    search_Snsr_pm=new QRadioButton("Sensori Inquinamento");
    search_all_sensors=new QRadioButton("Tutti i Sensori");

    Type_search=new QVBoxLayout;
    Type_search->addWidget(search_all_sensors);
    Type_search->addWidget(search_water_sensors);
    Type_search->addWidget(search_terrestrial_sensors);
    Type_search->addWidget(search_Snsr_pH);
    Type_search->addWidget(search_Snsr_Depth);
    Type_search->addWidget(search_Snsr_Temp);
    Type_search->addWidget(search_Snsr_pm);
    Type_search->setSpacing(5);

    QPushButton* ricerca_filtri=new QPushButton(QPixmap(":/Immagini/Cerca.png"),"Cerca");
    QPushButton* annulla_filtri=new QPushButton(QPixmap(":/Immagini/Decline.png"),"Annulla");

    QHBoxLayout* filters=new QHBoxLayout;
    filters->addWidget(ricerca_filtri);
    filters->addWidget(annulla_filtri);

    QVBoxLayout* layout_searching=new QVBoxLayout();
    layout_searching->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    layout_searching->addWidget(titolo1);
    layout_searching->addWidget(divisor);
    layout_searching->addLayout(Type_search);
    layout_searching->addLayout(filters);
    layout_searching->setObjectName("Ricerca con Filtri");

    connect(annulla_filtri,SIGNAL(clicked()),this,SLOT(Annulla_Filtri()));
    connect(ricerca_filtri,SIGNAL(clicked()),this,SLOT(Search_With_Filters()));

    this->setLayout(layout_searching);
}

void View_Filters::Annulla_Filtri(){
    search_all_sensors->setChecked(true);
    emit Researching("Sensore");
}

void View_Filters::Search_With_Filters(){
    if(search_all_sensors->isChecked()) emit Researching("Sensore");
    if(search_terrestrial_sensors->isChecked()) emit Researching("Sensore_Terrestre");
    if(search_water_sensors->isChecked()) emit Researching("Sensore_Acquatico");
    if(search_Snsr_pH->isChecked()) emit Researching("Sensore_pH");
    if(search_Snsr_Depth->isChecked()) emit Researching("Sensore_Profondità");
    if(search_Snsr_Temp->isChecked()) emit Researching("Sensore_Temperatura");
    if(search_Snsr_pm->isChecked()) emit Researching("Sensore_Inquinamento");
}
