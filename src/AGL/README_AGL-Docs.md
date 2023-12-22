# Window

- Defined in header <Window.h>

- namespace agl

<details>
<summary>Constructor</summary>

##### Parameters: 
- unsigned int width: screen width
- unsigned int height: screen height
- std::string title: screen title
#####  Return:
- none
</details>

<details>
<summary>create</summary>

##### Parameters: 
- none
#####  Return:
- none
#####  Descrption:
Creates the window and initializes GLAD. This funcion must be called before being able to do any sort of interaction with the window.
</details>

<details>
<summary>closeCallBack</summary>

##### Parameters: 
- none
#####  Return:
- bool
#####  Descrption:
Returns the state of close flag.
</details>
		
<details>
<summary>close</summary>

##### Parameters: 
- none
##### Return:
- none
##### Descrption:
Sets the close flag.
</details>

<details>
<summary>setFullscreen</summary>

##### Parameters: 
- bool fullscreen
##### Return:
- none
##### Descrption:
Sets the window to:
- fullscreen if "fullscreen" is true.
- windowed if "fullscreen" is false.
</details>

<details>
<summary>setBorderless</summary>

##### Parameters: 
- bool borderless
##### Return:
- none
##### Descrption:
Sets the window to:
- borderless fullscreen if "borderless" is true.
- windowed if "borderless" is false.
!This funcion isin't fully implemented. It doesn't make the window cover OS taskbar.
</details>

<details>
<summary>setVSync</summary>

##### Parameters: 
- bool vsync
##### Return:
- none
##### Descrption:
Sets the VSync to the value specified by "vsync". On by default.
</details>

<details>
<summary>setWindowSize</summary>

##### Parameters: 
- unsigned int width
- unsigned int height
##### Return:
- none
##### Descrption:
Sets the window size to the parameters specified in "width" and "height".

#### setWindowSize

##### Parameters: 
- glm::uvec2 dims
##### Return:
- none
##### Descrption:
Sets the window size to the parameters specified in "dims".
</details>

<details>
<summary>setWindowPos</summary>

##### Parameters: 
- unsigned int x
- unsigned int y
##### Return:
- none
##### Descrption:
Sets the window position to the parameters specified in "x" and "y". {0, 0} is the top left corner

#### setWindowPos

##### Parameters: 
- glm::uvec2 pos
##### Return:
- none
##### Descrption:
Sets the window position to the parameters specified in "pos". {0, 0} is the top left corner
</details>

<details>
<summary>setSizeLimits</summary>

##### Parameters: 
- unsigned int minW
- unsigned int minH
- unsigned int maxW
- unsigned int maxH
##### Return:
- none
##### Descrption:
Makes the window unable to be resized to a size smaller than specified by "minW" and "minH" and bigger than specified by "maxW" and "maxH".\
This limit will still apply when trying to maximise the window (including putting it in borderless fulscreen mode)!

#### setSizeLimits

##### Parameters: 
- glm::uvec2 minDims
- glm::uvec2 maxDims
##### Return:
- none
##### Descrption:
Makes the window unable to be resized to a size smaller than specified by "minDims" and bigger than specified by "maxDims".\
This limit will still apply when trying to maximise the window (including putting it in borderless fulscreen mode)!
</details>

<details>
<summary>setTitle</summary>

##### Parameters: 
- std::string title
##### Return:
- none
##### Descrption:
Sets the window title to one specified in "title".
</details>

<details>
<summary>setIcon</summary>

##### Parameters: 
- std::string icon
- std::string icon_small
##### Return:
- null
##### Descrption:
Sets the window icon to the image being located in the localization specified in "icon" and "icon_small".\
For details why two images are an option see GLFW Documentation.\
The image data is 32-bit, little-endian, non-premultiplied RGBA, i.e. eight bits per channel with the red channel first. The pixels are arranged canonically as sequential rows starting from the top##left corner.

#### setIcon

##### Parameters: 
- none
##### Return:
- none
##### Descrption:
Sets the window icon to the Windows default icon.
</details>
	
<details>
<summary>maximizeWindow</summary>

##### Parameters: 
- bool maximize
##### Return:
- none
##### Descrption:
Sets the window to:
- maximized if "maximize" is true.
- windowed if "maximize" is false.
</details>
	
<details>
<summary>setResizable</summary>

##### Parameters: 
- bool resizable
##### Return:
- none
##### Descrption:
- Allows windows resizeing if "resizable" is true.
- Disallows windows resizeing if "resizable" is false.
</details>

<details>
<summary>isBorderless</summary>

##### Parameters: 
- none
##### Return:
- bool
##### Descrption:
Return true is window is in borderless fullscreen, false otherwise.
</details>

<details>	
<summary>isFullscreen</summary>

