#include "mainwindow.h"

#include "csvreader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new QDeclarativeView;
    ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    //Находим корневой элемент
    Root = ui->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент window
    ui->rootContext()->setContextProperty("window", this);


     QList<QObject*> dataList;
     dataList.append(new ModelItem("23 March", 5));
     dataList.append(new ModelItem("24 March", 6));
     dataList.append(new ModelItem("25 March", 7));
     dataList.append(new ModelItem("26 March", 8));

     QDeclarativeContext *ctxt = ui->rootContext();
     ctxt->setContextProperty("mModel", QVariant::fromValue(dataList));
}

void MainWindow::FunctionC()
{
    //Найдем строку ввода
    QObject* textinput = Root->findChild<QObject*>("textinput");

    //Найдем поле вывода
    QObject* memo = Root->findChild<QObject*>("memo");

    QString str;//Создадим новую строковую переменную

    //Считаем информацию со строки ввода через свойство text
    str=(textinput->property("text")).toString();

    int a;
    a=str.toInt();//Переведем строку в число
    a++;//Добавим к числу 1

    QString str2;//Создадим еще одну строковую переменную
    str2=QString::number(a);//Переведем число в строку

    //Ну и наконец выведем в поле вывода нашу информацию
    memo->setProperty("text", str+"+1="+str2);


    //Max Code
    //Here Must be some smart search of csv files and reading it
    QList<QObject*> table = CSVReader::Read("Adobe.txt");
    //This table must be viewed on qml view
}

MainWindow::~MainWindow()
{
    delete ui;
}
