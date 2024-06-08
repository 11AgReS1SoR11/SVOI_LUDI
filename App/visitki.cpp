#include "visitki.h"
#include "ui_visitki.h"
#include <QDir>

visitki::visitki(const QStringList& Design, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::visitki),
    db("../App/Data.json")
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Мои визитки");

    // Fixed size
    const int height = 200;
    const int width = 300;

    my_vis = new CardView(Design, this);
    QFormLayout *gLayoutChoiceRegion = new QFormLayout();

    // TODO: free allData
    // get Data from database
    allData = db.readAllData();
    int countVis = db.getCount();
    QPushButton* buttons[countVis];

    connect(this, &visitki::visitka, my_vis, &CardView::cardReview);
    for (int i = 0; i < countVis; i++)
    {
        // Create button
        QString FIO = allData[i].first->GetFIO();
        buttons[i] = new QPushButton(FIO);
        buttons[i]->setStyleSheet(Design[0]);
        buttons[i]->setMinimumHeight(height);

        // Connect if clicked -> show visitka
        connect(buttons[i], SIGNAL(clicked()), SLOT(show_visitk()));

        // Finding images that are in the Image folder and are called ID + order of addition
        QDir dir = QDir::current();
        QString filename = dir.absolutePath() + "/../App/Images/ID" + QString::number(i+1) + ".jpg";
        QPixmap pixmap(filename);

        // Add image to screen
        QLabel* Field = new QLabel(parent);
        Field->setFixedSize(width, height);
        pixmap.scaled(Field->size(), Qt::KeepAspectRatio);
        Field->setScaledContents(true);
        Field->setPixmap(pixmap);

        // Add to layout
        gLayoutChoiceRegion->addRow(Field, buttons[i]);
    }

    // They will be located on the widget
    QWidget *widgetChoiceRegion = new QWidget();
    widgetChoiceRegion->setLayout(gLayoutChoiceRegion);

    // Putting the widget with buttons in the scroll zone
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetChoiceRegion);

    // To place a scroll zone with buttons on the group box
    // you will need to create another linker - the group box linker
    // we will place a scroll zone on it
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(scrollArea);

    QGroupBox *groupBoxChoiceRegion = new QGroupBox();
    groupBoxChoiceRegion->setLayout(vBoxLayout);

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
    vBoxLayoutMain->addWidget(groupBoxChoiceRegion);

    // Add button "Go back"
    QPushButton* Back = new QPushButton(this);
    Back->setText("Назад");
    Back->setMinimumHeight(50);
    Back->setStyleSheet(Design[0]);
    vBoxLayoutMain->addWidget(Back);
    connect(Back, &QPushButton::clicked, this, &visitki::onBackButtonClicked);

    // set Design
    widgetChoiceRegion->setStyleSheet(Design[3]);

    setLayout(vBoxLayoutMain);
}

visitki::~visitki()
{
    delete ui;
    for (auto& i : allData)
    {
        delete i.first;
        delete i.second;
    }
}

void visitki::onBackButtonClicked()
{
    this->close();
}

void visitki::show_visitk()
{
    // Get clicked button
    QPushButton* button = (QPushButton*)sender();

    // We take the name out of the button and search in the array of read items from the database
    QStringList FIO = button->text().split(" ");
    for (int i = 0; i < allData.size(); ++i)
    {
        if (allData[i].first->GetName() == FIO[1] && allData[i].first->GetSurname() == FIO[0])
        {
            emit visitka(allData[i], i + 1);
            return;
        }
    }

    // If don't found -> send 0
    emit visitka({}, 0);
}



