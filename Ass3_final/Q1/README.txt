I have implemented the 4 codes: Code explanations for all:

a1:
We create threads to link it to the philosophers and see as we pick up the chopsticks whether they are free or not. We do this by using a simple integer and checking if it is 1 or 0, if it is 0 the program enters a while loop and only comes out of it when the chopstick becomes available. We then enter the eating process, then after eating the philosopher will make the chopstick he/she used as one.

a2:
I have used semaphores instead of the while loop used in the previous problem. The rest of the functioning is the same and we use instructions like wait and post.

b1:
I have used an integer to mark how many bowls are being used at any point, once someone uses a bowl I decrease the integer by 1. And one can only start eating if there is a bowl left so basically bowl > 0 for anybody to start eating.

b2: 
Similar to A_3 but I have used semaphores instead of a while loop to implement waiting and signalling. 