
#include "neuro.h"
#include <QTimer>
#include <QObject>

QString findPythonInterpreter()
{
    QProcess process;
    QString command = "python";
#ifdef Q_OS_WIN
    QStringList arguments{"/C", "where python"};
    process.start("cmd.exe", arguments);
#else
    QStringList arguments{"-c", "which python3"};
    process.start("/bin/sh", arguments);
#endif
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to find Python interpreter";
        return QString();
    }

    QString output = process.readAllStandardOutput().trimmed();
    if (output.isEmpty())
    {
        qDebug() << "No Python interpreter found";
        return QString();
    }

    qDebug() << "Found Python interpreter at" << output;
    return output;
}

Neuro::Neuro(const QString& filename_path, const QString& neuro_py_path)
{
    QString python_exe_path = findPythonInterpreter();
    if (python_exe_path.isEmpty())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось найти интерпретатор Python");
        return;
    }

    QString query = python_exe_path + " " + neuro_py_path + " " + filename_path;
#ifdef Q_OS_WIN
    QStringList arguments{"/C", query};
#else
    QStringList arguments{"-c", query};
#endif

    // Создаем объект QProgressDialog
    QProgressDialog progressDialog("Загрузка...", "Отмена", 0, 100);
    progressDialog.setWindowTitle(" ");
    progressDialog.setWindowModality(Qt::WindowModal); // Блокирует основное окно приложения
    progressDialog.show();
    // Design
    QStringList info = GetDesign("../App/Design");
    progressDialog.setStyleSheet(info[4]);

    QProcess process;
#ifdef Q_OS_WIN
    process.start("cmd.exe", arguments);
#else
    process.start("/bin/sh", arguments);
#endif
    if (!process.waitForStarted())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть терминал");
        qDebug() << "Failed to start process";
        qDebug() << process.errorString(); // вывод ошибки
        process.waitForFinished();
        progressDialog.close();
        return; // доделать, чтобы прога не открывалась
    }

    // Ожидаем завершения процесса
    while (!process.waitForFinished(100))
    {
        // Обновляем прогресс выполнения процесса
        progressDialog.setValue(progressDialog.value() + 1);
        if (progressDialog.wasCanceled())
        {
            process.kill(); // Отменяем процесс при нажатии на кнопку "Cancel"
            break;
        }
    }
    // Закрываем окно после завершения процесса
    progressDialog.close();

    if (process.exitCode() == 1)
    {
        qDebug() << "Process finished with exit code" << process.exitCode() << ". Error: " << process.readAllStandardError();
    }

    Data = new QString(process.readAllStandardOutput());
    qDebug() << *Data;
}


Neuro::~Neuro()
{
    delete Data;
}

QString Neuro::FindAttribute(const int start)
{
    const int end = Data->indexOf("\n", start);
    QString Attribute = Data->mid(start, end - start);
    if (Attribute == "None") return "";
    return Attribute;
}

QStringList Neuro::GetDesign(const QString filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        return text.split("\n");
    }

    throw std::runtime_error("Can't open file with Design");
}

QString Neuro::GetSurname()
{
    int start = Data->indexOf("Surname: ")+9;
    return FindAttribute(start);
}

QString Neuro::GetName()
{
    int start = Data->indexOf("Name: ")+6;
    return FindAttribute(start);
}

QString Neuro::GetFatherName()
{
    int start = Data->indexOf("FatherName: ")+12;
    return FindAttribute(start);
}

QString Neuro::GetCompany()
{
    int start = Data->indexOf("Company: ")+9;
    return FindAttribute(start);
}

QString Neuro::GetPosition()
{
    int start = Data->indexOf("Position: ")+10;
    return FindAttribute(start);
}

QString Neuro::GetNumber()
{
    int start = Data->indexOf("Number: ") + 8 + 2;
    const int end = Data->indexOf("]", start) - 1;
    QString Attribute = Data->mid(start, end - start);
    if (Attribute == "None") return "";
    return Attribute;
}

QString Neuro::GetEmail()
{
    int start = Data->indexOf("Email: ")+7;
    return FindAttribute(start);
}

QString Neuro::GetAddress()
{
    int start = Data->indexOf("Address: ")+9;
    return FindAttribute(start);
}

QString Neuro::GetWeb()
{
    int start = Data->indexOf("Web: ")+5;
    return FindAttribute(start);
}