##### Parameters: 
- none
##### Return:
- bool
##### Descrption:
Return true is window is in fullscreen, false otherwise.
</details>
	
<details>
<summary>getTitle</summary>

##### Parameters: 
- none
##### Return:
- std::string
##### Descrption:
Return the currnet window title.
</details>

<details>
<summary>getWindowSize</summary>

##### Parameters: 
- int& width
- int& height
##### Return:
- none
##### Descrption:
Puts the current window width into "width" and current window height into "height".
</details>

<details>
<summary>getWindowPos</summary>

##### Parameters: 
- int& x
- int& y
##### Return:
- none
##### Descrption:
Puts the current window x coordinate into "x" and current window y coordinate into "y" {0, 0} being the top left corner.
</details>

<details>
<summary>getScreenResolution</summary>

##### Parameters: 
- int& width
- int& height
##### Return:
- none
##### Descrption:
Puts the primary monitor's resolution into "witdh" and "height".
</details>

<details>
<summary>getVSync</summary>

##### Parameters: 
- none
##### Return:
- bool
##### Descrption:
Returns true if VSync is on, false otherwise.
</details>

<details>
<summary>FEP</summary> 

(Frame End Point)

##### Parameters: 
- none
##### Return:
- none
##### Descrption:
This funcion marks the end of rendering frame and should be put at the end of rendering loop.
</details>

<details>
<summary>passPointer</summary>

##### Parameters: 
- none
##### Return:
- GLFWwindow*
##### Descrption:
Returns the pointer to the window. Using this method of interactions with the window is NOT advised.
</details>

As of this moment there is a funcion "bool IsKeyPressed(int key)"\
==BE CAREFULL USING THIS FUNCTION, IT WILL BE REMOVED!!!==

# Shader

- Defined in header <Shader.h>

- namespace agl

<details>
<summary>Constructor</summary>

##### Parameters: 
- std::string filePath
##### Return:
- none
##### Description:
The constructor takes care of compiling, linking and logging errors connected with compilation of the shader program.

#### Constructor

##### Parameters: 
- std::string vertexFilePath
- std::string fragmentFilePath
- std::string geometryFilePath
##### Return:
- none
##### Description:
The constructor takes care of compiling, linking and logging errors connected with compilation of the shader program.
</details>

<details>
<summary>bind</summary>

##### Parameters: 
- none
##### Return:
- none
##### Descrption:
Binds the shader.
</details>

<details>
<summary>unbind</summary>

:Static
##### Parameters: 
- none
##### Return:
- none
##### Descrption:
Unbinds all shaders.
</details>

<details>
<summary>setUniform1f</summary>

##### Parameters: 
- std::string varName
- float v0
##### Return:
- none
##### Descrption:
Sets the shader float uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform2f</summary>

##### Parameters: 
- std::string varName
- float v0
- float v1
##### Return:
- none
##### Descrption:
Sets the shader float2 uniform with the name of "varName" to the value of "v0" and "v1".

#### setUniform2f

##### Parameters: 
- std::string varName
- glm::vec2 v0
##### Return:
- none
##### Descrption:
Sets the shader float2 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform3f</summary>

##### Parameters: 
- std::string varName
- float v0
- float v1
- float v2
##### Return:
- none
##### Descrption:
Sets the shader float3 uniform with the name of "varName" to the value of "v0", "v1" and "v2".

#### setUniform3f

##### Parameters: 
- std::string varName
- glm::vec3 v0
##### Return:
- none
##### Descrption:
Sets the shader float3 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform4f</summary>

##### Parameters: 
- std::string varName
- float v0
- float v1
- float v2
- float v3
##### Return:
- none
##### Descrption:
Sets the shader float4 uniform with the name of "varName" to the value of "v0", "v1", "v2" and "v3".

#### setUniform4f

##### Parameters: 
- std::string varName
- glm::vec4 v0
##### Return:
- none
##### Descrption:
Sets the shader float4 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform1i</summary>

##### Parameters: 
- std::string varName
- int v0
##### Return:
- none
##### Descrption:
Sets the shader int uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform2i</summary>

##### Parameters: 
- std::string varName
- int v0
- int v1
##### Return:
- none
##### Descrption:
Sets the shader int2 uniform with the name of "varName" to the value of "v0" and "v1".

#### setUniform2i

##### Parameters: 
- std::string varName
- glm::ivec2 v0
##### Return:
- none
##### Descrption:
Sets the shader int2 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform3i</summary>

##### Parameters: 
- std::string varName
- int v0
- int v1
- int v2
##### Return:
- none
##### Descrption:
Sets the shader int3 uniform with the name of "varName" to the value of "v0", "v1" and "v2".

#### setUniform3i

##### Parameters: 
- std::string varName
- glm::ivec3 v0
##### Return:
- none
##### Descrption:
Sets the shader int3 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform4i</summary>

