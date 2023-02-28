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
    statusBar()->setSizeGripEnabled(false);

    this->map=new Map;
    nbLigneCyclone=0;

    QSizePolicy policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    map->setSizePolicy(policy);
    ajouterCyclone();
    //map->setMinimumSize(1100,600);
    map->setMinimumHeight(362);
    map->setMaximumHeight(362);
    ui->mapConteneur->addWidget(map);

    cheminFichier = "/data.csv";


    ui->lNomFichier->setText(baseFichier + cheminFichier );

    enSimulation=false;

    setVitesse(ui->SBvitesseVent->value());
    setPression(ui->SBpression->value());
    setTemperature(ui->SBTemperature->value());


    //connexion onglet graphique
    connect(this,SIGNAL(sigUpdatePos(int,int,int)),map,SLOT(updatePos(int,int,int)));
    connect(this,SIGNAL(sigUpdateTaille(int,int)),map,SLOT(updateTaille(int,int)));

    //connexion des sélecteurs de paramètres
    connect(ui->SBTemperature,SIGNAL(valueChanged(int)),this,SLOT(setTemperature(int)));
    connect(ui->SBvitesseVent,SIGNAL(valueChanged(int)),this,SLOT(setVitesse(int)));
    connect(ui->SBpression,SIGNAL(valueChanged(int)),this,SLOT(setPression(int)));



    connect(map,SIGNAL(cycloneDeplace(int,Cyclone*)),SLOT(updateTableWidgetCyclones(int,Cyclone*)));
    connect(ui->pushBAjoutCyclone,SIGNAL(clicked(bool)),SLOT(ajouterCyclone()));
    connect(ui->pushBSupprCyclone,SIGNAL(clicked(bool)),SLOT(supprimerCyclone()));
    connect(ui->SBdirectionVent,SIGNAL(valueChanged(int)),map,SLOT(updateArrow(int)));

    //connexion onglet multiple
    connect(ui->btnImportationFic,SIGNAL(clicked(bool)),SLOT(choixCheminFic()));
    connect(ui->nomFichier,SIGNAL(textEdited(QString)),SLOT(updateCheminFic()));


    connect(ui->pushBLancerSimu,SIGNAL(clicked(bool)),SLOT(simuler()));
    connect(ui->pushBRAZ,SIGNAL(clicked(bool)),SLOT(remiseAZero()));

}

//Ajoute un cyclone à la fin du tableau des cyclones
void MainWindow::ajouterCyclone(){
    QTableWidget* tab=ui->tableWidget;
    map->ajoutCyclone();

    tab->insertRow(nbLigneCyclone);
    tab->setItem(nbLigneCyclone,0,new QTableWidgetItem("Cyclone" + QString::number(nbLigneCyclone + 1)));
    tab->setItem(nbLigneCyclone,1,new QTableWidgetItem(QString::number(map->getCyclone(nbLigneCyclone)->getPosX())));
    tab->setItem(nbLigneCyclone,2,new QTableWidgetItem(QString::number(map->getCyclone(nbLigneCyclone)->getPosY())));
    tab->setItem(nbLigneCyclone,3,new QTableWidgetItem(QString::number(map->getCyclone(nbLigneCyclone)->getTaille())));
    QTableWidgetItem* checkBoxItem=new QTableWidgetItem();
    checkBoxItem->setCheckState(Qt::Unchecked);
    checkBoxItem->setSelected(false);
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
        map->getCyclone(r)->setPosition(ui->tableWidget->item(r,c)->text().toInt());
        emit sigUpdatePos(r,map->getCyclone(r)->getPosX(),map->getCyclone(r)->getPosY());

        //emit sigUpdateTaille(r,map->getCyclone(r)->getTaille());
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
    tab->setItem(index,3,new QTableWidgetItem(QString::number(cyclone->getPosition())));
}

void MainWindow::choixCheminFic(){
    cheminFichier = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Images (*.csv)"));
    ui->lNomFichier->setText(baseFichier + cheminFichier);
    ui->nomFichier->setText(cheminFichier);
}

void MainWindow::updateCheminFic(){
    if(ui->nomFichier->text().endsWith(".csv")){
        cheminFichier=ui->nomFichier->text();
        ui->lNomFichier->setText(baseFichier + cheminFichier);
    }
    else{
        ui->nomFichier->setText(cheminFichier);
    }
}

void MainWindow::etapeCyclone(){
    for(int i=0;i<nbLigneCyclone;i++){
        map->getCyclone(i)->nextPosition();
        /*int newTaille=rayon(map->getCyclone(i)->getPosition(),map->getCyclone(i)->listePosition.count()-1);
        map->getCyclone(i)->setTaille(newTaille);

        emit sigUpdateTaille(i,newTaille);
        */
        emit sigUpdatePos(i,map->getCyclone(i)->getPosX(),map->getCyclone(i)->getPosY());
    }
}

void MainWindow::simuler(){
    //maj des paramètres
    setVitesse(ui->SBvitesseVent->value());
    setPression(ui->SBpression->value());
    setTemperature(ui->SBTemperature->value());

    enSimulation=true;
    while(enSimulation){
        etapeCyclone();
        enSimulation=false;
        for(int i=0 ;i<nbLigneCyclone ;i++){
            if(!map->getCyclone(i)->IsDead()){
                enSimulation=true;
            }
        }
        usleep(400000);
    }
}

void MainWindow::remiseAZero(){
    for(int i=nbLigneCyclone-1;i>=0;i--){
        ui->tableWidget->item(i,4)->setCheckState(Qt::Checked);

    }
    supprimerCyclone();
    ajouterCyclone();
}

void MainWindow::setVitesse(int vites){
    vitesse=vites*1000/3600;
}

void MainWindow::setPression(int press){
    pression=press;
}

void MainWindow::setTemperature(int temp){
    temperature=temp+273.15;
}

float parabole(float initial, float finalp, int x){
    float xsommet = 2;
    float a = (initial - finalp)/(xsommet*xsommet);
    float res = a*(x - xsommet)*(x - xsommet) + finalp;
    return res;
}

float MainWindow::rayon(int position, int iter){

    float latitude=((position-1)%22)*5;

    float pstd = 1000; //hPa
    float g = 9.80665; //m/s
    float c = 0.00706; //lambda constante qui montre la convection
    float z = 15000; //hauteur entre 10*10**3 et 15*10**3


    float Pfinal = 999;
    float Tfinal = 30 + 273.15;

    float Px = parabole(pression, Pfinal,iter);
    float Tx = parabole(temperature,Tfinal,iter);

    if(latitude == 0){latitude = 1;}
    float f = 1.454*pow(10,-4)*sin(latitude*M_PI/180);//sind(latitude);
    float rayon = abs((1/(f*10))*((g*Tx*c*z*pow(Px/pstd,2/7))/(300.15*vitesse) - vitesse));

    return 10 + rayon*30/2994;
}


MainWindow::~MainWindow()
{
    delete ui;
}

