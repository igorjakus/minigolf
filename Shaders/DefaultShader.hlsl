#shader vertex
#version 330 core
layout(location = 0) in vec2 aPos;  
layout(location = 1) in vec2 aTex;  

uniform mat4 u_P;
uniform mat4 u_M;

out vec2 vTex;

void main()
{
    gl_Position = u_P * u_M * vec4(aPos, 0.0f, 1.0f);
    vTex = aTex;
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 vTex;
uniform sampler2D u_Tex;

void main()
{
    color = texture(u_Tex, vTex);
}