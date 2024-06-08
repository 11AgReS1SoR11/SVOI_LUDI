
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>

#include "recognize.h"
#include "visitki.h"

namespace Ui
{
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT
public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_Download_clicked();
    void on_MyCard_clicked();
    void on_Daily_clicked();
    void on_Exit_clicked();

private:
    QStringList GetDesign(const QString filepath);
    bool Connection_to_database();

    Ui::StartWindow *ui;
    Recognize* RecognizeWindow;
    visitki* VisitkiViewWindow;
    QStringList info; // Design information (will be shared with the rest of the classes)
};

#endif // STARTWINDOW_H
