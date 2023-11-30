# number-master-solver
Program to solve at best Brainbashers' number master game. This game has a relatively small solution search space so it's a (quite) exact algorithm, it doesn't use artificial intelligence nor machine learning techniques. See https://www.brainbashers.com/numbermaster.asp

nmtool.cpp ask you to provide the number you tried to guess and the hint code you received. It then tells you how many and what are the possible remaing number that can be the winning number.

nmsolver.cpp does the same thing of nmtool.cpp but in addition, it also tells you which number is the best to be the next guess.

The file nmsolver_test.cpp draws a random number and use the same strategy of nmsolver.cpp to guess it autonomously. This file has been used to show that the average guesses that the program uses to find the correct number is: 5.47. My personal average is 5.87 (:
