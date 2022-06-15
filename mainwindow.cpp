#include "mainwindow.h"
#include "ui_mainwindow.h"

//auto fwhile=[](Group &g)->void{
//        QFuture<void> future=QtConcurrent::run(g,&Group::output);
//        while(!future.isFinished()){
//            QApplication::processEvents(QEventLoop::AllEvents,1000);
//        }
//    };

QPainterPath MainWindow::caculatePath(Unit u,const std::vector<std::vector<double>> posi){
    double maxp;
    for(int i=0;i<(int)posi.size();i++){
        maxp=std::max(posi[i][0],maxp);
        maxp=std::max(position[i][1],maxp);
    }
    if(maxp>800){
        int standard=2;
        while(maxp/standard>800)
            standard++;
        QPainterPath ans;
        std::vector<int> tp=u.getPath();
        ans.moveTo(100+posi[tp[0]][0]/standard,100+posi[tp[0]][1]/standard);
        ans.addEllipse(100+posi[tp[0]][0]/standard-5,100+posi[tp[0]][1]/standard-5,10,10);
        ans.lineTo(100+posi[tp[0]][0]/standard,100+posi[tp[0]][1]/standard);
        for(int i=0;i<(int)tp.size();i++){
            double x=100+posi[tp[i]][0]/standard;
            double y=100+posi[tp[i]][1]/standard;
            ans.lineTo(x,y);
            ans.addEllipse(x-5,y-5,10,10);
            ans.lineTo(x,y);
        }
        return ans;
    }else{
        int standard=2;
        while(maxp*standard<800)
            standard++;
        standard--;
        QPainterPath ans;
        std::vector<int> tp=u.getPath();
        ans.moveTo(100+posi[tp[0]][0]*standard,100+posi[tp[0]][1]*standard);
        ans.addEllipse(100+posi[tp[0]][0]*standard-5,100+posi[tp[0]][1]*standard-5,10,10);
        ans.lineTo(100+posi[tp[0]][0]*standard,100+posi[tp[0]][1]*standard);
        for(int i=0;i<(int)tp.size();i++){
            double x=100+posi[tp[i]][0]*standard;
            double y=100+posi[tp[i]][1]*standard;
            ans.lineTo(x,y);
            ans.addEllipse(x-5,y-5,10,10);
            ans.lineTo(x,y);
        }
        return ans;
    }
}

bool MainWindow::getDisMatrix(std::string path, std::vector<std::vector<double> > &dis, std::vector<std::vector<double> > &pos){
    std::ifstream disFile(path);
    if (!disFile.is_open()){
        return false;
    }
    std::vector<double> date(0);
    double temp = 0;
    while (!disFile.eof()) {
        disFile >> temp;
        date.push_back(temp);
    }
    std::vector<std::vector<double>> posi(date.size()/3,std::vector<double>(2,0));
    for(int i=0,k=0;i<(int)posi.size();i++){
        k++;
        for(int j=0;j<2;j++){
            posi[i][j]=date[k++];
        }
    }
    std::vector<std::vector<double>> disMatrix(date.size() / 3, std::vector<double>(date.size() / 3, 0));
    for (int i = 0; i < (int)disMatrix.size(); i++) {
        for (int j = 0; j < (int)disMatrix.size(); j++) {
            if (i == j)
                disMatrix[i][j] = 0;
            else if (i > j)
                disMatrix[i][j] = disMatrix[j][i];
            else
                disMatrix[i][j] = sqrt(pow(date[(i + 1) * 3 - 2] - date[(j + 1) * 3 - 2], 2)
                    + pow(date[(i + 1) * 3 - 1] - date[(j + 1) * 3 - 1], 2));
        }
    }
    dis = disMatrix;
    pos=posi;
    return true;
}

