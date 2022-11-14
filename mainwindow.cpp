#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passager.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>
#include <QAxObject>
#include <QDesktopServices>
#include <QUrl>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_num_pass->setValidator(new QIntValidator(0,9999999,this));
    ui->le_billet->setValidator(new QIntValidator(0,9999999,this));
    ui->le_bag->setValidator(new QIntValidator(0,9999999,this));
    ui->le_num_pass_2->setValidator(new QIntValidator(0,9999999,this));
    ui->le_billet_2->setValidator(new QIntValidator(0,9999999,this));
    ui->le_bag_2->setValidator(new QIntValidator(0,9999999,this));

    ui->tab_passager->setModel(P.afficher());



    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());

        ui->web->dynamicCall("Navigate(const QString&)", "https://fr.flightaware.com/live/");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    int numpass=ui->le_num_pass->text().toInt();
    int billet=ui->le_billet->text().toInt();
    int bag=ui->le_bag->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString dest=ui->la_dest->text();
    QString classe=ui->classe->currentText();

Passager P(nom,prenom,numpass,dest,classe,billet,bag);
bool test=P.ajouter();
if (test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""click cancel to exit."),QMessageBox::Cancel);
    ui->tab_passager->setModel((P.afficher()));
    }
    else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Ajout non effectué\n""click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_pb_supp_clicked()
{
    Passager P1;
    P1.setnumpass(ui->le_id_supp->text().toInt());
    bool test=P1.supprimer(P1.getnumpass());
     QMessageBox msgbox;
     if (test)
    { msgbox.setText("Success");
     ui->tab_passager->setModel(P1.afficher());}
     else msgbox.setText("echec");
     msgbox.exec();


}

void MainWindow::on_pb_modifier_clicked()
{


    int numpass=ui->le_num_pass_2->text().toInt();
    int billet=ui->le_billet_2->text().toInt();
    int bag=ui->le_bag_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    QString dest=ui->la_dest_2->text();
    QString classe=ui->classe_2->currentText();

Passager P(nom,prenom,numpass,dest,classe,billet,bag);
    bool test=P.modifier();
    if (test)
    {
                 QMessageBox::information(nullptr, QObject::tr(" OK"),
                             QObject::tr("UPDATE successful.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
                 ui->tab_passager->setModel(P.afficher());

              }
              else
              {
                 QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                             QObject::tr("UPDATE failed.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

              }
 ui->tab_passager->setModel(P.afficher());
}


void MainWindow::on_pb_tri_clicked()
{
    QSqlQuery qry;
    qry.prepare("select * from PASSAGER ORDER BY NOM ");
    if (qry.exec())
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery(qry);
        ui->tab_passager->setModel(model);
    }
    else
    {
        QMessageBox::warning(this,"edit","error");
    }


}

void MainWindow::on_pb_rech_clicked()
{
    QSqlQuery qry;
   int numpass=ui->num_pass_rech->text().toInt();
   qry.prepare("select *from PASSAGER where NUMPASS=:NUMPASS");
   qry.bindValue(":NUMPASS",numpass);
   if(qry.exec())
   {


       QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery(qry);
       ui->tab_passager->setModel(model);
   }
   else
   {
       QMessageBox::warning(this,"edit","error");
   }

}


void MainWindow::on_tab_passager_clicked(const QModelIndex &index)
{
    QString numpass=ui->tab_passager->model()->data(index).toString();
     QSqlQuery qry;
     qry.prepare("select * from PASSAGER where NUMPASS=:NUMPASS");
     qry.bindValue(":NUMPASS",numpass);
     if (qry.exec())
     {
         while(qry.next())
         {


             QString s=("numero passeport: "+qry.value(0).toString()+"\n""Nom: "+qry.value(4).toString()+"\n""Prenom: "+qry.value(2).toString()+"\n""Destination: "+qry.value(5).toString()+"\n""Classe: "+qry.value(3).toString()+"\n""Billet: "+qry.value(6).toString()+"\n""Bagages: "+qry.value(1).toString());
             ui->tab_pdf->setText(s);
         }
     }
         else
         {
            QMessageBox::warning(this,"error","no information");
         }
}



void MainWindow::on_pb_impri_clicked()
{
    QPrinter printer;
    printer.setPrinterName("fichier");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected)
    {

        return ;
    }
    else
        ui->tab_pdf->print(&printer);
}


void MainWindow::on_pushButton_clicked()
{

    QSqlQuery q1,q2,q3,q4;
        qreal tot=0,c1=0,c2=0,c3=0;

        q1.prepare("SELECT * FROM PASSAGER");

        if(q1.exec())
        {
          while (q1.next())
          {
              tot++;
          }
        }

        q2.prepare("SELECT * FROM PASSAGER WHERE CLASSE='First'");
        if(q2.exec())
        {
          while (q2.next())
          {
              c1++;
          }

        }

        q3.prepare("SELECT * FROM PASSAGER WHERE CLASSE='Business'");
        if(q3.exec())
        {
          while (q3.next())
          {
              c2++;
          }
        }

        q4.prepare("SELECT * FROM PASSAGER WHERE CLASSE='Eco' ");
        if(q4.exec())
        {
          while (q4.next())
          {
              c3++;
          }
        }


        c1=c1/tot;
        c2=c2/tot;
        c3=c3/tot;

            QPieSeries *series = new QPieSeries();
            series->append("First classe ",c1);
            series->append("Business Classe",c2);
            series->append("Economic Classe",c3);
            QPieSlice *slice0 = series->slices().at(0);
                        slice0->setExploded();
                        slice0->setLabelVisible();
                        slice0->setPen(QPen(Qt::darkGray, 2));
                        slice0->setBrush(Qt::gray);
            QPieSlice *slice1 = series->slices().at(1);
                        slice1->setExploded();
                        slice1->setLabelVisible();
                        slice1->setPen(QPen(Qt::darkRed, 2));
                        slice1->setBrush(Qt::red);
            QPieSlice *slice2 = series->slices().at(2);
                        slice2->setExploded();
                        slice2->setLabelVisible();
                        slice2->setPen(QPen(Qt::darkYellow, 2));
                        slice2->setBrush(Qt::yellow);
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("STATS");
            chart->setAnimationOptions(QChart::AllAnimations);
            chart->legend()->hide();
            QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        QGridLayout *layout = new QGridLayout();
                        layout->addWidget(chartView);
                        ui->stat->setLayout(layout);

}


void MainWindow::on_pb_web_clicked()
{
    QString link="https://fr.flightaware.com/live/";
    QDesktopServices ::openUrl(QUrl(link));
}
