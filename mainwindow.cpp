#include "mainwindow.h"

#include "csvreader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new QDeclarativeView;
    ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    Root = ui->rootObject();
    ui->rootContext()->setContextProperty("window", this);


     //dataList.append(new ModelItem("23 March", 5));
     //dataList.append(new ModelItem("24 March", 6));
     //dataList.append(new ModelItem("25 March", 7));
     //dataList.append(new ModelItem("26 March", 8));
    dataList = CSVReader::Read(":/Adobe.csv");

     QDeclarativeContext *ctxt = ui->rootContext();
     ctxt->setContextProperty("mModel", QVariant::fromValue(dataList));
}

void MainWindow::FunctionC()
{
    //QObject* textinput = Root->findChild<QObject*>("textinput");
    //str=(textinput->property("text")).toString();
    //memo->setProperty("text", str+"+1="+str2);


    //Max Code
    //Here Must be some smart search of csv files and reading it
    //QList<QObject*> table = CSVReader::Read("Adobe.txt");
    //This table must be viewed on qml view
}

MainWindow::~MainWindow()
{
    delete ui;
}
