#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <glauber.h>

QString MathSymbolSigma(0x03C3);
QString MathSymbolOmega(0x03A9);
QString MathSymbolTheta(0x03B8);

void Processing_thread::run (void)
{
    Glauber Scattering;
    Result = Scattering.Cross_section_calculation((Energy)(Proton_energy), 60);
    qDebug()<<"Calculation Done!";

    emit Calculation_done();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/new/gifs/cookie_monster_waiting.gif");

    ui->gif_label->setMovie(movie);

    ui->gif_label->setScaledContents(true);
    movie->start();
    ui->gif_label->hide();


    ui->comboBox->addItem("47 MeV");
    ui->comboBox->addItem("180 MeV");


    ui->Plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    ui->Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //ui->Plot->addGraph();


    ui->Plot->yAxis->setLabel("d" + MathSymbolSigma + "/d" + MathSymbolOmega + ", mbarn");
    ui->Plot->xAxis->setLabel(MathSymbolTheta + ",deg");

    blackDotPen.setColor(Qt::darkCyan);
    blackDotPen.setStyle(Qt::DotLine);
    blackDotPen.setWidthF(1.5);



    //ui->Plot->hide();

    connect(&(this->Thread), SIGNAL(Calculation_done (void) ),this,SLOT( replot() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Thread.Set_energy( (ui->comboBox->currentIndex()) );
    Thread.start();

    ui->gif_label->show();

}

void MainWindow::replot (void)
{
    QVector <QVector <double> > Y = Thread.Get_Result();

    ui->gif_label->hide();

    //ui->Plot->show();

    ui->Plot->clearGraphs();
    ui->Plot->legend->clear();

    ui->Plot->legend->setVisible(true);
    ui->Plot->legend->setFont(QFont("Helvetica",9));

    ui->Plot->addGraph();
    ui->Plot->graph(0)->setData(Y[0],Y[1]);
    ui->Plot->graph(0)->setName("Coulomb");

    ui->Plot->addGraph();
    ui->Plot->graph(1)->setData(Y[0],Y[2]);
    ui->Plot->graph(1)->setName("Cross section");

    ui->Plot->addGraph();
    ui->Plot->graph(2)->setData(Y[0],Y[3]);
    ui->Plot->graph(2)->setName("Nuclear");

    ui->Plot->graph(1)->setPen(blackDotPen);
    ui->Plot->graph(0)->setPen(QPen(Qt::darkYellow));


    ui->Plot->rescaleAxes();
    ui->Plot->replot();
}
