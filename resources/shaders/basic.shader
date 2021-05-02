#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
void main(){
    gl_Position = vec4(position, 0.0, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

uniform vec4 u_Color; // u_<...> means variable is a uniform

void main(){
    FragColor = u_Color;
}