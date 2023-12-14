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
!This funcion isin't fully implemented. It doesn't make the window cover os taskbar.
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
</details>

<details>
<summary>setSizeLimits</summary>

##### Parameters: 
-unsigned int minW
-unsigned int minH
-unsigned int maxW
-unsigned int maxH
##### Return:
- none
##### Descrption:
Makes the window unable to be resized to a size smaller than specified by "minW" and "minH" and bigger than specified by "maxW" and "maxH".
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
Sets the window icon to the image being located in the localization specified in "icon" and "icon_small".
For details why two images are an option see GLFW Documentation
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

As of this moment there is a funcion "bool IsKeyPressed(int key)" 
DO NOT USE THIS FUNCION, IT WILL BE REMOVED!!!
</details>
