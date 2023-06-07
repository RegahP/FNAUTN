uniform sampler2D texture;
uniform vec2 screen;
//uniform vec2 texture;
//uniform vec4 v_vColour;

void main()
{
	vec2 coordinates;
	float pixelDistanceX;
	float pixelDistanceY;
	float offset;
	float dir;

	vec2 position = gl_TexCoord[0].xy;



    // multiply it by the color



    //gl_FragColor = gl_Color * pixel;

    /*
	pixelDistanceX = distance(gl_FragCoord.x, 0.5);
	pixelDistanceY = distance(gl_FragCoord.y, 0.5);

	offset = (pixelDistanceX*0.2) * pixelDistanceY;

	if (gl_TexCoord[0].y <= 0.5){
        dir = 1.0;
	}
	else{
        dir = -1.0;
	}
	*/
	pixelDistanceX = distance(gl_TexCoord[0].x, 0.5);
	pixelDistanceY = distance(gl_TexCoord[0].y, 0.5);

    offset = (pixelDistanceX) * pixelDistanceY;

    if (gl_TexCoord[0].y <= 0.5){
        dir = -1;
    }
    else{
        dir = -1;
    }

	coordinates = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + pixelDistanceY * (offset * 2 * dir)/*+ pixelDistanceX * (offset * 0.0 * dir)*/);
	//coordinates = vec2(gl_FragCoord.x, gl_FragCoord.y);

	vec4 pixel = texture2D(texture, coordinates);
	gl_FragColor = gl_Color * pixel;
}
