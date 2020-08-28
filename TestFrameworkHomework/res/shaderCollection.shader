#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 uniformMVP;/*Our model view projection matrix.*/

void main()
{
    gl_Position = uniformMVP * vec4(position);/*To give our image the righr aspect ratio we multiply our positions
    With the Matrix we just took in as our uniform*/
    v_texCoord = texCoord;/*our input goes to the v_texCoord remember v_texCoord will ouput to the fragment shader*/
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, v_texCoord);
    color = texColor;
}