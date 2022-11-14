#include "passager.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

Passager::Passager()
{
numpass=0;billet=0;bag=0;
nom="";prenom="";dest="";classe="";
}
Passager::Passager(QString nom,QString prenom ,int numpass,QString dest ,QString classe,int billet,int bag)
{this->nom=nom ; this->prenom=prenom; this->numpass=numpass; this->dest=dest ; this->classe=classe; this->billet=billet; this ->bag=bag;}
int Passager::getnumpass()
{return numpass;}
int Passager::getbillet()
{return billet;}
int Passager::getbag()
{return bag;}
QString Passager::getnom()
{return nom;}
QString Passager::getprenom()
{return prenom;}
QString Passager::getdest()
{return dest;}
QString Passager::getclasse()
{return classe;}
void Passager::setnumpass(int numpass)
{this->numpass=numpass;}
void Passager::setbillet(int billet)
{this->billet=billet;}
void Passager::setbag(int bag)
{this->bag=bag;}
void Passager::setnom(QString nom)
{this->nom=nom;}
void Passager::setprenom(QString prenom)
{this->prenom=prenom;}
void Passager::setdest(QString dest)
{this->dest=dest;}
void Passager::setclasse(QString classe)
{this->classe=classe;}

bool Passager::ajouter()
{

    QSqlQuery query;
        QString numpass_string= QString::number(numpass);
        QString billet_string= QString::number(billet);
        QString bag_string= QString::number(bag);

          query.prepare("INSERT INTO PASSAGER (numpass, bag, prenom,classe,nom,dest,billet) "
                        "VALUES (:NUMPASS, :BAG, :PRENOM, :CLASSE, :NOM, :DEST, :BILLET)");
          query.bindValue(":NUMPASS", numpass_string);
          query.bindValue(":BAG",bag_string );
          query.bindValue(":PRENOM", prenom);
          query.bindValue(":CLASSE", classe);
          query.bindValue(":NOM", nom);
          query.bindValue(":DEST", dest);
          query.bindValue(":BILLET", billet_string);


    return query.exec();
}
bool Passager::supprimer(int numpass)
{
    QSqlQuery query;
    query.prepare("Delete from passager where numpass=:numpass");
    query.bindValue(0, numpass);



  return query.exec();
}

QSqlQueryModel *Passager::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT * FROM passager");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero passeport"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Destination"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Classe"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Billet"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Bagages"));

        return model;

}
bool Passager::modifier()

{
QSqlQuery query;
//QString up=QString();
QString numpass_string= QString::number(numpass);
QString billet_string= QString::number(billet);
QString bag_string= QString::number(bag);


//preparation de la requette

query.prepare("update  PASSAGER set BAG=:BAG, PRENOM=:PRENOM, CLASSE=:CLASSE, NOM=:NOM, DEST=:DEST, BILLET=:BILLET where NUMPASS=:NUMPASS");
//creation des variables liée

query.bindValue(":NUMPASS", numpass_string);
query.bindValue(":BAG",bag_string );
query.bindValue(":PRENOM", prenom);
query.bindValue(":CLASSE", classe);
query.bindValue(":NOM", nom);
query.bindValue(":DEST", dest);
query.bindValue(":BILLET", billet_string);


return query.exec();//retourner la resultat d execution

}

