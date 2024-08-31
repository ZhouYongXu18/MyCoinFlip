#ifndef DATEFILE_H
#define DATEFILE_H

#include <QMainWindow>
#include <QMap>
class DateFile : public QMainWindow
{
    Q_OBJECT
public:
    explicit DateFile(QWidget *parent = nullptr);
QMap<int, QVector< QVector<int> > >mData;
signals:
};

#endif // DATEFILE_H
