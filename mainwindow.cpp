#include "mainwindow.h"

#include "csv.h"
#include "csv.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mp_ui(new QDeclarativeView)
{
    mp_ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(mp_ui);
    mp_ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    mp_root = mp_ui->rootObject();
    mp_ui->rootContext()->setContextProperty("window", this);

    _FormModel();

    if(m_model.HasCompanies())
    {
        QDeclarativeContext *p_ctxt = mp_ui->rootContext();
        p_ctxt->setContextProperty("mModel", QVariant::fromValue(m_model.GetListOfCompanies()[0]->GetListOfObjectItems()));
    }
}

void MainWindow::FunctionC()
{
}

void MainWindow::_FormModel()
{
    QList<QString> csv_files = CSV::Find(QDir::root());
    for(int i = 0; i<csv_files.size(); ++i)
    {
        ModelCompany* p_company = new ModelCompany();
        CSV::Read(*p_company, csv_files[i]);
        m_model.AddCompany(p_company);
    }
}

MainWindow::~MainWindow()
{
    delete mp_ui;
}
