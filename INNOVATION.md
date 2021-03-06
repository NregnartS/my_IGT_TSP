# INNOVATION

## 基于IGT算法的一些修改与创新

## 1.优化算子

IGT算法在优化算子一步中，随机选取最优个体中的若干基因段，在种群中查找是否有满足特定条件的基因段，以最优个体为优化目标，使用种群中其他个体来对最优个体优化，加快收敛。然而这一步实际实现时，代码设计困难，基因段有效命中率低，强行提高命中率需要以提高计算量为代价，得不偿失，在本程序实际表现中很难真正达到加快收敛的目的。

本程序在设计优化算子时主要采用以下流程：

随机选取被优化个体中的一段基因段，在优化个体中查找是否有满足特定条件的基因段，若有则进行优化操作。并使用了自适应控制策略来调整优化算子的使用策略：演化速度大于收敛速度时（此时程序以Inver-over算子为主，主要进行解交叉操作），使用最优个体来优化全体种群，在演化速度小于收敛速度（以映射优化为主，主要进行基因段交换操作）时，使用全体种群来优化最优个体。

这样一来，较为简单的实现了优化算子，经过实际测试也确实有效达到了加快收敛的目的。

## 2.自适应控制策略

IGT算法在问题规模变大时，容易陷入局部最优。面对这一现象，考虑可能是映射算子和优化算子在加快收敛速度，使得计算后期快速收敛的同时，较难保证种群多样性

使用一种新的自适应控制策略来防止局部收敛问题：

当种群陷入局部最优情况，多代最优解未发生变化时，将此时已经降到很低的变异概率重新提高到某个值，再将此时已经低于临界速度的演化速度提高到高于临界速度的某个值，重新采用一开始的变异与交叉策略，高速演化。如此一来，原本的算法流程是：初期以Inver-over算子为主，后期以映射算子为主。改变后的流程是，初期以Inver-over算子为主，演化速度降低时以映射算子为主，陷入局部最优时再让种群演化速度提高，回归Inver-over算子为主并加大变异概率，如此反复。

经过测试，虽然提高了运算量，但该策略可以一定程度上避免陷入局部最优，综合效果好。

**总结：**总的来说，该程序实现了IGT算法，完成了完整的程序，并有一定的修改与创新。