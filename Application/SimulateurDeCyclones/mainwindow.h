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

signals:
    void sigUpdatePos(int, int, int);

    void sigUpdateTaille(int ,int);

private:
    Ui::MainWindow *ui;
    Map *map;
    int nbLigneCyclone;
    QString cheminFichier;
    const QString baseFichier="Chemin du fichier: ";

};
#endif // MAINWINDOW_H