##### Parameters: 
- std::string varName
- int v0
- int v1
- int v2
- int v3
##### Return:
- none
##### Descrption:
Sets the shader int4 uniform with the name of "varName" to the value of "v0", "v1", "v2", "v3".

#### setUniform4i

##### Parameters: 
- std::string varName
- glm::ivec4 v0
##### Return:
- none
##### Descrption:
Sets the shader int4 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform1u</summary>

##### Parameters: 
- std::string varName
- unsigned int v0
##### Return:
- none
##### Descrption:
Sets the shader uint uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform2u</summary>

##### Parameters: 
- std::string varName
- unsigned int v0
- unsigned int v1
##### Return:
- none
##### Descrption:
Sets the shader uint2 uniform with the name of "varName" to the value of "v0" and "v1".

#### setUniform2u

##### Parameters: 
- std::string varName
- glm::uvec2 v0
##### Return:
- none
##### Descrption:
Sets the shader uint3 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform3u</summary>

##### Parameters: 
- std::string varName
- unsigned int v0
- unsigned int v1
- unsigned int v2
##### Return:
- none
##### Descrption:
Sets the shader uint3 uniform with the name of "varName" to the value of "v0", "v1" and "v2".

#### setUniform3u

##### Parameters: 
- std::string varName
- glm::uvec3 v0
##### Return:
- none
##### Descrption:
Sets the shader uint3 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform4u</summary>

##### Parameters: 
- std::string varName
- unsigned int v0
- unsigned int v1
- unsigned int v2
- unsigned int v3
##### Return:
- none
##### Descrption:
Sets the shader uint4 uniform with the name of "varName" to the value of "v0", "v1", "v2" and "v3".

#### setUniform4u

##### Parameters: 
- std::string varName
- glm::uvec4 v0
##### Return:
- none
##### Descrption:
Sets the shader uint4 uniform with the name of "varName" to the value of "v0".
</details>

<details>
<summary>setUniform1fv</summary>

##### Parameters: 
- std::string varName
- float* ptr
- size_t size
##### Return:
- none
##### Descrption:
Sets the shader float or float{2, 3, 4} array uniform with the name of "varName" to the data specified in the array passed with the "ptr" pointer and size of "size".

#### setUniform1fv

##### Parameters: 
- std::string varName
- std::vector&lt;float&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader float or float{2, 3, 4} array uniform with the name of "varName" to the data specified in the vector "arr".

#### setUniform1fv

##### Parameters: 
- std::string varName
- std::array&lt;float, any&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader float or float{2, 3, 4} array uniform with the name of "varName" to the data specified in the array "arr".
</details>

<details>
<summary>setUniform1iv</summary>

##### Parameters: 
- std::string varName
- int* ptr
- size_t size
##### Return:
- none
##### Descrption:
Sets the shader int or int{2, 3, 4} array uniform with the name of "varName" to the data specified in the array passed with the "ptr" pointer and size of "size".

#### setUniform1iv

##### Parameters: 
- std::string varName
- std::vector&lt;int&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader int or int{2, 3, 4} array uniform with the name of "varName" to the data specified in the vector "arr".

#### setUniform1iv

##### Parameters: 
- std::string varName
- std::array&lt;int, any&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader int or int{2, 3, 4} array uniform with the name of "varName" to the data specified in the array "arr".
</details>

<details>
<summary>setUniform1uv</summary>

##### Parameters: 
- std::string varName
- unsigned int* ptr
- size_t size
##### Return:
- none
##### Descrption:
Sets the shader uint or uint{2, 3, 4} array uniform with the name of "varName" to the data specified in the array passed with the "ptr" pointer and size of "size".

#### setUniform1uv

##### Parameters: 
- std::string varName
- std::vector&lt;unsigned int&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader uint or uint{2, 3, 4} array uniform with the name of "varName" to the data specified in the vector "arr".

#### setUniform1uv

##### Parameters: 
- std::string varName
- std::array&lt;unsigned int, any&gt; arr
##### Return:
- none
##### Descrption:
Sets the shader uint or uint{2, 3, 4} array uniform with the name of "varName" to the data specified in the array "arr".
</details>

<details>
<summary>setUniformMatrix3</summary>

##### Parameters: 
- std::string varName
- glm::mat3 v0
##### Return:
- none
##### Descrption:
Sets the shader matrix(float, 3, 3) uniform with the name of "varName" to the data specified in the array "v0".
</details>

<details>
<summary>setUniformMatrix4</summary>

##### Parameters: 
- std::string varName
- glm::mat4 v0
##### Return:
- none
##### Descrption:
Sets the shader matrix(float, 4, 4) uniform with the name of "varName" to the data specified in the array "v0".
</details>