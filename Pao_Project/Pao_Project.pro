QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += widgets
QT += charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    json_file.cpp \
    main.cpp \
    model.cpp \
    sensore.cpp \
    sensore_acquatico.cpp \
    sensore_inquinamento.cpp \
    sensore_ph.cpp \
    sensore_profondita.cpp \
    sensore_temperatura.cpp \
    sensore_terrestre.cpp \
    view.cpp \
    view_add_sensor.cpp \
    view_change_sensor_details.cpp \
    view_chart_sensor_depth.cpp \
    view_chart_sensor_ph.cpp \
    view_chart_sensor_pollution.cpp \
    view_chart_sensor_temperature.cpp \
    view_choice_details_new_sensor.cpp \
    view_filters.cpp \
    view_list_sensor.cpp \
    view_sensor.cpp \
    view_sensore_details.cpp \
    visitor_json.cpp

HEADERS += \
    json_file.h \
    lista_sensori.h \
    model.h \
    sensor_visitor.h \
    sensore.h \
    sensore_acquatico.h \
    sensore_inquinamento.h \
    sensore_ph.h \
    sensore_profondita.h \
    sensore_temperatura.h \
    sensore_terrestre.h \
    view.h \
    view_add_sensor.h \
    view_change_sensor_details.h \
    view_chart_sensor.h \
    view_chart_sensor_depth.h \
    view_chart_sensor_ph.h \
    view_chart_sensor_pollution.h \
    view_chart_sensor_temperature.h \
    view_choice_details_new_sensor.h \
    view_filters.h \
    view_list_sensor.h \
    view_sensor.h \
    view_sensore_details.h \
    visitor_json.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
