
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
    QString* Data;
    QString FindAttribute(const int start);

    QStringList GetDesign(const QString filepath);
};




class MyObject : public QObject
{
    Q_OBJECT

public:
    MyObject(QObject *parent = nullptr)
        : QObject(parent)
    {
        // Создаем диалоговое окно загрузки
        m_progressDialog = new QProgressDialog("Loading...", "Cancel", 0, 100, nullptr);
        m_progressDialog->setWindowModality(Qt::WindowModal);
        m_progressDialog->setMinimumDuration(0);
        m_progressDialog->setValue(0);
    }

    ~MyObject()
    {
        delete m_progressDialog;
    }

public slots:
    void doSomething()
    {
        // Выполняем какую-то длительную операцию
        for (int i = 0; i <= 100; ++i) {
            // Обновляем значение прогресса
            m_progressDialog->setValue(i);

            // Проверяем, не была ли нажата кнопка "Отмена"
            if (m_progressDialog->wasCanceled()) {
                return;
            }
        }

        // Операция выполнена, закрываем диалоговое окно
        m_progressDialog->close();
    }

private:
    QProgressDialog *m_progressDialog;
};

#endif // NEURO_H
