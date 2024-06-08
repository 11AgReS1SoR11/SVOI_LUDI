#include "cardform.h"
#include "ui_cardform.h"

CardForm::CardForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardForm)
{
    ui->setupUi(this);

    Layout = new QFormLayout();
    QSpacerItem* space = new QSpacerItem(0,5, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set image
    Image = new QLabel(this);
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    Image->setAutoFillBackground(true);
    Image->setPalette(palette);
    Image->setAlignment(Qt::AlignHCenter);
    Image->setFixedSize(550, 350);

    // Add image to layout
    QHBoxLayout* IMG = new QHBoxLayout(this);
    IMG->addItem(space); // add some space
    IMG->addWidget(Image);
    IMG->addItem(space); // add some space
    QWidget* tmp = new QWidget(this);
    tmp->setLayout(IMG);
    Layout->addWidget(tmp);

    // Human information
    person = new Human(this);
    Layout->addWidget(person);

    // add some space
    Layout->addItem(space);
    Layout->addItem(space);

    // Organization information
    org = new ORG(this);
    Layout->addWidget(org);

    // Set to widget
    QWidget *widgetChoiceRegion = new QWidget();
    widgetChoiceRegion->setLayout(Layout);

    // Putting the widget with buttons in the scroll zone
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetChoiceRegion);

    // To place a scroll zone with buttons on the group box
    // you will need to create another linker - the group boxlinker
    // we will place a scroll zone on it
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(scrollArea);

    QGroupBox *groupBoxChoiceRegion = new QGroupBox();
    groupBoxChoiceRegion->setTitle(" ");
    groupBoxChoiceRegion->setLayout(vBoxLayout);

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
    vBoxLayoutMain->addWidget(groupBoxChoiceRegion);

    setLayout(vBoxLayoutMain);

    QStringList info = GetDesign("../App/Design");
    widgetChoiceRegion->setStyleSheet(info[2]);
}

void CardForm::NeuroRecognize(const QString &filename, const QString &neuro_py_path)
{
    Neuro N(filename, neuro_py_path); // recognizing

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
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        return text.split("\n");
    }
    
    throw std::runtime_error("Can't open file with Design");
}

CardForm::~CardForm()
{
    delete ui;
}
