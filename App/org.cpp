#include "org.h"
#include "ui_org.h"

ORG::ORG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ORG)
{
    ui->setupUi(this);

    Layout = new QFormLayout(this);

    // информация об организации
    Name = new QLineEdit(this);
    Layout->addRow(tr("&Организация:"), Name);
    Right = new QLineEdit(this);
    Layout->addRow(tr("&Правовая форма:"), Right);
    INN = new QLineEdit(this);
    Layout->addRow(tr("&ИНН:"), INN);
    Birthday = new QLineEdit(this);
    Layout->addRow(tr("&Дата создания:"), Birthday);
    Death = new QLineEdit(this);
    Layout->addRow(tr("&Дата ликвидации:"), Death);
    OKVED = new QLineEdit(this);
    Layout->addRow(tr("&ОКВЭД:"), OKVED);
    Actions = new QLineEdit(this);
    Layout->addRow(tr("&Род деятельности:"), Actions);
    Address = new QLineEdit(this);
    Layout->addRow(tr("&Адрес:"), Address);
    Site = new QLineEdit(this);
    Layout->addRow(tr("&Сайт:"), Site);
    Number = new QLineEdit(this);
    Layout->addRow(tr("&Телефон:"), Number);
    Email = new QLineEdit(this);
    Layout->addRow(tr("&Эл. Почта:"), Email);
    Comment = new QLineEdit(this);
    Layout->addRow(tr("&Комментарий:"), Comment);
}

ORG::ORG(const QJsonObject& json, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ORG)
{
    ui->setupUi(this);

    Layout = new QFormLayout(this);

    Name = new QLineEdit(this);
    Name->setText(json["Name"].toString());
    Layout->addRow(tr("&Организация:"), Name);

    Right = new QLineEdit(this);
    Right->setText(json["Right"].toString());
    Layout->addRow(tr("&Правовая форма:"), Right);

    INN = new QLineEdit(this);
    INN->setText(json["INN"].toString());
    Layout->addRow(tr("&ИНН:"), INN);

    Birthday = new QLineEdit(this);
    Birthday->setText(json["Birthday"].toString());
    Layout->addRow(tr("&Дата создания:"), Birthday);

    Death = new QLineEdit(this);
    Death->setText(json["Death"].toString());
    Layout->addRow(tr("&Дата ликвидации:"), Death);

    OKVED = new QLineEdit(this);
    OKVED->setText(json["OKVED"].toString());
    Layout->addRow(tr("&ОКВЭД:"), OKVED);

    Actions = new QLineEdit(this);
    Actions->setText(json["Actions"].toString());
    Layout->addRow(tr("&Род деятельности:"), Actions);

    Address = new QLineEdit(this);
    Address->setText(json["Address"].toString());
    Layout->addRow(tr("&Адрес:"), Address);

    Site = new QLineEdit(this);
    Site->setText(json["Site"].toString());
    Layout->addRow(tr("&Сайт:"), Site);

    Number = new QLineEdit(this);
    Number->setText(json["Number"].toString());
    Layout->addRow(tr("&Телефон:"), Number);

    Email = new QLineEdit(this);
    Email->setText(json["Email"].toString());
    Layout->addRow(tr("&Эл. Почта:"), Email);

    Comment = new QLineEdit(this);
    Comment->setText(json["Comment"].toString());
    Layout->addRow(tr("&Комментарий:"), Comment);
}

ORG::~ORG()
{
    delete ui;
    delete Layout;
    delete OKVED;
    delete Death;
    delete Name;
    delete Birthday;
    delete Address;
    delete Actions;
    delete Site;
    delete Number;
    delete Email;
    delete INN;
    delete Comment;
}

QString ORG::GetName() const
{
    return Name->text();
}

QString ORG::GetRight() const
{
    return Right->text();
}

QString ORG::GetINN() const
{
    return INN->text();
}

QString ORG::GetBirthday() const
{
    return Birthday->text();
}

QString ORG::GetDeath() const
{
    return Death->text();
}

QString ORG::GetOKVED() const
{
    return OKVED->text();
}

QString ORG::GetActions() const
{
    return Actions->text();
}

QString ORG::GetAddress() const
{
    return Address->text();
}

QString ORG::GetSite() const
{
    return Site->text();
}

QString ORG::GetNumber() const
{
    return Number->text();
}

QString ORG::GetEmail() const
{
    return Email->text();
}

QString ORG::GetComment() const
{
    return Comment->text();
}

void ORG::SetTextName(const QString &text)
{
    Name->setText(text);
}

void ORG::SetTextAddress(const QString &text)
{
    Address->setText(text);
}

void ORG::SetTextPravo(const QString &text)
{
    Right->setText(text);
}

void ORG::SetTextINN(const QString &text)
{
    INN->setText(text);
}

void ORG::SetTextBirthday(const QString &text)
{
    Birthday->setText(text);
}

void ORG::SetTextDeath(const QString &text)
{
    Death->setText(text);
}

void ORG::SetTextOKVED(const QString &text)
{
    OKVED->setText(text);
}

void ORG::SetTextAction(const QString &text)
{
    Actions->setText(text);
}

void ORG::SetTextSite(const QString &text)
{
    Site->setText(text);
}

void ORG::SetTextEmail(const QString &text)
{
    Email->setText(text);
}

