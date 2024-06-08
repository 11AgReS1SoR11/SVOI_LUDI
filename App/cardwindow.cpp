#include "cardwindow.h"
#include "ui_cardwindow.h"

CardWindow::CardWindow(const QString &filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow),
    db("../App/Data.json")
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Загрузить визитку");

    imagepath = filename;

    // Button Ok
    QPushButton* OK = new QPushButton(this);
    OK->setText("OK");
    OK->setMinimumHeight(50);
    OK->setStyleSheet("QPushButton { background-color: #27214d; color: white; border: 2px solid black; font-size: 18px; font-weight: bold; font-family: Century Gothic; } QPushButton:hover { border: 2px solid #39306f; font-size: 20px; font-weight: bold; font-family: Century Gothic; }");
    ui->verticalLayout->addWidget(OK);

    // Recognize and fill fields
    Card = new CardForm(this);
    ui->verticalLayout->addWidget(Card);
    Card->NeuroRecognize(imagepath);
    Card->SetPictures(imagepath);

    connect(OK, &QPushButton::clicked, this, &CardWindow::on_pushButton_clicked);
}

CardWindow::~CardWindow()
{
    delete ui;
    delete Card;
}

void CardWindow::on_pushButton_clicked()
{
    // copying an image to the directory "images"
    QDir dir = QDir::current();
    QString path = dir.absolutePath() + "/../App/Images/ID" + QString::number(db.getCount() + 1) + ".jpg";
    qDebug() << QFile::copy(imagepath, path);

    // Add data to database
    db.addUser(*Card->person, *Card->org);

    // Complite message
    QMessageBox compite_message(this);
    compite_message.setText("Успешно");
    compite_message.exec();
    this->close();
}

