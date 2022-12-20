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

    ajouterCyclone();

    ui->mapConteneur->addWidget(map);
    connect(ui->pushBAjoutCyclone,SIGNAL(clicked(bool)),SLOT(ajouterCyclone()));
    connect(ui->pushBSupprCyclone,SIGNAL(clicked(bool)),SLOT(supprimerCyclone()));
}

//Ajoute un cyclone à la fin du tableau des cyclones
void MainWindow::ajouterCyclone(){
    QTableWidget* tab=ui->tableWidget;

    listeCyclone.append(new Cyclone);

    tab->insertRow(nbLigneCyclone);
    tab->setItem(nbLigneCyclone,0,new QTableWidgetItem("Cyclone" + QString::number(nbLigneCyclone + 1)));
    tab->setItem(nbLigneCyclone,1,new QTableWidgetItem("120"));
    tab->setItem(nbLigneCyclone,2,new QTableWidgetItem("150"));
    tab->setItem(nbLigneCyclone,3,new QTableWidgetItem("BLEU"));
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
            listeCyclone.removeAt(i);
            i--;
            nbLigneCyclone--;
        }
    }
}

void MainWindow::updateCyclone(int r, int c){
    switch ( c )
    {
    case 0:
        listeCyclone.at(r)->setNom(ui->tableWidget->item(r,c)->text());
        break;
    case 1:
        listeCyclone.at(r)->setPosX(ui->tableWidget->item(r,c)->text().toInt());
        break;
    case 2:
        listeCyclone.at(r)->setPosY(ui->tableWidget->item(r,c)->text().toInt());
        break;
    case 3:
        listeCyclone.at(r)->setTaille(ui->tableWidget->item(r,c)->text().toInt());
        break;
    /*case 4:
        listeCyclone.at(r)->setCouleur(ui->tableWidget->item(r,c)->text().toInt());
        break;*/
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

