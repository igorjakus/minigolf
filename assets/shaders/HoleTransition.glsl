#shader vertex
#version 330 core
layout(location = 0) in vec2 aPos;  
layout(location = 1) in vec2 aTex;  

uniform mat4 u_P;
uniform mat4 u_T;
uniform mat4 u_R;
uniform mat4 u_S;

out vec2 vTex;
out vec2 pos;

void main()
{
    gl_Position = vec4(aPos * 2, 0.0f, 1.0f);
    vTex = aTex;
    vec4 temp = inverse(u_P) * u_T * u_R * u_S * vec4(aPos, 0.0f, 1.0f);
    pos = temp.xy;
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 vTex;
in vec2 pos;
uniform sampler2D u_Tex;
uniform vec4 u_Col;
uniform int u_Texuse;

void main()
{
    if(u_Texuse == 1)
        color = texture(u_Tex, vTex) * u_Col;
    else
    {
        float dist = pos.x * pos.x + pos.y * pos.y;
        float rad = u_Col.x;
        if(dist > rad * rad)
            color = vec4(vTex.xy, 0.5 , 1.);
        else 
            color = vec4(0., 0., 0., 0.);
            
    }
}