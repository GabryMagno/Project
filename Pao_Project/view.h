#ifndef VIEW_H
#define VIEW_H
#include"model.h"
#include"view_list_sensor.h"
#include"view_filters.h"
#include<QMainWindow>
#include<QToolBar>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QMenuBar>
#include<QAction>
#include<QObject>
#include"json_file.h"

class View : public QMainWindow{
    Q_OBJECT
private:
    bool not_saved;
    void closeEvent(QCloseEvent *event) override;
public:
    View(Model* =nullptr, QWidget* =nullptr);

    Model* model;
    Json_File* file;
    View_Filters* filters;
    View_List_Sensor* widget_list;

    QWidget*  main_Widget;

    QToolBar* tbar;
    QAction* salva;
    QAction* apri_file;
    QAction* chiudi;
    QAction* salva_come;
    QAction* Aggiungi;

    QHBoxLayout* main;

public slots:
    void Aggiorna();
    void Salva();
    void close();
    void Load();
};

#endif // VIEW_H
