#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"passager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();



    void on_pb_modifier_clicked();

    void on_pb_tri_clicked();

    void on_pb_rech_clicked();

    void on_tab_passager_clicked(const QModelIndex &index);



    void on_pb_impri_clicked();

    void on_pushButton_clicked();

    void on_pb_web_clicked();

private:
    Ui::MainWindow *ui;
    Passager P;
};
#endif // MAINWINDOW_H
