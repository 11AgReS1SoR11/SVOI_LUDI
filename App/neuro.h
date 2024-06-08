
#ifndef NEURO_H
#define NEURO_H

#include <QStringList>
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QProgressDialog>
#include <QWidget>
#include <QMessageBox>
#include <QFile>

class Neuro
{
public:
    Neuro(const QString &filename_path, const QString &neuro_py_path = "../App/Neuro.py");
    ~Neuro();
    QString GetSurname();
    QString GetName();
    QString GetFatherName();
    QString GetCompany();
    QString GetPosition();
    QString GetNumber();
    QString GetEmail();
    QString GetAddress();
    QString GetWeb();

private:
    QString FindAttribute(const int start);
    QStringList GetDesign(const QString filepath);

    QString* Data;
};

#endif // NEURO_H
