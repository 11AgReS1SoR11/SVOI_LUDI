#ifndef RECOGNIZE_H
#define RECOGNIZE_H

#include <QDialog>
#include <QLabel>
#include <QPalette>
#include <QFileDialog>
#include <QMessageBox>

#include "cardwindow.h"

namespace Ui {
class Recognize;
}

class Recognize : public QDialog
{
    Q_OBJECT

public:
    explicit Recognize(const QStringList& Design, QWidget *parent = nullptr);
    ~Recognize();

private slots:
    void on_ChooseFileButton_clicked();

    void on_OK_clicked();

private:
    Ui::Recognize *ui;
    CardWindow* cardwin;
};

#endif // RECOGNIZE_H
