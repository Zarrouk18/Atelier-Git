#ifndef PASSAGER_H
#define PASSAGER_H
#include <QString>
#include <QSqlQueryModel>

#include <QtCharts>
#include <QChartView>
#include <QLegend>
#include <QPieSeries>
#include <QPieSlice>



class Passager
{
public:
    Passager();
    Passager(QString,QString,int,QString,QString,int,int);
    int getnumpass();
    int getbillet();
    int getbag();
    QString getnom();
    QString getprenom();
    QString getdest();
    QString getclasse();
    void setnumpass(int);
    void setbillet(int);
    void setbag(int);
    void setnom(QString);
    void setprenom(QString);
    void setdest(QString);
    void setclasse(QString);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int numpass);

    bool modifier();


private:
    int numpass,billet,bag;
    QString nom,prenom,dest,classe ;
};

#endif // PASSAGER_H
