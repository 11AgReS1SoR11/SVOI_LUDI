#include "human.h"
#include "ui_human.h"

Human::Human(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Human)
{
    ui->setupUi(this);

    Layout = new QFormLayout(this);

    // информация о человеке
    FIO = new QLineEdit(this);
    Layout->addRow(tr("&ФИО:"), FIO);
    Birthday = new QLineEdit(this);
    Layout->addRow(tr("&Дата рождения:     "), Birthday);
    Address = new QLineEdit(this);
    Layout->addRow(tr("&Адрес:"), Address);
    Actions = new QLineEdit(this);
    Layout->addRow(tr("&Род занятий:"), Actions);
    Titul = new QLineEdit(this);
    Layout->addRow(tr("&Титул:"), Titul);
    Number = new QLineEdit(this);
    Layout->addRow(tr("&Телефон:"), Number);
    Email = new QLineEdit(this);
    Layout->addRow(tr("&Эл. Почта:"), Email);
    Facebook = new QLineEdit(this);
    Layout->addRow(tr("&Facebook:"), Facebook);
    Occupation = new QLineEdit(this);
    Layout->addRow(tr("&Должность:"), Occupation);
    INN = new QLineEdit(this);
    Layout->addRow(tr("&ИНН:"), INN);
    Comment = new QLineEdit(this);
    Layout->addRow(tr("&Комментарий:"), Comment);
}

Human::Human(const QJsonObject& json, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Human)
{
    ui->setupUi(this);

    Layout = new QFormLayout(this);

    // информация о человеке
    FIO = new QLineEdit(this);
    FIO->setText(json["FIO"].toString());
    Layout->addRow(tr("&ФИО:"), FIO);

    Birthday = new QLineEdit(this);
    Birthday->setText(json["Birthday"].toString());
    Layout->addRow(tr("&Дата рождения:     "), Birthday);

    Address = new QLineEdit(this);
    Address->setText(json["Address"].toString());
    Layout->addRow(tr("&Адрес:"), Address);

    Actions = new QLineEdit(this);
    Actions->setText(json["Actions"].toString());
    Layout->addRow(tr("&Род занятий:"), Actions);

    Titul = new QLineEdit(this);
    Titul->setText(json["Titul"].toString());
    Layout->addRow(tr("&Титул:"), Titul);

    Number = new QLineEdit(this);
    Number->setText(json["Number"].toString());
    Layout->addRow(tr("&Телефон:"), Number);

    Email = new QLineEdit(this);
    Email->setText(json["Email"].toString());
    Layout->addRow(tr("&Эл. Почта:"), Email);

    Facebook = new QLineEdit(this);
    Facebook->setText(json["Facebook"].toString());
    Layout->addRow(tr("&Facebook:"), Facebook);

    Occupation = new QLineEdit(this);
    Occupation->setText(json["Occupation"].toString());
    Layout->addRow(tr("&Должность:"), Occupation);

    INN = new QLineEdit(this);
    INN->setText(json["INN"].toString());
    Layout->addRow(tr("&ИНН:"), INN);

    Comment = new QLineEdit(this);
    Comment->setText(json["Comment"].toString());
    Layout->addRow(tr("&Комментарий:"), Comment);
}

Human::~Human()
{
    delete ui;
    delete Layout;
    delete FIO;
    delete Birthday;
    delete Address;
    delete Actions;
    delete Titul;
    delete Number;
    delete Email;
    delete Facebook;
    delete Occupation;
    delete INN;
    delete Comment;
}

QString Human::GetFIO() const
{
    QString fio = FIO->text();
    for (int i = fio.size()-1; i >= 0 && fio[i] == ' '; i--)
        fio.resize(fio.size()-1);
    return fio;
}

QString Human::GetSurname() const
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 1)
        return "";
    return names[0];
}

QString Human::GetName() const
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 2)
        return "";
    return names[1];
}


QString Human::GetFatherName() const
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 3)
        return "";
    return names[2];
}

QString Human::GetBirthday() const
{
    return Birthday->text();
}

QString Human::GetAddress() const
{
    return Address->text();
}

QString Human::GetActions() const
{
    return Actions->text();
}

QString Human::GetTitul() const
{
    return Titul->text();
}

QString Human::GetNumber() const
{
    return Number->text();
}

QString Human::GetEmail() const
{
    return Email->text();
}

QString Human::GetFacebook() const
{
    return Facebook->text();
}

QString Human::GetOccupation() const
{
    return Occupation->text();
}

QString Human::GetINN() const
{
    return INN->text();
}

QString Human::GetComment() const
{
    return Comment->text();
}

void Human::SetTextFIO(const QString &text)
{
    FIO->setText(text);
}

void Human::SetTextAddress(const QString &text)
{
    Address->setText(text);
}

void Human::SetTextNumber(const QString &text)
{
    Number->setText(text);
}

void Human::SetTextEmail(const QString &text)
{
    Email->setText(text);
}

void Human::SetTextOccupation(const QString &text)
{
    Occupation->setText(text);
}

void Human::SetTextBirthday(const QString &text)
{
    Birthday->setText(text);
}

void Human::SetTextINN(const QString &text)
{
    INN->setText(text);
}

void Human::SetTextAction(const QString &text)
{
    Actions->setText(text);
}
