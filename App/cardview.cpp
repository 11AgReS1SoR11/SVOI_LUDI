#include "cardview.h"
#include "ui_cardview.h"

#include <QMessageBox>

CardView::CardView(const QStringList& Design, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardView)
{
    ui->setupUi(this);
    setWindowTitle("СВОИ ЛЮДИ - Мои визитки");

    QVBoxLayout* Layout = new QVBoxLayout(this);

    Card = new CardForm(this);
    Layout->addWidget(Card);

    QPushButton* Back = new QPushButton(this);
    Back->setText("Назад");
    Back->setMinimumHeight(50);
    Back->setStyleSheet(Design[0]);
    Layout->addWidget(Back);

    setLayout(Layout);
    connect(Back, &QPushButton::clicked, this, CardView::on_pushButton_clicked);
}

CardView::~CardView()
{
    delete ui;
    delete Card;
}

void CardView::on_pushButton_clicked()
{
    this->close();
}


void CardView::show_sl(QSqlQuery my_query)
{
    this->show();
    SetPersonInformation(my_query);
    SetORGInformation(my_query);
    SetPictures(my_query.value(23).toString());
}

void CardView::SetPersonInformation(QSqlQuery my_query)
{
    Human* Person = this->Card->person;
    Person->SetTextFIO(my_query.value(1).toString() + " " + my_query.value(2).toString() + " " + my_query.value(3).toString());
    Person->SetTextINN(my_query.value(4).toString());
    Person->SetTextBirthday(my_query.value(5).toString());
    //Person->SetTextDeath(my_query.value(6).toString());
    Person->SetTextAddress(my_query.value(8).toString());
    Person->SetTextNumber(my_query.value(13).toString());
    Person->SetTextEmail(my_query.value(14).toString());
    Person->SetTextAction(my_query.value(15).toString());

    // Из связи
    Person->SetTextOccupation(my_query.value(21).toString());
}

void CardView::SetORGInformation(QSqlQuery my_query)
{
    ORG* Org = this->Card->org;
    Org->SetTextName(my_query.value(29).toString());
    Org->SetTextINN(my_query.value(30).toString());
    Org->SetTextPravo(my_query.value(31).toString());
    Org->SetTextBirthday(my_query.value(32).toString());
    Org->SetTextDeath(my_query.value(33).toString());
    Org->SetTextOKVED(my_query.value(35).toString());
    Org->SetTextAction(my_query.value(36).toString());
    Org->SetTextAddress(my_query.value(38).toString());
    Org->SetTextSite(my_query.value(43).toString());
    Org->SetTextEmail(my_query.value(44).toString());
}

void CardView::SetPictures(const QString &filename)
{
    Card->SetPictures(filename);
}


