
#include "neuro.h"
#include <QTimer>
#include <QObject>

// Getting the path to the python interpreter
QString findPythonInterpreter()
{
    QProcess process;
    QString command = "python";

#ifdef Q_OS_WIN // if windows os
    QStringList arguments{"/C", "where python"};
    process.start("cmd.exe", arguments);
#else // if linux os
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

    // Filling in command line arguments (python file and image path)
    QString query = python_exe_path + " " + neuro_py_path + " " + filename_path;
#ifdef Q_OS_WIN // if windows of
    QStringList arguments{"/C", query};
#else // if linux os
    QStringList arguments{"-c", query};
#endif

    // Download window
    QProgressDialog progressDialog("Загрузка...", "Отмена", 0, 100);
    progressDialog.setWindowTitle(" ");
    progressDialog.setWindowModality(Qt::WindowModal); // Блокирует основное окно приложения
    progressDialog.show();
    // set Design
    QStringList info = GetDesign("../App/Design");
    progressDialog.setStyleSheet(info[4]);


    // start python algorithm
    QProcess process;
#ifdef Q_OS_WIN // if windows of
    process.start("cmd.exe", arguments);
#else // if linux os
    process.start("/bin/sh", arguments);
#endif

    // fail process
    if (!process.waitForStarted())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Failed to start process");
        qDebug() << process.errorString(); // print error
        process.waitForFinished();
        progressDialog.close();
        return;
    }

    // Waiting for the completion of the process
    while (!process.waitForFinished(100))
    {
        // Updating the progress of the process
        progressDialog.setValue(progressDialog.value() + 1);
        if (progressDialog.wasCanceled())
        {
            process.kill(); // Cancel the process by clicking on the "Cancel" button
            break;
        }
    }

    // We close the window after the process is completed
    progressDialog.close();

    if (process.exitCode() == 1) // error
    {
        qDebug() << "Process finished with exit code" << process.exitCode() << ". Error: " << process.readAllStandardError();
    }

    Data = new QString(process.readAllStandardOutput());
    qDebug() << *Data; // print output data
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
