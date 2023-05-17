
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>

#include <recognize.h>
#include <visitki.h>


QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QDialog

{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private:
    QStringList GetDesign(const QString filepath);
    bool Connection_to_database(QSqlDatabase& db);

private slots:
    void on_Download_clicked();
    void on_MyCard_clicked();
    void on_Daily_clicked();
    void on_Exit_clicked();

private:
    Ui::StartWindow *ui;
    QSqlDatabase db;
    Recognize* RecognizeWindow;
    visitki* VisitkiViewWindow;
    QStringList info;
};

#endif // STARTWINDOW_H
