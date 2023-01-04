#ifndef MAP_H
#define MAP_H
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QtWidgets>

#include <QLabel>
#include "cyclone.h"
#include <QFrame>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Map : public QFrame
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    Cyclone* getCyclone(int indice);
    void ajoutCyclone();
    void supprimerCyclone(int indice);

public slots:
    void updatePos(int index, int x, int y);
    void updateTaille(int index, int taille);
    void updateArrow(int angle);

signals:
    void cycloneDeplace(int index,Cyclone* cyclone);

protected:
    void paintEvent(QPaintEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int labelActuel;
    QPen pen;
    QBrush brush;
    QPixmap pixBackground;
    QPixmap pixCyclone;
    QPixmap pixArrow;

    QLabel *labelArrow;
    QList<Cyclone*> listeCyclone;
    QList<QLabel*> listeImageCyclone;
};
#endif // MAP_H
