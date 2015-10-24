#include "dialog.h"
#include "ui_dialog.h"

//This code actually generates the graph, look at this
//qcustomplot.cpp is supplied by qcustomplot, do not touch that
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Dialog::make_graph();
}

Dialog::~Dialog()
{
    delete ui;
}

//draws graph
void Dialog::make_graph()
{
    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
    QCPBars *nuclear = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
    QCPBars *fossil = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
    ui->bar_graph->addPlottable(regen);
    ui->bar_graph->addPlottable(nuclear);
    ui->bar_graph->addPlottable(fossil);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    fossil->setName("Fossil fuels");
    pen.setColor(QColor(255, 131, 0));
    fossil->setPen(pen);
    fossil->setBrush(QColor(255, 131, 0, 50));
    nuclear->setName("Nuclear");
    pen.setColor(QColor(1, 92, 191));
    nuclear->setPen(pen);
    nuclear->setBrush(QColor(1, 92, 191, 50));
    regen->setName("Regenerative");
    pen.setColor(QColor(150, 222, 0));
    regen->setPen(pen);
    regen->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
    ui->bar_graph->xAxis->setAutoTicks(false);
    ui->bar_graph->xAxis->setAutoTickLabels(false);
    ui->bar_graph->xAxis->setTickVector(ticks);
    ui->bar_graph->xAxis->setTickVectorLabels(labels);
    ui->bar_graph->xAxis->setTickLabelRotation(60);
    ui->bar_graph->xAxis->setSubTickCount(0);
    ui->bar_graph->xAxis->setTickLength(0, 4);
    ui->bar_graph->xAxis->grid()->setVisible(true);
    ui->bar_graph->xAxis->setRange(0, 8);

    // prepare y axis:
    ui->bar_graph->yAxis->setRange(0, 12.1);
    ui->bar_graph->yAxis->setPadding(5); // a bit more space to the left border
    ui->bar_graph->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    ui->bar_graph->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->bar_graph->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->bar_graph->yAxis->grid()->setSubGridPen(gridPen);

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
    nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
    nuclear->setData(ticks, nuclearData);
    regen->setData(ticks, regenData);

    // setup legend:
    ui->bar_graph->legend->setVisible(true);
    ui->bar_graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->bar_graph->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->bar_graph->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->bar_graph->legend->setFont(legendFont);
    ui->bar_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
