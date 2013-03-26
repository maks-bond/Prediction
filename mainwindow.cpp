#include "mainwindow.h"

#include "csvreader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mp_ui(new QDeclarativeView)
{
    mp_ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(mp_ui);
    mp_ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mp_root = mp_ui->rootObject();
    mp_ui->rootContext()->setContextProperty("window", this);


     //dataList.append(new ModelItem("23 March", 5));
     //dataList.append(new ModelItem("24 March", 6));
     //dataList.append(new ModelItem("25 March", 7));
     //dataList.append(new ModelItem("26 March", 8));
    ModelCompany data_list;
    CSVReader::Read(data_list, ":/Adobe.csv");

    QDeclarativeContext *p_ctxt = mp_ui->rootContext();
    p_ctxt->setContextProperty("mModel", QVariant::fromValue(data_list.GetListOfObjectItems()));
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
    delete mp_ui;
}
