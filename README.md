# README

TSP (traveling salesman problem) is one of the typical NP hard problems in combinatorial optimization, and evolutionary algorithm is a very effective method to solve combinatorial optimization problems. 

This paper mainly studies the framework and operator of efficient evolutionary algorithm for TSP problem, adopts the crossover and mutation strategy (inver-over operator) of GT algorithm, uses the mapping operator and optimization operator proposed by IGT algorithm to accelerate convergence, designs a new adaptive control strategy to prevent local convergence, and develops a set algorithm implementation, graphical evolution process observation Algorithm performance diagnosis function as one of the procedures. 

The graphical display of the optimal individual path in the population is realized by using C + + programming language and Qt library. The program uses markbench test samples to design, verify and improve the algorithm. 

Finally, all test samples can evolve in an algebra of 50 times the size of the problem, and the result is equal to or even better than the optimal solution provided by the sample.