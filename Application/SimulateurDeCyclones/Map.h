#ifndef MAP_H
#define MAP_H
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

#include "cyclone.h"


class Map : public QWidget
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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;
    QPixmap pixBackground;
    QPixmap pixCyclone;
    QList<Cyclone*> listeCyclone;

};
#endif // MAP_H
