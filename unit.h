#ifndef UNIT_H
#define UNIT_H

#include<vector>

#pragma execution_character_set("utf-8")

class Unit											//个体类
{
private:
    double value;										//个体价值
    std::vector<int> path;
public:
    //构造函数
    Unit();

    //带路径的构造函数
    Unit(const std::vector<int>& tp);

    //获取当前个体价值
    double getValue() const {return this->value;};

    //设置当前个体价值
    void setValue(double v){this->value=v;}

    //获取该个体路径
    std::vector<int> getPath() const {return this->path;}

    //设置该个体路径
    void setPath(const std::vector<int>& tp){this->path=tp;}
};



#endif // UNIT_H
