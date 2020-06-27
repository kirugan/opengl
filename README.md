Playlist - https://www.youtube.com/redirect?q=https%3A%2F%2Fthecherno.com%2Fopengl&v=H2E3yO0J7TM&redir_token=j7sqmdb2IDwV1IJ3Wgf31QcxUS58MTU5MzIwMTgzOUAxNTkzMTE1NDM5&event=video_description

#1 
OpenGL is specification as HTML5. GPU manufacturers implement them in their drivers, although there is a software implementation of OpenGL called Mesa.

You need glfw library to create windows and stuff crossplatform.

#2 
Windows implemented OpenGL 1.1 max (< 1997 year) they view of graphics programming is - DirectX.
So in order to access newer version of OpenGL you have to link glut library.

Basically it dynamically loads driver library and provide you header files (with function interfaces).

#3
OpenGL is very context specific. For instance:
    glBuffer...
    glBind.... // relates to glBuffer
    
Everything has objectId

Beware vertex has nothing to do with a position. Cause vertex can contain way more than a position i.e. text coord, colors, normals ...
Index - attribute (color, normal etc.)

#4
... -> Vertex Shader (one call per vertex) -> .... -> Fragment Shader (Pixel shader) -> ...
You can pass data from VS to FS1

#7
glDeleteShader - like deleting obj files from compilation 

#9
indexBuffers needs in order to reuse vertex data (for instance draw rectangle using 2 triangles - you need only 4 vertices)

# Questions
1. It seems like all these openGL calls happens on CPU, so most of the time CPU pass commands to GPU and do almost nothing.
   Is there any way to pass all this geometry logic to gpu and do something useful on cpu instead.