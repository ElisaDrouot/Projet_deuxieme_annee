#include "map.h"


Map::Map(QWidget * /*parent*/)
{
    pixCyclone.load(":/images/ressources/cyclone.png");
    pixArrow.load(":/images/ressources/arrow.png");

    labelArrow = new QLabel(this);
    labelArrow->setPixmap(pixArrow.scaled(40,40,Qt::KeepAspectRatio));
    labelArrow->move(20, 20);
    labelArrow->resize(40,40);

    labelArrow->show();
    labelArrow->setAttribute(Qt::WA_DeleteOnClose);
    labelArrow->setAcceptDrops(false);


    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    setAcceptDrops(true);
}


QSize Map::minimumSizeHint() const
{
    return QSize(1100, 600);
}

QSize Map::sizeHint() const
{
    return QSize(1100, 600);
}

void Map::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

/*
    for(int i=0;i<listeCyclone.size();i++){
        taille=listeCyclone.at(i)->getTaille();
        painter.drawPixmap(listeCyclone.at(i)->getPosX(),listeCyclone.at(i)->getPosY(),taille,taille,pixCyclone);
    }*/
    int a,b,c,d;
    Position p;


    //contours
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(QRect(0, 1, width() - 1, height() - 1));

    for(int i=0; i<listeCyclone.size();i++){
        if(listeCyclone.at(i)->listePosition.size() > 1){
            for(int j=1; j<listeCyclone.at(i)->listePosition.size();j++){
                a=p.getLatitude(listeCyclone.at(i)->listePosition.at(j-1));
                b=p.getLongitude(listeCyclone.at(i)->listePosition.at(j-1));
                c=p.getLatitude(listeCyclone.at(i)->listePosition.at(j));
                d=p.getLongitude(listeCyclone.at(i)->listePosition.at(j));
                int taillePix=listeImageCyclone.at(i)->pixmap().height()/2;
                painter.drawLine(QLine(a+taillePix,b+taillePix,c+taillePix,d+taillePix));
            }
        }
    }
}

Cyclone* Map::getCyclone(int indice){
    return listeCyclone.at(indice);
}

void Map::ajoutCyclone(){

    Cyclone* cyclone=new Cyclone;
    listeCyclone.append(cyclone);


    QLabel *label = new QLabel(this);
    label->setPixmap(pixCyclone.scaled(cyclone->getTaille(), cyclone->getTaille()));
    label->move(cyclone->getPosX(), cyclone->getPosY());
    label->resize(cyclone->getTaille(),cyclone->getTaille());

    label->show();
    label->setAttribute(Qt::WA_DeleteOnClose);
    listeImageCyclone.append(label);
}

void Map::supprimerCyclone(int indice){
    listeCyclone.removeAt(indice);
    //listeImageCyclone.removeAt(indice);
    QLabel* label=listeImageCyclone.at(indice);

    listeImageCyclone.removeAt(indice);
    label->close();

}

void Map::updatePos(int index, int x, int y){
    if(!listeCyclone.at(index)->IsDead()){
        listeImageCyclone.at(index)->move(x,y);
        repaint();

    }
    else{
        listeImageCyclone.at(index)->hide();
    }
}

void Map::updateTaille(int index, int taille){
    listeImageCyclone.at(index)->setPixmap(pixCyclone.scaled(taille,taille));
    listeImageCyclone.at(index)->resize(taille,taille);
}

void Map::updateArrow(int angle){
    QTransform trans;
    trans.rotate(angle);

    labelArrow->setPixmap(pixArrow.transformed(trans).scaled(40,40,Qt::KeepAspectRatio));

}

void Map::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {//On accepte pas les images venant d'autres application, normal quoi
            event->ignore();
        }
    } else {
        event->ignore();
    }
}

void Map::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {//On accepte pas les images venant d'autres application, normal quoi
            event->ignore();
        }
    } else {
        event->ignore();
    }
}

void Map::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap.scaled(listeCyclone.at(labelActuel)->getTaille(),listeCyclone.at(labelActuel)->getTaille()));

        //calcul de la nouvelle position (entre 0 et 264)
        QPoint pointActuel=event->position().toPoint();
        while(pointActuel.x()%30 != 0){pointActuel.setX(pointActuel.x()-1);}
        while(pointActuel.y()%30 != 0){pointActuel.setY(pointActuel.y()-1);}
        int positionActuelle=0;

        positionActuelle = 22- (pointActuel.x()/30) ;
        positionActuelle += 11*22- 22* (pointActuel.y()/30);


        listeCyclone.at(labelActuel)->setPosition(positionActuelle);


        newIcon->move(pointActuel);//event->position().toPoint() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);


        listeImageCyclone.replace(labelActuel,newIcon);


        //listeCyclone.at(labelActuel)->setPosX(pointActuel.x());//event->position().x()-offset.x());
        //listeCyclone.at(labelActuel)->setPosY(pointActuel.y());//event->position().y()-offset.y());

        emit cycloneDeplace(labelActuel,listeCyclone.at(labelActuel));


        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {//On accepte pas les images venant d'autres application, normal quoi
            event->ignore();
        }
    } else {
        event->ignore();
    }
}


void Map::mousePressEvent(QMouseEvent *event)
{
    int i;

    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child)
        return;
    if(child == labelArrow)
        return;

    for(i=0;i<listeImageCyclone.size();i++){
        if(child == listeImageCyclone.at(i)){
            labelActuel=i;
            break;
        }

    }

    QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());



    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);



    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->position().toPoint() - child->pos());


    /*QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);*/

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    }
}


