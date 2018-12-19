# shooter
A simple FPS game written with C++ and OpenGL.

## Run
A binary excutable file is provided, and it may run on your Linux if you have compatible OpenGL and GLFW3.  
`$ ./shooter`  
Then you may see the scene in the following picture:  
<img src="images/shooter.png" width="300">  
You can press the arrow keys and move your mouse around.  
Press `ESC` to quit.
## Compile
`$ make`
## Dependencies
### OpenGL
version >= 3.3, core profile
### GLFW3
Tested with version 3.2.
### GLM
Tested with version 0.9.8 and 0.9.9.
### GLAD (Optional)
This lib is optional, as it's contained in this repo, but you can modify it to your prefer.  
GLAD should choose OpenGL >= 3.3 and core profile if you choose to use your own version.  
OpenGL 4.0 core can be found in https://glad.dav1d.de/  
Setting up method:  
https://learnopengl.com/Getting-started/Creating-a-window  
## Reference
- https://learnopengl.com/Getting-started/Camera
- https://learnopengl.com/In-Practice/2D-Game/Breakout
