# ColorQuestForPreSchool
ColorQuest is an interactive color learning game designed specifically for preschool students. Developed in C++ using OpenGL, this project helps young children recognize and associate colors with familiar objects through a simple and engaging click-to-choose interface.
This game was created as an assignment for a Computer Graphics course and is still under active development. It demonstrates fundamental graphics programming concepts such as 2D shape rendering, user input handling, and basic game logic, all while providing a fun educational experience. 
Features
•	Objects: apple, banana, sky, rose, sunflower
•	Clickable color buttons with instant feedback
•	Responsive layout that handles window resizing
How to Run
Requirements: C++ compiler, OpenGL, GLUT
Compile and run: Setup the environment for OpenGL and copy the code from main.cpp and paste it in your compiler.

✅ Steps to Run test3.cpp in Code::Blocks (32-bit)
1. Install Code::Blocks with MinGW (32-bit)
•	Download Code::Blocks with MinGW from:
https://www.codeblocks.org/downloads/
•	Choose the version that includes mingw-setup.exe (32-bit)
2. Install OpenGL & GLUT Libraries
You need the following files:
•	Header files: GL/glut.h, GL/glu.h, GL/gl.h
•	Library files: libglut32.a, libglu32.a, libopengl32.a
•	DLL: glut32.dll
You can download free GLUT packages like:
•	https://www.transmissionzero.co.uk/software/freeglut-devel/
Then do:
1.	Copy .h files → CodeBlocks\MinGW\include\GL\
2.	Copy .a files → CodeBlocks\MinGW\lib\
3.	Copy glut32.dll → C:\Windows\System32\ (for 32-bit)
3. Create a New OpenGL Project in Code::Blocks
1.	Open Code::Blocks → File → New → Project → OpenGL Project
2.	Set project name and location
3.	Replace the auto-generated .cpp with your test3.cpp code
4. Link the Required Libraries
Go to:
Project → Build options → Linker settings tab
Add these to Link libraries:
nginx
CopyEdit
opengl32
glu32
glut32
5. Build & Run
Click Build and Run (F9)
You should see the game window open. Click color buttons to play.


Future Work
•	Add more objects and colors
•	Introduce animations and sounds
•	Enhance UI design
________________________________________
A fun and educational project combining graphics programming and interactive learning.

