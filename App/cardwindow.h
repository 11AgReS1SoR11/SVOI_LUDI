#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QDir>

#include "human.h"
#include "org.h"
#include "neuro.h"
#include "cardform.h"
#include "Database.h"

namespace Ui
{
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT
public:
    explicit CardWindow(const QString &filename, QWidget *parent = nullptr);
    ~CardWindow();

public slots:
    void on_pushButton_clicked();

protected:
    Ui::CardWindow *ui;
    CardForm* Card;
    Database db;
    QString imagepath;
};

#endif // CARDWINDOW_H
