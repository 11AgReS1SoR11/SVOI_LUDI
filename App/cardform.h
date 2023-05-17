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

#include <human.h>
#include <org.h>
#include <neuro.h>

namespace Ui {
class CardForm;
}

class CardForm : public QWidget
{
    Q_OBJECT

public:
    explicit CardForm(QWidget *parent = nullptr);
    ~CardForm();
    void NeuroRecognize(const QString &filename, const QString& python_exe_path = "C:\\Users\\79916\\PycharmProjects\\Neuro\\venv\\Scripts\\python.exe", const QString& neuro_py_path = "C:\\Users\\79916\\PycharmProjects\\Neuro\\Neuro.py");
    Human* person;
    ORG* org;
    void SetPictures(const QString& filename);

private:
    Ui::CardForm *ui;
    QFormLayout *Layout;
    QLabel* Image;
    QStringList GetDesign(const QString filepath);
};

#endif // CARDFORM_H
