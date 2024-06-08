#ifndef VISITKI_H
#define VISITKI_H

#include <QWidget>
#include <QDialog>
#include <QScrollBar>
#include <QGroupBox>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>

#include "cardview.h"
#include "Database.h"

namespace Ui
{
class visitki;
}

class visitki : public QDialog
{
    Q_OBJECT
public:
    explicit visitki(const QStringList& Design, QWidget *parent = nullptr);
    ~visitki();

public slots:
    void show_visitk();
    void onBackButtonClicked();

signals:
    void visitka(QPair<Human*, ORG*>, int);

private:
    Ui::visitki *ui;
    Database db;
    CardView* my_vis;
    QVector<QPair<Human*, ORG*>> allData;
};

#endif // VISITKI_H
