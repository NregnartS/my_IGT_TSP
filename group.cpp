#include "group.h"

bool Group::isRpt(const std::vector<int>& s1){
    std::vector<bool> hash(cityNumber, false);
    for (int i = 0; i < (int)s1.size(); i++) {
        if (hash[s1[i]] == true)
            return true;
        hash[s1[i]] = true;
    }
    return false;
}

Group::Group(const Group &tg){
    if(this!=&tg){
        this->group=tg.group;
        this->best=tg.best;
        this->bestGen=tg.bestGen;
        this->cityNumber=tg.cityNumber;
        this->unitNumber=tg.unitNumber;
        this->persent=tg.persent;
        this->genmax=tg.genmax;
        this->vM=tg.vM;
        this->v=tg.v;
        this->mappingPersent=tg.mappingPersent;
        this->someBest=tg.someBest;
        this->someGen=tg.someGen;
        this->length=tg.length;
        this->position=tg.position;
        this->adjacencyMatrix = tg.adjacencyMatrix;
    }
}

Group& Group::operator=(const Group &tg){
    if(this!=&tg){
        this->group=tg.group;
        this->best=tg.best;
        this->bestGen=tg.bestGen;
        this->cityNumber=tg.cityNumber;
        this->unitNumber=tg.unitNumber;
        this->persent=tg.persent;
        this->genmax=tg.genmax;
        this->vM=tg.vM;
        this->v=tg.v;
        this->mappingPersent=tg.mappingPersent;
        this->someBest=tg.someBest;
        this->someGen=tg.someGen;
        this->length = tg.length;
        this->position = tg.position;
        this->adjacencyMatrix = tg.adjacencyMatrix;
    }
    return *this;
}

Group::Group(int cn, int un, int p1, int gm, int vm, int v1, int p2)
    :bestGen(0)
    ,cityNumber(cn),unitNumber(un),persent(p1),genmax(gm),vM(vm),v(v1),mappingPersent(p2)
    ,someBest(0),someGen(0),group(un)
{
    this->best.setValue(0x3f3f3f3f);
    for (int i = 0; i < un; i++)
    {
        std::vector<bool> flag(cn, false);
        std::vector<int> pt(cn,0);
        for (int j = 0; j < cn; j++)	//随机生成cityNumber个个体并填充路径
        {
            int tCity = rand() % cn;
            while (flag[tCity])
                tCity = rand() % cn;
            flag[tCity] = true;
            pt[j] = tCity;
        }
        this->group[i].setPath(pt);
    }
    //初始化各参数
}

void Group::singleValue(){
    for (int k = 0; k < this->unitNumber; k++)
    {
        caculateValue(this->group[k]);
        if (this->best.getValue() > this->group[k].getValue())
            this->best = this->group[k];
    }
}

int Group::find_c(const Unit &M, int c){
    int _c=0;
    std::vector<int> mother=M.getPath();
    for(int i=0;i<cityNumber;i++){
        if(c==mother[i]){
            if(i!=cityNumber-1)
                _c=mother[i+1];
            else
                _c=mother[0];
        }
    }
    return _c;
}

bool Group::judgeAdjacent(int one,int two){
    if(one>0&&one<cityNumber-1){
        if(two==one+1||two==one-1)
            return true;
        return false;
   }else if(one==0){
        if(two==one+1||two==cityNumber-1)
            return true;
        return false;
    }else if(one==cityNumber-1){
        if(two==one-1||two==0)
            return true;
        return false;
    }
    return false;
}

//void Group::cross(Unit &F, const Unit &M, int c){
//   int r = 0;
//    std::vector<int> father=F.getPath(),mother=M.getPath();
//    for (int i = 0; i < cityNumber; i++) {
//        if (father[i] == mother[l]) {
//            if (i != cityNumber-1)
//                r =mother[i + 1];			//找到母个体中与父个体C相邻的基因C'
//            else
//                r =mother[0];
//        }
//    }
//    for (int i = 0; i < cityNumber; i++) {
//        if (father[i] == r)					//找到父个体中的C'
//        {
//            if (i < l)
//                std::swap(i, l);
//            if(i!=l+1)
//                reverse(father.begin() + l, father.begin() + i + 1);
//            break;
//        }
//    }
//    F.setPath(father);
//    caculateValue(F);
//}

//void Group::mutation(Unit &t, int one){
//    int two = rand() % cityNumber;
//    while (two == one)
//        two = rand() % cityNumber;
//    if (one > two)
//        std::swap(one, two);
//    std::vector<int> tp=t.getPath();
//    reverse(tp.begin() + one,tp.begin() + two + 1);
//    t.setPath(tp);
//    caculateValue(t);
//}

