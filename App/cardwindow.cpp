#include "cardwindow.h"
#include "ui_cardwindow.h"
#include <QSqlError>

CardWindow::CardWindow(const QString &filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Загрузить визитку");

    imagepath = filename;

    Card = new CardForm(this);
    ui->verticalLayout->addWidget(Card);
    QPushButton* OK = new QPushButton(this);
    OK->setText("OK");
    OK->setMinimumHeight(50);
    OK->setStyleSheet("QPushButton { background-color: #27214d; color: white; border: 2px solid black; font-size: 18px; font-weight: bold; font-family: Century Gothic; } QPushButton:hover { border: 2px solid #39306f; font-size: 20px; font-weight: bold; font-family: Century Gothic; }");

    ui->verticalLayout->addWidget(OK);
    Card->NeuroRecognize(imagepath);
    Card->SetPictures(imagepath);


    connect(OK, &QPushButton::clicked, this, &CardWindow::on_pushButton_clicked);
}

CardWindow::~CardWindow()
{
    delete ui;
    delete Card;
}

bool CardWindow::Connection_to_database(QSqlDatabase& db){
    // Открываю базу данных
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Databasa");
    db.setUserName("root");
    db.setPassword("Daniil1102*");

    // Если не открылась база данных, то вывожу сообщение об ошибки и завершаю
    if (!db.open()) return false;
    else return true;
}

bool CheckForDate(const QString& Date)
{
    if (Date.size() != 10) return false;
    if (Date[0].isDigit() && Date[1].isDigit() && Date[2].isDigit() && Date[3].isDigit() &&
        Date[4] == '-' && Date[5].isDigit() && Date[6].isDigit() &&
        Date[7] == '-' && Date[8].isDigit() && Date[9].isDigit()) return true;
    return false;
}

int CardWindow::AddPerson()
{
    Human* Person = this->Card->person;
    QString Name = Person->GetName();
    QString Surname = Person->GetSurname();
    QString FatherName = Person->GetFatherName();
    QString INN = Person->GetINN();
    QString Birthday = Person->GetBirthday();
    if (!CheckForDate(Birthday)) Birthday = "1000-01-01";
    QString Address = Person->GetAddress();
    if (Address.size() >= 199) Address.resize(199);
    QString Phone = Person->GetNumber();
    Phone = Phone.replace("'", "");
    QString Email = Person->GetEmail();
    QString Actions = Person->GetActions();
    QSqlQuery query = QSqlQuery(db);
    QString querystr = QString("INSERT INTO `opd`.`человек` (фамилия,имя,отчество,ИНН,дата_рождения,город,email,род_занятий,телефон) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')").arg(Surname).arg(Name).arg(FatherName).arg(INN).arg(Birthday).arg(Address).arg(Email).arg(Actions).arg(Phone);
    query.exec(querystr);
    qDebug() << query.lastError().text();
    return query.lastInsertId().toInt();
}

int CardWindow::AddORG()
{
    ORG* org = this->Card->org;
    QString FullName = org->GetName();
    QString ShortName = FullName;
    QString AdressORG = org->GetAddress();
    QString INN = org->GetINN();
    QString Pravo = org->GetRight();
    QString Birthday = org->GetBirthday();
    if (!CheckForDate(Birthday)) Birthday = "1000-01-01";
    QString Death = org->GetDeath();
    if (!CheckForDate(Death)) Death = "1000-01-01";
    QString OKVED1 = org->GetOKVED();
    QString OKVED2 = OKVED1;
    QString Actions = org->GetActions();
    QString Site = org->GetSite();
    QString Email = org->GetEmail();
    QSqlQuery query = QSqlQuery(db);
    QString querystr = QString("INSERT INTO `opd`.`организация` (`сокращенное название`, `полное название`, `ИНН`, `правовая форма`, `дата создания`, "
                               "`дата ликвидации`, `основной ОКВЭД код`, `основной ОКВЭД расшифровка`, `род деятельности`, `город`, `сайт`, `email`)"
                               " VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12')")
                           .arg(ShortName).arg(FullName).arg(INN).arg(Pravo).arg(Birthday).arg(Death).arg(OKVED1)
                           .arg(OKVED2).arg(Actions).arg(AdressORG).arg(Site).arg(Email);
    query.exec(querystr);
    qDebug() << query.lastError().text();
    return query.lastInsertId().toInt();
}

int CardWindow::AddPhone(const QString& PhoneNumber, const QString& PhoneTiedId)
{
    QSqlQuery query = QSqlQuery(db);
    QString querystr = QString("INSERT INTO `opd`.`телефон` (`номер телефона`, `телефон_связь_id`) VALUES ('%1', '%2');").arg(PhoneNumber).arg(PhoneTiedId);
    query.exec(querystr);
    return query.lastInsertId().toInt();
}

int CardWindow::AddTied(const QString& UserId, const QString& OrgId, const QString& Position, const QString& Email, const QString& image_path)
{
    QSqlQuery query = QSqlQuery(db);
    QString querystr = QString("INSERT INTO `opd`.`связь` (`объект1`, `объект2`, `должность`, `email`, `визитка`) VALUES ('%1', '%2', '%3', '%4', '%5');").arg(UserId).arg(OrgId).arg(Position).arg(Email).arg(image_path);
    query.exec(querystr);
    return query.lastInsertId().toInt();
}

void CardWindow::on_pushButton_clicked()
{
    if (!Connection_to_database(db))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть базу данных");
        this->close();
        return;
    }

    QString Phone = this->Card->person->GetNumber();
    QString Position = this->Card->person->GetOccupation();
    QString Email = this->Card->person->GetEmail();

    int org_id = AddORG();
    int user_id = AddPerson();
    QString OrgID = QString::number(org_id);
    QString PersonID = QString::number(user_id);


    // копирование картинки в директорию
    QDir dir = QDir::current(); dir.cdUp();
    QString path = dir.absolutePath() + "/../App/Images/" + QFileInfo(imagepath).fileName();
    qDebug() << QFile::copy(imagepath, path);


    int s_id = AddTied(PersonID, OrgID, Position, Email, path);
    QString SID = QString::number(s_id);
    int t_id = AddPhone(Phone, SID);


    QMessageBox compite_message(this);
    compite_message.setText("Успешно");
    compite_message.exec();
    this->close();

    // TODO: занести в ежедневник
}

