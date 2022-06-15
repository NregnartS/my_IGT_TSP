#ifndef GROUP_H
#define GROUP_H

#include"unit.h"
#include<algorithm>
#include <iostream>
#include <fstream>
#include <QThread>
#include <QtConcurrent/QtConcurrentRun>

class Group:public QThread										//种群类
{
     Q_OBJECT
private:
    Unit best;										//当前种群最优个体
    int bestGen;									//演化过程中最优世代
    int genStop=0;									//停止演化时的代数
    int cityNumber;											//城市数量
    int unitNumber;											//群体拥有个体数量
    double persent;													//变异几率
    int genmax;												//最大代数
    double vM;													//临界速度
    double v;															//演化速度
    double mappingPersent;											//映射概率
    Unit officalBest;
    std::vector<Unit> someBest;
    std::vector<int> someGen;
    std::vector<Unit> group;								//个体数组构成种群
    //距离矩阵
    std::vector<std::vector<double>> length;
    //城市坐标数据
    std::vector<std::vector<double>> position;
    std::vector<std::vector<int>> adjacencyMatrix;
    //优化算子用到的一个小工具，优化代码结构时可以直接丢到private或者优化算子函数里
    bool isRpt(const std::vector<int>& s1);

public:
    //构造函数
    Group(){};
    Group(int cn, int un, int p1, int gm, int vm, int v1, int p2);
    Group(const Group&tg);
    //计算当前种群内各个个体的价值（距离）并设置当前种群最优个体
    void singleValue();

    int find_c(const Unit &M, int c);

    bool judgeAdjacent(int one,int two);
    //杂交算子
    //void cross(Unit& S,const Unit& M,int c);
    //变异算子
    //void mutation(Unit& t, int one);

    //映射算子
    void mapping(Unit &s1,const Unit& s2);

    //优化算子
    void optimize(Unit& s1,const Unit &s2);

    //演化
    void evolution();

    Group& operator=(const Group& tg);

    void printParameters();

    bool getBestAns(std::string path);

//    void output();

    virtual void run();

    std::vector<int> getSomeGen(){return this->someGen;}

    std::vector<Unit> gestSomeBest(){return this->someBest;}

    void caculateValue(Unit &u);

    void setLength(std::vector<std::vector<double>> l);

    void setPos(std::vector<std::vector<double>> pos){this->position=pos;}

signals:
    void textChanged(QString);
};

#endif // GROUP_H
