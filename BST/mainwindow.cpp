/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 *
 * This class is the main window - the GUI is build in this class and any other classes involved begin from this class.
 */

#include "mainwindow.h"
//#include "bst_about_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStringListIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Create default save directory
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    //this->bst = this->getBST();
    bst = new BinarySearchTree<int>;
    //this->createMenu();

    // Build buttons and layout for buttons on the bottom of the window
    propertyButton = new QPushButton("&Свойства", this);
    deleteButton = new QPushButton("&Удалить", this);
    insertButton = new QPushButton("&Вставить", this);
    Balancing = new QPushButton("&Балансировка", this);
    //zoomOutButton = new QPushButton("&Отдалить", this);
    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    // Set properties of buttons
    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Balancing->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //zoomOutButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    insertValueLineEdit->setFixedWidth(200);
    //insertValueLineEdit->setToolTip("Введите одно значение");

    deleteValueLineEdit->setFixedWidth(100);
    //deleteValueLineEdit->setToolTip("Enter value to delete");

    // Connect the slots to the button signals
    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(Balancing, SIGNAL(clicked()), this, SLOT(BalancingClicked()));
    //connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    // Create button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(Balancing);
    //buttonLayout->addWidget(zoomOutButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);

    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
    treeScrollArea->installEventFilter(renderArea);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(400);
    this->setWindowTitle("Двоичное дерево");
    //this->showMaximized();

    // Create secondary windows (but do not display them)
    prop = new BST_Properties_Window();
    //about = new BST_About_Window();

    // must show window before loading settings
    this->show();
    //this->loadSettings();

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->renderArea->callRepaint();
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete propertyButton;
    delete deleteButton;
    delete insertButton;
    delete Balancing;
    //delete zoomOutButton;
    delete treeScrollArea;
    delete prop;
    //delete about;
    delete bst;
    delete centralWidget;
}

//void MainWindow::createMenu()
//{
//    this->createActions();

////    fileMenu = this->menuBar()->addMenu(tr("&File"));
////    fileMenu->addAction(loadAction);
////    fileMenu->addAction(saveAction);
////    fileMenu->addAction(exitAction);

////    editMenu = this->menuBar()->addMenu(tr("&Edit"));
////    editMenu->addAction(resetAction);
////    editMenu->addAction(changeNodeColorAction);
////    editMenu->addAction(changeBackgroundColorAction);
////    editMenu->addAction(changeTextColorAction);

//    this->menuBar()->addAction(aboutAction);
//}

//void MainWindow::createActions()
//{
    //aboutAction = new QAction(tr("&About"), this);
    //aboutAction->setStatusTip("About Binary Search Tree Visualization");
    //connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutMenu);

    //loadAction = new QAction(tr("&Load"), this);
    //loadAction->setStatusTip("Load a BST from a file");
    //connect(loadAction, &QAction::triggered, this, &MainWindow::loadFileMenu);

    //saveAction = new QAction(tr("&Save"), this);
    //saveAction->setStatusTip("Save a BST to a file");
    //connect(saveAction, &QAction::triggered, this, &MainWindow::saveMenu);

//    exitAction = new QAction(tr("&Exit"), this);
//    exitAction->setStatusTip("Exit the application");
//    connect(exitAction, &QAction::triggered, this, &MainWindow::exitMenu);

//    resetAction = new QAction(tr("&Reset"), this);
//    resetAction->setStatusTip("Reset the BST to be empty");
//    connect(resetAction, &QAction::triggered, this, &MainWindow::resetMenu);

//    changeNodeColorAction = new QAction(tr("&Node color"), this);
//    changeNodeColorAction->setStatusTip("Change Node Color");
//    connect(changeNodeColorAction, &QAction::triggered, this, &MainWindow::changeNodeColorMenu);

//    changeBackgroundColorAction = new QAction(tr("&Background color"), this);
//    changeBackgroundColorAction->setStatusTip("Change Background Color");
//    connect(changeBackgroundColorAction, &QAction::triggered, this, &MainWindow::changeBackgroundColorMenu);

//    changeTextColorAction = new QAction(tr("Node &text color"), this);
//    changeTextColorAction->setStatusTip("Change Node Text Color");
//    connect(changeTextColorAction, &QAction::triggered, this, &MainWindow::changeTextColorMenu);

//}

void MainWindow::closeEvent(QCloseEvent *event)
{

    // Save BST before closing
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QString text = bst->getPreOrderTraversal();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
    }
    //this->saveSettings();

    prop->closePropertyWindow(); // close property window
    //about->close(); // close about window
    event->setAccepted(true); // set whether to close application or not
    return;
}

// Slot for property button
void MainWindow::propertyClicked() const
{
    // show and update the properties gui
    prop->show();
    prop->update(this->bst);
    return;
}

// Slot for delete button
void MainWindow::deleteClicked() const {
    QString value = deleteValueLineEdit->text();

    if(!this->bst->deleteItem(value.toInt()))
        this->statusLabel->setText("Значения нет");
    else
        this->statusLabel->setText("Значение удалено");

    this->renderArea->repaint(); // repaint to show changes to tree
    this->deleteValueLineEdit->setText(""); // clear text box
    return;
}

// Slot for insert button
void MainWindow::insertClicked() const
{
    // Get entire line of text and iterate through the list of
    // values separated by whitespace - inserting all the values
    QString values = insertValueLineEdit->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt())) // inserts 0 if text isn't an int
            this->statusLabel->setText("Значение уже есть");
        else
            this->statusLabel->setText("Значение введено");
    }
    this->renderArea->repaint(); // repaint to show changes to tree
    insertValueLineEdit->setText(""); // clear text box

    return;
}

void MainWindow::BalancingClicked() const {
    bst->balanceTree();
    this->renderArea->repaint();

}
