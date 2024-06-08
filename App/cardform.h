#ifndef CARDFORM_H
#define CARDFORM_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>

#include "human.h"
#include "org.h"
#include "neuro.h"

namespace Ui
{
class CardForm;
}

class CardForm : public QWidget
{
    Q_OBJECT
public:
    explicit CardForm(QWidget *parent = nullptr);
    ~CardForm();
    void NeuroRecognize(const QString &filename, const QString& neuro_py_path = "../App/Neuro.py");
    void SetPictures(const QString& filename);

    Human* person;
    ORG* org;

private:
    QStringList GetDesign(const QString filepath);

    Ui::CardForm *ui;
    QFormLayout *Layout;
    QLabel* Image;
};

#endif // CARDFORM_H
