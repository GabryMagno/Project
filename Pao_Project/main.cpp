#include"view.h"
#include<QApplication>
#include"sensore_temperatura.h"
#include"sensore_inquinamento.h"
#include"sensore_ph.h"
#include"sensore_profondita.h"
#include"model.h"
#include<QScreen>
int main(int argc, char *argv[]){
    srand(time(NULL));
    QApplication a(argc, argv);
    Sensore* st=new Sensore_Temperatura();
    Sensore* st1=new Sensore_Inquinamento();
    Sensore* st2=new Sensore_pH();
    Sensore* st3=new Sensore_Profondità();
    Sensore* st4=new Sensore_Temperatura();
    Sensore* st5=new Sensore_Inquinamento();
    Sensore* st6=new Sensore_pH();
    Sensore* st7=new Sensore_Profondità();
    Sensore* st8=new Sensore_Temperatura();
    Sensore* st9=new Sensore_Inquinamento();
    Model *sensori=new Model();
    sensori->Aggiungi_Sensore(st3);
    sensori->Aggiungi_Sensore(st2);
    sensori->Aggiungi_Sensore(st1);
    sensori->Aggiungi_Sensore(st);
    sensori->Aggiungi_Sensore(st4);
    sensori->Aggiungi_Sensore(st5);
    sensori->Aggiungi_Sensore(st6);
    sensori->Aggiungi_Sensore(st7);
    sensori->Aggiungi_Sensore(st8);
    sensori->Aggiungi_Sensore(st9);
    View* v=new View(sensori);
    int width=v->frameGeometry().width();
    int height=v->frameGeometry().height();
    QScreen* screen=a.primaryScreen();
    int screenWidth=screen->geometry().width();
    int screenHeight=screen->geometry().height();
    v->setGeometry((screenWidth/2)-(width/2), (screenHeight/2)-(height/2), width, height);
    v->show();
    return a.exec();
}