void MainWindow::getFiles(std::string path,std::vector<std::string>& ans){
    intptr_t handle;
    struct _finddata_t fileInfo;
    handle=_findfirst(path.c_str(),&fileInfo);
    if(handle==-1){
        _findclose(handle);
        return ;
    }
    ans.push_back(fileInfo.name);
    while(_findnext(handle,&fileInfo)==0) {
        ans.push_back(fileInfo.name);
    }
    _findclose(handle);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("IGT-TSP");
    ui->startCltBtn->setEnabled(false);
    ui->getPicBtn->setEnabled(false);
    ui->pathEdit->setText("C:\\Users\\75851\\Desktop\\Graduation_project\\standardSet");
    this->newPicture.hide();
    connect(&g,SIGNAL(textChanged(QString)),ui->textBrowser,SLOT(append(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_getPathBtn_clicked()
{
    QString inPath=ui->pathEdit->text();
    if(inPath=="")
        QMessageBox::warning(this,tr("路径有误"),tr("路径不可为空！"),QMessageBox::Ok);
    else if(_access(inPath.toStdString().c_str(),0)==-1)
        QMessageBox::warning(this,tr("路径有误"),tr("路径格式错误或不存在！"),QMessageBox::Ok);
    else{
        std::vector<std::string> txtFiles(0);
        inPath+="\\*_question.txt";
        getFiles(inPath.toStdString(),txtFiles);
        if(txtFiles.size()==0)
            QMessageBox::warning(this,tr("路径有误！"),tr("该路径下无标准数据集！"),QMessageBox::Ok);
        else{
            for(int i=0;i<(int)txtFiles.size();i++)
                ui->testSetSlct->addItem(txtFiles[i].c_str());
            QMessageBox::about(this,tr("载入成功！"),tr("已加载该目录下所有合法数据集！"));
            ui->getPathBtn->setEnabled(false);
            ui->startCltBtn->setEnabled(true);
        }
    }
}


void MainWindow::on_startCltBtn_clicked()
{
    ui->startCltBtn->setEnabled(false);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    std::string fileName=ui->testSetSlct->currentText().toStdString();
    if(!getDisMatrix(ui->pathEdit->text().toStdString()+"\\"+fileName, this->length, this->position))
        QMessageBox::warning(this,tr("读取有误"),tr("文件读取失败！"),QMessageBox::Ok);
    else
        QMessageBox::about(this,tr("载入成功"),tr("已读取该标准集!"));
    this->g=Group((int)length.size(), 80, 5, 50*(int)length.size(), 20, 100, 5);
    //this->g = Group((int)length.size(), 80, 5, 30000, 20, 100, 5);
    g.setLength(this->length);
    g.setPos(this->position);
    //读取并输出官方最优解
    g.printParameters();
    for(int i=0;i<(int)fileName.size();i++){
        if(fileName[i]=='_'){
            std::string temp="_ans.txt";
            fileName.replace(i,13,temp);
        }
    }
    g.getBestAns(ui->pathEdit->text().toStdString()+"\\"+fileName);//读取最优解并加入画图数组
    g.start();
    while(!g.isFinished()){
              QApplication::processEvents(QEventLoop::AllEvents,1000);
           }
    QMessageBox::about(this,tr("DONE"),tr("计算完成！"));
    ui->pictureSlct->addItem("官方最优解路径图");
    std::vector<int> sg=g.getSomeGen();
    for(int i=1;i<(int)sg.size();i++){
        if(i==(int)(int)sg.size()){
            ui->pictureSlct->addItem("计算最优解路径图");
        }
        else{
            std::string temp="第"+std::to_string(sg[i])+"代路径图";
            ui->pictureSlct->addItem(temp.c_str());
        }
    }
    ui->getPicBtn->setEnabled(true);
}

void MainWindow::on_getPicBtn_clicked()
{
    this->newPicture.setUV(g.gestSomeBest()[ui->pictureSlct->currentIndex()].getValue());
    this->newPicture.setPath(caculatePath(g.gestSomeBest()[ui->pictureSlct->currentIndex()],this->position));
    this->newPicture.show();
    this->newPicture.update();
//    std::string v="该路径距离为："+std::to_string(g.gestSomeBest()[ui->pictureSlct->currentIndex()].getValue());
//    QMessageBox::about(this,tr("绘制成功！"),tr(v.c_str()));
}
