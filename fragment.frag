#version 330

uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	
	float distance = length(vPos);

	// Settingan Jam
	float dotHour = dot(normalize(vPos), vec2(0.8 * cos(currentHourPointer), 0.8 * sin(currentHourPointer)));
	if (distance <=0.9 && dotHour < 0.8 * sin(currentHourPointer))
	{
		color = color1;	
	}

	if(distance<=0.8){
	color = vec4(1.0, 1.0, 1.0, 1.0);
	}


	// Settingan Menit
	float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));
	if (distance <= 0.7 && dotMinute < 0.6 * sin(currentMinutePointer))
	{
		color = color2;
	}

	if(distance <= 0.6){
	color = vec4(1.0,1.0,1.0,1.0);
	}



	// Settingan Detik
	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
	if (distance <= 0.5 && dotSecond < sin(currentSecondPointer))
	{
			color = color3;
	}

	if(distance <=0.4){
		color = vec4(1.0,1.0,1.0,1.0);
	}

	

}