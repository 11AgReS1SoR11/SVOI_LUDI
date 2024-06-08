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
    connect(Back, &QPushButton::clicked, this, &CardView::on_pushButton_clicked);
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

void CardView::cardReview(QPair<Human*, ORG*> my_query, int ID)
{
    if (ID == 0)
    {
        qDebug() << "NO such data";
        return; // TODO: warning message (not found)
    }

    SetPersonInformation(my_query);
    SetORGInformation(my_query);
    SetPictures("../App/Images/ID" + QString::number(ID) + ".jpg");
    this->show();
}

void CardView::SetPersonInformation(QPair<Human*, ORG*>& my_query)
{
    Human* Person = this->Card->person;
    Person->SetTextFIO(my_query.first->GetFIO());
    Person->SetTextINN(my_query.first->GetINN());
    Person->SetTextBirthday(my_query.first->GetBirthday());
    Person->SetTextAddress(my_query.first->GetAddress());
    Person->SetTextNumber(my_query.first->GetNumber());
    Person->SetTextEmail(my_query.first->GetEmail());
    Person->SetTextAction(my_query.first->GetActions());
    Person->SetTextOccupation(my_query.first->GetOccupation());
}

void CardView::SetORGInformation(QPair<Human*, ORG*>& my_query)
{
    ORG* Org = this->Card->org;
    Org->SetTextName(my_query.second->GetName());
    Org->SetTextINN(my_query.second->GetINN());
    Org->SetTextPravo(my_query.second->GetRight());
    Org->SetTextBirthday(my_query.second->GetBirthday());
    Org->SetTextDeath(my_query.second->GetDeath());
    Org->SetTextOKVED(my_query.second->GetOKVED());
    Org->SetTextAction(my_query.second->GetActions());
    Org->SetTextAddress(my_query.second->GetAddress());
    Org->SetTextSite(my_query.second->GetSite());
    Org->SetTextEmail(my_query.second->GetEmail());
}

void CardView::SetPictures(const QString &filename)
{
    Card->SetPictures(filename);
}
