#include "cardform.h"
#include "ui_cardform.h"

CardForm::CardForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardForm)
{
    ui->setupUi(this);

    Layout = new QFormLayout();
    QSpacerItem* space = new QSpacerItem(0,5, QSizePolicy::Expanding, QSizePolicy::Expanding);


    // картинка
    Image = new QLabel(this);
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    Image->setAutoFillBackground(true);
    Image->setPalette(palette);
    Image->setAlignment(Qt::AlignHCenter);
    //Image->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    Image->setFixedSize(550, 350);
    QHBoxLayout* IMG = new QHBoxLayout(this);
    IMG->addItem(space);
    IMG->addWidget(Image);
    IMG->addItem(space);

    QWidget* tmp = new QWidget(this);
    tmp->setLayout(IMG);

    Layout->addWidget(tmp);

    // информация о человеке
    person = new Human(this);
    Layout->addWidget(person);

    // пробел
    Layout->addItem(space);
    Layout->addItem(space);

    // информация об организации
    org = new ORG(this);
    Layout->addWidget(org);

    // Располагаться будут на виджете
    QWidget *widgetChoiceRegion = new QWidget();
    widgetChoiceRegion->setLayout(Layout);

    // Помещаем виджет с кнопками в скролл зону
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetChoiceRegion);

    // Для размещения скролл-зоны с кнопками на group box
    // нужно будет создать еще один компоновщик - компоновщик group box
    // поместим на нем скролл-зону
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(scrollArea);

    QGroupBox *groupBoxChoiceRegion = new QGroupBox();
    groupBoxChoiceRegion->setTitle(" ");
    groupBoxChoiceRegion->setLayout(vBoxLayout);

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
    vBoxLayoutMain->addWidget(groupBoxChoiceRegion);

    setLayout(vBoxLayoutMain);

    QStringList info = GetDesign(":/Design/Design");
    widgetChoiceRegion->setStyleSheet(info[2]);
}

void CardForm::NeuroRecognize(const QString &filename, const QString &python_exe_path, const QString &neuro_py_path)
{
    Neuro N(filename, python_exe_path, neuro_py_path);
    this->person->SetTextFIO(N.GetSurname() + " " + N.GetName() + " " + N.GetFatherName());
    this->person->SetTextAddress(N.GetAddress());
    this->person->SetTextEmail(N.GetEmail());
    this->person->SetTextNumber(N.GetNumber());
    this->person->SetTextOccupation(N.GetPosition());

    this->org->SetTextAddress(N.GetAddress());
    this->org->SetTextName(N.GetCompany());
}

void CardForm::SetPictures(const QString &filename)
{
    QPixmap pixmap(filename);
    pixmap = pixmap.scaled(this->Image->size(), Qt::KeepAspectRatio);
    this->Image->setPixmap(pixmap);
    this->Image->setScaledContents(true);
}

QStringList CardForm::GetDesign(const QString filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        return text.split("\n");
    }
}

CardForm::~CardForm()
{
    delete ui;
}
