uniform sampler2D texture;

void main()
{
	vec2 coordinates;
	float pixelDistanceX;
	float pixelDistanceY;
	float offset;
	float dir;

	pixelDistanceX = distance(gl_TexCoord[0].x, 0.5);
	pixelDistanceY = distance(gl_TexCoord[0].y, 0.5);

    offset = (pixelDistanceX  * 0.2) * pixelDistanceY;

    if (gl_TexCoord[0].y <= 0.5){
        dir = 1;
    }
    else{
        dir = -1;
    }

	coordinates = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y * 0.9 + 0.1 + pixelDistanceX * (offset * 2.5 * dir)/*+ pixelDistanceX * (offset * 0.0 * dir)*/);

	vec4 pixel = texture2D(texture, coordinates);

	gl_FragColor = gl_Color * pixel;
}
