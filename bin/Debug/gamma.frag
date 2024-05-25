out vec4 FragColor;

uniform sampler2D texture;
uniform float gamma;

void main()
{
    vec2 coords = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
    vec4 texColor = texture2D(texture, coords);

    // Apply gamma correction
    vec3 correctedColor = pow(texColor.rgb, vec3(1.0 / gamma));

    FragColor = vec4(correctedColor, texColor.a);
}
