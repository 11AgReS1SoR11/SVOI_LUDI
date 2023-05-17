#ifndef VISITKI_H
#define VISITKI_H

#include <QWidget>
#include<QDialog>
#include<QSqlQueryModel>
#include<QScrollBar>
#include<QGroupBox>
#include<QScrollArea>
#include<QPushButton>
#include<QLabel>
#include<QFrame>
#include<QBoxLayout>
#include<QWidget>
#include<QMainWindow>
#include<QVBoxLayout>
#include<QFormLayout>

#include<cardview.h>

namespace Ui {
class visitki;
}

class visitki : public QDialog
{
    Q_OBJECT


public:
    explicit visitki(const QStringList& Design, QWidget *parent = nullptr);
    ~visitki();

private:
    Ui::visitki *ui;
    QSqlQueryModel * query;
    CardView* my_vis;

public slots:
    void show_visitk();
    void onBackButtonClicked();
    void Slot();

//private slots:
//    void Slot();

signals:
    void visitka(QSqlQuery);
};

#endif // VISITKI_H
