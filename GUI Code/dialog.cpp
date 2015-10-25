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

//    // create empty bar chart objects:
//    QCPBars *postBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
//    QCPBars *underBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
//    QCPBars *continBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);
//    QCPBars *otherBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);

//    ui->bar_graph->addPlottable(postBar);
//    ui->bar_graph->addPlottable(underBar);
//    ui->bar_graph->addPlottable(continBar);
//    ui->bar_graph->addPlottable(otherBar);

//    // set names and colors:
//    QPen pen;
//    pen.setWidthF(1.2);
//    totHours->setName("Total Hours");
//    pen.setColor(QColor(255, 131, 0));
//    totHours->setPen(pen);
//    totHours->setBrush(QColor(255, 131, 0, 50));

//    // prepare x axis with country labels:
//    QVector<double> ticks;
//    QVector<QString> labels;
//    ticks << 1 << 2 << 3 << 4;
//    labels << "Undergraduate Education" << "Continuing Education" << "Post Education" << "Other" ;
//    ui->bar_graph->xAxis->setAutoTicks(true);
//    ui->bar_graph->xAxis->setAutoTickLabels(true);
//    ui->bar_graph->xAxis->setTickVector(ticks);
//    ui->bar_graph->xAxis->setTickVectorLabels(labels);
//    //ui->bar_graph->xAxis->setTickLabelRotation(60);
//    //ui->bar_graph->xAxis->setSubTickCount(0);
//    //ui->bar_graph->xAxis->setTickLength(0, 4);
//    ui->bar_graph->xAxis->grid()->setVisible(true);
//    //ui->bar_graph->xAxis->setRange(0, 8);

//    // prepare y axis:
//    ui->bar_graph->yAxis->setAutoTicks(true);
//    ui->bar_graph->yAxis->setAutoTickLabels(true);
//    //ui->bar_graph->yAxis->setRange(0, 12.1);
//    ui->bar_graph->yAxis->setPadding(5); // a bit more space to the left border
//    ui->bar_graph->yAxis->setLabel("Total Hours of Teaching");
//    ui->bar_graph->yAxis->grid()->setSubGridVisible(true);
//    QPen gridPen;
//    gridPen.setStyle(Qt::SolidLine);
//    gridPen.setColor(QColor(0, 0, 0, 25));
//    ui->bar_graph->yAxis->grid()->setPen(gridPen);
//    gridPen.setStyle(Qt::DotLine);
//    ui->bar_graph->yAxis->grid()->setSubGridPen(gridPen);

//            // Add data:
//            Summary	grabber = new Summary();

//            QVector<year> underVec= grabber.summaryFill("Undergraduate Education",2010,2015);
//            QVector<year> continuingVec= grabber.summaryFill("Continuing education",2010,2015);
//            QVector<year> postVec= grabber.summaryFill("Postgraduate Education",2010,2015);
//            QVector<year> otherVec= grabber.summaryFill("other",2010,2015);

//            int postTot = 0;
//            int underTot = 0;
//            int continTot = 0;
//            int otherTot = 0;

//            for (int curYear = 2010; curYear < 2015; curYear++){

//                postTot+= postVec[i].totHours;
//                underTot+= underVec[i].totHours;
//                continTot+= continuingVec[i].totHours;
//                otherTot+= otherVec[i].totHours;

//            }

//   // fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;

//    postBar->setData(ticks, postTot);
//    underBar->setData(ticks, underTot);
//    continBar->setData(ticks, continTot);
//    otherBar->setData(ticks, otherTot);

//    // setup legend:
//    ui->bar_graph->legend->setVisible(true);
//    ui->bar_graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
//    ui->bar_graph->legend->setBrush(QColor(255, 255, 255, 200));
//    QPen legendPen;
//    legendPen.setColor(QColor(130, 130, 130, 200));
//    ui->bar_graph->legend->setBorderPen(legendPen);
//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    ui->bar_graph->legend->setFont(legendFont);
//    ui->bar_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
