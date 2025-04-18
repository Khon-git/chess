# chess

Hello! :)
This is a simple terminal based chess for 2 players, written in C++
Admittedly, I am quite the novice when it comes to this language, so there may be some questionable syntax choices used. 

Anyways, if you aren't familiar with how to run C++ programs, you need a compiler to compile the code first.
One thing to note: Since I utilized unicode representations for the pieces, I don't recommend running the code on a windows terminal (In fact, I tried that, and you can see how the board looks like)

![image](https://github.com/user-attachments/assets/257b88d0-57b6-465c-b62f-df05154dfd4e)

In reality, it should look like this:

![image](https://github.com/user-attachments/assets/45b75965-4fa0-4695-b250-ec766c30016f)


Anyways, unless you are using a Linux terminal (wsl doesn't count), I'd recommend installing VSCode (tutorials can be found online) and using its terminal instead.
Also, this is optional but if you do plan on coding frequently I'd highly recommend installing WSL (tutorials can be found online) if you are on Windows.

Once you've done that, install g++, it's the compiler I use to compile my code.
I may be wrong, but if my memory serves me correctly, then it should come included on a Linux or WSL system. If not you can install it easily like this:
![image](https://github.com/user-attachments/assets/baba09d9-7e7c-4d91-bac6-ea1581291b1e)

If you are on windows, you'll have to install MinGW (a collection of development tools) to use g++. There are many tutorials online so I won't get into this.

Anyways, once you have install g++, simply run this in the VSCode terminal inside the directory you've kept this file:
"g++ chess.cpp -o chess.exe"
![image](https://github.com/user-attachments/assets/b263818f-353a-45c2-bee9-448bad42c38b)


This tells the compiler to compile the "chess.cpp" file, and save the resulting executable as "chess.exe"
Now, you can run the program by entering:
"./chess.exe"
![image](https://github.com/user-attachments/assets/160de1d3-39a6-45ad-92e9-ce32013fa85d)

Anyways, that's all, hope you enjoy! 