void Group::mapping(Unit &s1, const Unit &s2){
    int one = rand() % cityNumber;
    int two = rand() % cityNumber;
    while (two == one || abs(two - one) == 1)
        two = rand() % cityNumber;
    if (one > two)
        std::swap(one, two);
    int length = two - one;
    std::vector<int> sp1=s1.getPath(),sp2=s2.getPath();
    for (int i = 0; i < cityNumber; i++) {
        if (sp2[i] == sp1[one]) {
            if (cityNumber - i >= length) {
                std::vector<int> temp1(length, 0);
                std::vector<int> temp2 = temp1;
                copy(sp1.begin() + one, sp1.begin() + two, temp1.begin());			//建立映射表
                copy(sp2.begin() + i, sp2.begin() + i + length, temp2.begin());
                copy(temp2.begin(), temp2.end(), sp1.begin() + one);					//交换对应基因片段
                do {
                    for (int j = 1; j < length; j++) {
                        for (int k = 0; k < cityNumber; k++) {
                            if (temp2[j] == sp1[k] && (!(k >= one && k < two))) {
                                sp1[k] = temp1[j];
                            }
                        }
                    }
                } while (isRpt(sp1));		//按映射表消除全部重复基因
                s1.setPath(sp1);
                caculateValue(s1);
                return;
            }
            else return;//无满足条件的基因片段
        }
    }
}

