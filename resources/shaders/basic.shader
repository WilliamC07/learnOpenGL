#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

uniform mat4 u_modelViewProjection;

// v for varying
// varying is when you pass something from vertex shader to fragment
out vec2 v_TexCoord;

void main(){
    gl_Position = u_modelViewProjection * vec4(position, 0.0, 1.0);
    v_TexCoord = textureCoords;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 v_TexCoord;
uniform sampler2D u_Texture; // u_<...> means variable is a uniform

void main(){
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
}