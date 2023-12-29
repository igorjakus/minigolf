#shader vertex
#version 330 core
layout(location = 0) in vec2 aPos;  
layout(location = 1) in vec2 aTex;  

uniform mat4 u_P;
uniform mat4 u_T;
uniform mat4 u_R;
uniform mat4 u_S;

out vec2 vTex;

void main()
{
    gl_Position = u_P * u_T * u_R * u_S * vec4(aPos, 0.0f, 1.0f);
    vTex = aTex;
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 vTex;
uniform sampler2D u_Tex;
uniform vec4 u_Col;
uniform int u_Texuse;

void main()
{
    color = (u_Texuse == 1) ? texture(u_Tex, vTex) * u_Col : u_Col;
}