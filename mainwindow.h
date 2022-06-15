#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextCodec>
#include <string>
#include <io.h>
#include <stdio.h>

#include"drawingboard.h"
#include"group.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::vector<std::vector<double>> length;
    std::vector<std::vector<double>> position;
    Ui::MainWindow *ui;
    drawingBoard newPicture;
    Group g;
    bool getDisMatrix(std::string path, std::vector<std::vector<double>>& dis,std::vector<std::vector<double>>& pos);
    void getFiles(std::string path,std::vector<std::string>& ans);
    QPainterPath caculatePath(Unit u,const std::vector<std::vector<double>> posi);

private slots:

    void on_getPathBtn_clicked();

    void on_startCltBtn_clicked();

    void on_getPicBtn_clicked();

};
#endif // MAINWINDOW_H
