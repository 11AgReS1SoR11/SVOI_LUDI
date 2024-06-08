
#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ");

    if (!Connection_to_database()) // try connect to database
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть базу данных");
    }

    // Setting design
    info = GetDesign("../App/Design");
    ui->Download->setStyleSheet(info[0]);
    ui->MyCard->setStyleSheet(info[0]);
    ui->Daily->setStyleSheet(info[0]);
    ui->Exit->setStyleSheet(info[0]);
    this->setStyleSheet(info[1]);
}

StartWindow::~StartWindow()
{
    delete ui;
}

QStringList StartWindow::GetDesign(const QString filepath)
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

void StartWindow::on_Download_clicked()
{
    RecognizeWindow = new Recognize(info, this);
    RecognizeWindow->exec();
}

void StartWindow::on_MyCard_clicked()
{
    VisitkiViewWindow = new visitki(info, this);
    VisitkiViewWindow->exec();
}

void StartWindow::on_Daily_clicked() // Not implemented yet
{
    QMessageBox::warning(this, tr("Внимание"),
                             tr("Данной функции ещё нет\nно она скоро появится"),
                             QMessageBox::Ok);
}

void StartWindow::on_Exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Вы уверены?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

bool StartWindow::Connection_to_database() // checks the existence of a data file
{
    QFile f("../App/Data.json");
    if (f.exists()) return true;
    return false;
}