void Group::optimize(Unit &s1, const Unit &s2){
    if (s1.getPath() == s2.getPath())
        return;
    int one = rand() % cityNumber;
    int two = rand() % cityNumber;
    while (two == one || abs(two - one) == 1)
        two = rand() % cityNumber;
    if (one > two)
        std::swap(one, two);
    int tlength = two - one;
    std::vector<bool> hash(cityNumber+1, false);
    std::vector<int> sp1=s1.getPath(),sp2=s2.getPath();
    for (int i = one; i < two; i++) {
        hash[sp1[i]] = true;
    }
    for (int i = 0; i < cityNumber - tlength + 1; i++) {//寻找是否有满足要求的基因片段
        bool flag = true;
        for (int j = i; j < i+tlength; j++) {
            if (!hash[sp2[j]]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            if (std::vector<int>(sp2.begin() + i, sp2.begin() + i + tlength) ==
                std::vector<int>(sp1.begin() + one, sp1.begin() + one + tlength))//保证S1，S2中选中的两段基因不一样
                return;
            std::vector<int> tp=sp1;
            copy(sp2.begin() + i, sp2.begin() + i + tlength, tp.begin() + one);
            double rel=0;
            for (int k = 1; k < cityNumber; k++)
                rel += length[tp[k - 1]][tp[k]];		//从第一个城市到最后一个城市的距离和
            rel += length[tp[cityNumber - 1]][tp[0]];		//最后一个城市到第一个城市成环的距离
            if (rel < s1.getValue()) {
                s1.setPath(tp);//复制更优个体中的基因片段
                s1.setValue(rel);
            }
            else
                return;
        }
    }
}

void Group::evolution(){
    int sameGen = 0;//用来判断有多少代最优个体已经无变化(陷入局部最优)
    singleValue();//计算每个个体适应度，并找出当前种群最优个体
    emit textChanged("初始种群最优解路径为：");
    QString pathS="";
    std::vector<int>tbp=best.getPath();
    for (int j = 0; j < cityNumber; j++)
        pathS+=QString::number(tbp[j]+1)+" ";
    emit textChanged(pathS);
    emit textChanged("总权值："+QString::number(best.getValue(),10,6)+"\n");
    double lastBestValue = best.getValue();//用于记录发生大幅度优化之前的最优值
    someBest.push_back(best);
    someGen.push_back(1);
    for (int i = 0; i < genmax; i++)					//最多演化genmax代
    {
        int kmax = cityNumber * i / genmax;
        double bestValue = best.getValue();				//记录演化前（上一代）的最优值
        for (int j = 0; j < unitNumber; j++) {			//IGT中3-8步，变异和交叉算子的使用
            Unit S=group[j];
            int one=rand()%cityNumber;
            int c=S.getPath()[one];
            int two=-1;
            int _c=-1;
            std::vector<bool> hash(cityNumber,false);
            int hashflag=0;
            while (true) {
                bool isVariation;
                if(rand()%100<=persent){
                    if (kmax <= 2)
                        two = 1;
                    else 
                        two=rand()%kmax;
                    while (two==0)
                        two = rand() % kmax;
 //                   while(two==one)
   //                     two=rand()%cityNumber;
                   // _c=S.getPath()[two];
                    _c = adjacencyMatrix[c][two];
                    isVariation=true;
                }
                else{
                    int randS=rand()%unitNumber;
                    while(randS==j)
                        randS=rand()%unitNumber;
                    _c=find_c(group[randS],c);
                    isVariation=false;
                }
                std::vector<int> STPATH=S.getPath();
                if(two==-1){
                    for(int i=0;i<cityNumber;i++){
                        if(STPATH[i]==_c)
                            two=i;
                    }
                }
                if(judgeAdjacent(one,two)&&!isVariation)
                    break;
                else{
                    if(one>two)
                        std::swap(one, two);
                    reverse(STPATH.begin()+one+1,STPATH.begin()+two+1);
                    S.setPath(STPATH);
                    caculateValue(S);
                    if(S.getValue()-group[j].getValue()<0&&v<vM&&!isVariation)
                        break;
                    if (hash[one] == false) {
                        hash[one] = true;
                        hashflag++;
                        if (i == cityNumber)
                            break;
                    }
                    c=_c;
                    one=two;
                    two=-1;
                    _c=-1;
                }
            }
            if(S.getValue()<=group[j].getValue())
                group[j]=S;
        }
//        for (int j = 0; j < unitNumber; j++) {			//IGT中3-8步，变异和交叉算子的使用
//            Unit S=group[j];
//            int one=rand()%cityNumber;
//            int c=S.getPath()[one];
//            int two=-1;
//            int _c=-1;
//            while (true) {
//                if(rand()%100<=persent){
//                    two=rand()%cityNumber;
//                    while(two==one)
//                        two=rand()%cityNumber;
//                    _c=S.getPath()[two];
//                }
//                else{
//                    int randS=rand()%unitNumber;
//                    while(randS==j)
//                        randS=rand()%unitNumber;
//                    _c=find_c(group[randS],c);
//                }
//                std::vector<int> STPATH=S.getPath();
//                if(two==-1){
//                    for(int i=0;i<cityNumber;i++){
//                        if(STPATH[i]==_c)
//                            two=i;
//                    }
//                }
//                if(judgeAdjacent(one,two))
//                    break;
//                else{
//                    if(one>two)
//                        std::swap(one, two);
//                    reverse(STPATH.begin()+one+1,STPATH.begin()+two+1);
//                    S.setPath(STPATH);
//                    caculateValue(S);
//                    if(S.getValue()-group[j].getValue()<0&&v<vM)
//                        break;
//                    c=_c;
//                    one=two;
//                    two=-1;
//                    _c=-1;
//                }
//            }
//            if(S.getValue()<=group[j].getValue())
//                group[j]=S;
//        }
        persent = persent * (1 - i * 0.01 / (genmax));//更新变异机率
        v = v * (1 - i * 0.01 / (genmax));	//更新演化速度
        //v = vM * genmax/i;
        //if (best.getValue() <= 0.98*lastBestValue)
            //v *= (best.getValue() / lastBestValue);
        int p = rand() % 100;
        if (v < vM && p <= mappingPersent) {										//映射算子
            int first = rand() % unitNumber;
            int second = rand() % unitNumber;
            while (second == first)
                second = rand() % unitNumber;
            (group[first].getValue() > group[second].getValue()) ?
                mapping(group[first], group[second]) : mapping(group[second], group[first]);
        }
        singleValue();//更新best
        if (v<vM) {
            for (int j = 0; j < unitNumber; j++) {			//优化算子
                optimize(best,group[j]);
            }
        }
        else {
            for (int j = 0; j < unitNumber; j++) {			//优化算子
                optimize(group[j],best);
            }
            singleValue();
        }
        /*
        if(best.getValue()-officalBest.getValue()<=0.001){
            bestGen=i;
            genStop=i;
            emit textChanged("已达到官方最优解！");
            someBest.push_back(best);
            someGen.push_back(i+1);
            break;
        }
        */
        if (best.getValue() - bestValue < 0) {	//更新最优世代数
            bestGen = i;
            sameGen = 0;
            if (best.getValue() < lastBestValue * 0.90) {
                someBest.push_back(best);
                someGen.push_back(i+1);
                emit textChanged( "第" +QString::number(bestGen + 1)+ "代最优个体大幅变化(最短路径为原来的90%以下)：\n路径为：");
                pathS="";
                tbp=best.getPath();
                for (int j = 0; j < cityNumber; j++)
                    pathS+=QString::number(tbp[j]+1)+" ";
                emit textChanged(pathS);
                emit textChanged("总权值："+QString::number(best.getValue(),10,6));
                lastBestValue = best.getValue();
                emit textChanged( "此时变异几率为："+QString::number( persent,10,6));
                emit textChanged( "此时演化速度为："+QString::number( v,10,6) +"\n");
            }
        }
        else if (best.getValue()- bestValue<=0.0001)
            sameGen++;
        /*if (sameGen >= genmax * 0.1) {
            v /= 2;
            vM /= 1.5;
        }*/
        
        if (cityNumber > 100) {
            if (sameGen >= genmax * 0.1||persent<0.001||v<0.001) {
                v = 1.5 * vM;
//                persent = 5;
                sameGen = 0;
            }
        }
        else {
            if (sameGen >= 0.3*genmax) {
                genStop = i;
                someBest.push_back(best);
                someGen.push_back(bestGen + 1);
                emit textChanged("最优个体不再变化，停止演化" );
                break;
            }
        }
        /*if (sameGen >= 0.3 * genmax) {
            genStop = i;
            emit textChanged("最优个体不再变化，停止演化");
            break;
        }*/
    }
    if (genStop == 0) {
        someBest.push_back(best);
        someGen.push_back(bestGen+1);
        emit textChanged( "达到最大演化代数！\n");
        genStop = genmax;
    }
}

void Group::printParameters(){
    emit textChanged( "初始参数：\n城市数量：" +QString::number( cityNumber ));
    emit textChanged("群体拥有个体数量：" +QString::number( unitNumber));
    emit textChanged( "最大代数：" +QString::number( genmax));
    emit textChanged("初始变异机率：" +QString::number( persent,10,6)+"%");
    emit textChanged("映射概率:"+QString::number( mappingPersent,10,6)+"%");
    emit textChanged("临界速度:" +QString::number( vM,10,6));
    emit textChanged("初始演化速度为：" +QString::number( v,10,6)+"\n");
}


bool Group::getBestAns(std::string path) {//读取并输出官方最优解
    std::ifstream ansFile(path);
    //读取并输出官方最优解
    if (ansFile.is_open())
        emit textChanged("读取官方最优解文件成功！\n");
    else {
        emit textChanged("读取官方最优解文件失败！\n");
        return false;
    }
    std::vector<int> bestPath(cityNumber);
    int temp = 0;
    int i = 0;
    while (!ansFile.eof()) {
        ansFile >> temp;
        bestPath[i++] = temp - 1;
    }
    Unit bestU(bestPath);
    caculateValue(bestU);
    emit textChanged("官方最优解：");
    QString pathS="";
    std::vector<int> tp=bestU.getPath();
    for (int j = 0; j < cityNumber; j++)
        pathS+=QString::number(tp[j]+1)+" ";
    emit textChanged(pathS);
    emit textChanged("总权值："+QString::number(bestU.getValue(),10,6)+"\n");
    this->officalBest=bestU;
    this->someBest.push_back(bestU);
    this->someGen.push_back(0);
    return true;
}

void Group::run(){
    using namespace std::chrono;
    auto start = system_clock::now();
    this->evolution();
    emit textChanged("本次求解最优路径：");
    QString pathS="";
    std::vector<int> tp=this->best.getPath();
    for (int j = 0; j < cityNumber; j++)
        pathS+=QString::number(tp[j]+ 1)+" ";
    emit textChanged(pathS);
    emit textChanged("总权值："+QString::number(this->best.getValue(),10,6));
    emit textChanged("与官方最优解差值为：" + QString::number(best.getValue() - officalBest.getValue(), 10, 6));
    emit textChanged("第"+QString::number(this->bestGen + 1)+ "代获得最优解");
    emit textChanged("停止代数："+QString::number(this->genStop + 1));
    duration<double> diff = system_clock::now() - start;
    emit textChanged("耗时："+QString::number(diff.count(),10,3)+ "s");
}

void Group::caculateValue(Unit &u){
    double rel=0;
    std::vector<int> tp=u.getPath();
    for (int i = 1; i < this->cityNumber; i++)
        rel += this->length[tp[i - 1]][tp[i]];			//从第一个城市到最后一个城市的距离和
    rel += this->length[tp[this->cityNumber - 1]][tp[0]];		//最后一个城市到第一个城市成环的距离
    u.setValue(rel);
}

void Group::setLength(std::vector<std::vector<double>> l) {
    this->length = l;
    int sz = l.size();
    for (int i = 0; i < sz; i++) {
        std::sort(l[i].begin(), l[i].end());
    }
    std::vector<std::vector<int>> temp(sz, std::vector<int>(sz));
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (j == 0)
                temp[i][j] = i;
            else {
                temp[i][j] = find(length[i].begin(), length[i].end(), l[i][j]) - length[i].begin();
            }
        }
    }
    this->adjacencyMatrix = temp;
}