#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QCheckBox>

#include "map.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ajouterCyclone();
    void supprimerCyclone();
    void updateCyclone(int x, int y);
    void updateTableWidgetCyclones(int index,Cyclone* cyclone);
    void choixCheminFic();//clic sur bouton du choix du chemin du fichier
    void updateCheminFic();//Changement via modification de l'EditText
    void etapeCyclone();
    void simuler();
    void remiseAZero();

    void setVitesse(int vites);
    void setPression(int press);
    void setTemperature(int temp);

    float rayon(int position, int iter);


signals:
    void sigUpdatePos(int, int, int);

    void sigUpdateTaille(int ,int);

private:
    Ui::MainWindow *ui;
    Map *map;
    int nbLigneCyclone;
    QString cheminFichier;
    bool enSimulation;
    const QString baseFichier="Chemin du fichier: ";
    float vitesse;
    float pression;
    float temperature;

};
#endif // MAINWINDOW_H
