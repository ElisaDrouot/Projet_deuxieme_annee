#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>



#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Simulateur de cyclones");
    this->map=new Map;
    nbLigneCyclone=0;

    QSizePolicy policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    map->setSizePolicy(policy);
    ajouterCyclone();
    ui->mapConteneur->addWidget(map);

    connect(this,SIGNAL(sigUpdatePos(int,int,int)),map,SLOT(updatePos(int,int,int)));
    connect(this,SIGNAL(sigUpdateTaille(int,int)),map,SLOT(updateTaille(int,int)));


    connect(map,SIGNAL(cycloneDeplace(int,Cyclone*)),SLOT(updateTableWidgetCyclones(int,Cyclone*)));
    connect(ui->pushBAjoutCyclone,SIGNAL(clicked(bool)),SLOT(ajouterCyclone()));
    connect(ui->pushBSupprCyclone,SIGNAL(clicked(bool)),SLOT(supprimerCyclone()));
    connect(ui->SBdirectionVent,SIGNAL(valueChanged(int)),map,SLOT(updateArrow(int)));
}

//Ajoute un cyclone à la fin du tableau des cyclones
void MainWindow::ajouterCyclone(){
    QTableWidget* tab=ui->tableWidget;

    map->ajoutCyclone();

    tab->insertRow(nbLigneCyclone);
    tab->setItem(nbLigneCyclone,0,new QTableWidgetItem("Cyclone" + QString::number(nbLigneCyclone + 1)));
    tab->setItem(nbLigneCyclone,1,new QTableWidgetItem("120"));
    tab->setItem(nbLigneCyclone,2,new QTableWidgetItem("150"));
    tab->setItem(nbLigneCyclone,3,new QTableWidgetItem("100"));
    QTableWidgetItem* checkBoxItem=new QTableWidgetItem();
    checkBoxItem->setCheckState(Qt::Unchecked);
    tab->setItem(nbLigneCyclone,4,checkBoxItem);
    connect(tab,SIGNAL(cellChanged(int,int)),this,SLOT(updateCyclone(int,int)));
    nbLigneCyclone++;
}

void MainWindow::supprimerCyclone(){
    for(int i=0;i<nbLigneCyclone;i++){
        if(ui->tableWidget->item(i,4)->checkState() == Qt::Checked){
            ui->tableWidget->removeRow(i);
            this->map->supprimerCyclone(i);
            i--;
            nbLigneCyclone--;
        }
    }
}

//Permet de mettre à jour les positions de départ des cyclones
void MainWindow::updateCyclone(int r, int c){
    switch ( c )
    {
    case 0:
        map->getCyclone(r)->setNom(ui->tableWidget->item(r,c)->text());
        break;
    case 1:
        map->getCyclone(r)->setPosX(ui->tableWidget->item(r,c)->text().toInt());
        emit sigUpdatePos(r,map->getCyclone(r)->getPosX(),map->getCyclone(r)->getPosY());
        break;
    case 2:
        map->getCyclone(r)->setPosY(ui->tableWidget->item(r,c)->text().toInt());
        emit sigUpdatePos(r,map->getCyclone(r)->getPosX(),map->getCyclone(r)->getPosY());
        break;
    case 3:
        map->getCyclone(r)->setTaille(ui->tableWidget->item(r,c)->text().toInt());
        emit sigUpdateTaille(r,map->getCyclone(r)->getTaille());
        break;
    /*case 4:
        map->getCyclone(r)->setCouleur(ui->tableWidget->item(r,c)->text().toInt());
        break;*/
    }
    map->repaint();

}

void MainWindow::updateTableWidgetCyclones(int index,Cyclone* cyclone){
    QTableWidget* tab=ui->tableWidget;

    tab->setItem(index,0,new QTableWidgetItem(cyclone->getNom()));
    tab->setItem(index,1,new QTableWidgetItem(QString::number(cyclone->getPosX())));
    tab->setItem(index,2,new QTableWidgetItem(QString::number(cyclone->getPosY())));
    tab->setItem(index,3,new QTableWidgetItem(QString::number(cyclone->getTaille())));
}



MainWindow::~MainWindow()
{
    delete ui;
}

