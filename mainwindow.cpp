#include "mainwindow.h"

#include "csv.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mp_ui(new QDeclarativeView)
{
    mp_ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(mp_ui);
    mp_ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mp_root = mp_ui->rootObject();
    mp_ui->rootContext()->setContextProperty("window", this);

    _FormModel();

    /*
    if(m_model.IsValid())
    {
        QDeclarativeContext *p_ctxt = mp_ui->rootContext();
        p_ctxt->setContextProperty("mModel", QVariant::fromValue(m_model.GetListOfCompanies()[0]->GetListOfObjectItems()));
    }
    */
}

void MainWindow::FunctionC()
{
}

void MainWindow::_FormModel()
{
    /*QDir dir(QDir::currentPath());
    QVector<QString> csv_files = CSV::Find(dir);
    //QObject* p_memo = mp_root->findChild<QObject*>("memo");
    //p_memo->setProperty("text", QVariant::fromValue(dir.path()));
    for(int i = 0; i<csv_files.size(); ++i)
    {
        DataCompany* p_company = CSV::Read(csv_files[i]);
        m_model.AddCompany(p_company);
    }
    */
}

MainWindow::~MainWindow()
{
    delete mp_ui;
}
