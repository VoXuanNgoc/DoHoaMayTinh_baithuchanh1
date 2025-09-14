#version 330 core
layout (location = 0) in vec3 aPos;   // for cube (3 components) or vec2 for tri (but we still use vec3)
layout (location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
