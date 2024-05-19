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

QString Human::GetFIO()
{
    QString fio = FIO->text();
    for (int i = fio.size()-1; i >= 0 && fio[i] == ' '; i--)
        fio.resize(fio.size()-1);
    return fio;
}

QString Human::GetSurname()
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 1)
        return "";
    return names[0];
}

QString Human::GetName()
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 2)
        return "";
    return names[1];
}


QString Human::GetFatherName()
{
    QString fio = GetFIO();
    QStringList names = fio.split(" ");
    if (names.size() < 3)
        return "";
    return names[2];
}

QString Human::GetBirthday()
{
    return Birthday->text();
}

QString Human::GetAddress()
{
    return Address->text();
}

QString Human::GetActions()
{
    return Actions->text();
}

QString Human::GetTitul()
{
    return Titul->text();
}

QString Human::GetNumber()
{
    return Number->text();
}

QString Human::GetEmail()
{
    return Email->text();
}

QString Human::GetFacebook()
{
    return Facebook->text();
}

QString Human::GetOccupation()
{
    return Occupation->text();
}

QString Human::GetINN()
{
    return INN->text();
}

QString Human::GetComment()
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
