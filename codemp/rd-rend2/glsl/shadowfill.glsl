/*[Vertex]*/
in vec3 attr_Position;
in vec3 attr_Normal;
in vec4 attr_TexCoord0;

in vec3 attr_Position2;
in vec3 attr_Normal2;

uniform int u_DeformType;
uniform int u_DeformFunc;
uniform float u_DeformParams[7];

uniform float u_Time;
uniform mat4 u_ModelViewProjectionMatrix;

uniform float u_VertexLerp;

float GetNoiseValue( float x, float y, float z, float t )
{
	// Variation on the 'one-liner random function'.
	// Not sure if this is still 'correctly' random
	return fract( sin( dot(
		vec4( x, y, z, t ),
		vec4( 12.9898, 78.233, 12.9898, 78.233 )
	)) * 43758.5453 );
}

float CalculateDeformScale( in int func, in float time, in float phase, in float frequency )
{
	float value = phase + time * frequency;

	switch ( func )
	{
		case WF_SIN:
			return sin(value * 2.0 * M_PI);
		case WF_SQUARE:
			return sign(0.5 - fract(value));
		case WF_TRIANGLE:
			return abs(fract(value + 0.75) - 0.5) * 4.0 - 1.0;
		case WF_SAWTOOTH:
			return fract(value);
		case WF_INVERSE_SAWTOOTH:
			return 1.0 - fract(value);
		default:
			return 0.0;
	}
}

vec3 DeformPosition(const vec3 pos, const vec3 normal, const vec2 st)
{
	switch ( u_DeformType )
	{
		default:
		{
			return pos;
		}

		case DEFORM_BULGE:
		{
			float bulgeHeight = u_DeformParams[1]; // amplitude
			float bulgeWidth = u_DeformParams[2]; // phase
			float bulgeSpeed = u_DeformParams[3]; // frequency

			float scale = CalculateDeformScale( WF_SIN, u_Time, bulgeWidth * st.x, bulgeSpeed );

			return pos + normal * scale * bulgeHeight;
		}

		case DEFORM_WAVE:
		{
			float base = u_DeformParams[0];
			float amplitude = u_DeformParams[1];
			float phase = u_DeformParams[2];
			float frequency = u_DeformParams[3];
			float spread = u_DeformParams[4];

			float offset = dot( pos.xyz, vec3( spread ) );
			float scale = CalculateDeformScale( u_DeformFunc, u_Time, phase + offset, frequency );

			return pos + normal * (base + scale * amplitude);
		}

		case DEFORM_MOVE:
		{
			float base = u_DeformParams[0];
			float amplitude = u_DeformParams[1];
			float phase = u_DeformParams[2];
			float frequency = u_DeformParams[3];
			vec3 direction = vec3( u_DeformParams[4], u_DeformParams[5], u_DeformParams[6] );

			float scale = CalculateDeformScale( u_DeformFunc, u_Time, phase, frequency );

			return pos + direction * (base + scale * amplitude);
		}

		case DEFORM_PROJECTION_SHADOW:
		{
			vec3 ground = vec3(
				u_DeformParams[0],
				u_DeformParams[1],
				u_DeformParams[2]);
			float groundDist = u_DeformParams[3];
			vec3 lightDir = vec3(
				u_DeformParams[4],
				u_DeformParams[5],
				u_DeformParams[6]);

			float d = dot( lightDir, ground );

			lightDir = lightDir * max( 0.5 - d, 0.0 ) + ground;
			d = 1.0 / dot( lightDir, ground );

			vec3 lightPos = lightDir * d;

			return pos - lightPos * dot( pos, ground ) + groundDist;
		}
	}
}

vec3 DeformNormal( const in vec3 position, const in vec3 normal )
{
	if ( u_DeformType != DEFORM_NORMALS )
	{
		return normal;
	}

	float amplitude = u_DeformParams[1];
	float frequency = u_DeformParams[3];

	vec3 outNormal = normal;
	const float scale = 0.98;
	
	outNormal.x += amplitude * GetNoiseValue(
		position.x * scale,
		position.y * scale,
		position.z * scale,
		u_Time * frequency );

	outNormal.y += amplitude * GetNoiseValue(
		100.0 * position.x * scale,
		position.y * scale,
		position.z * scale,
		u_Time * frequency );

	outNormal.z += amplitude * GetNoiseValue(
		200.0 * position.x * scale,
		position.y * scale,
		position.z * scale,
		u_Time * frequency );

	return outNormal;
}

void main()
{
	vec3 position  = mix(attr_Position, attr_Position2, u_VertexLerp);
	vec3 normal    = mix(attr_Normal,   attr_Normal2,   u_VertexLerp);
	normal = normalize(normal - vec3(0.5));

	position = DeformPosition(position, normal, attr_TexCoord0.st);
	gl_Position = u_ModelViewProjectionMatrix * vec4(position, 1.0);
}

/*[Fragment]*/
out vec4 out_Color;
void main()
{
	out_Color = vec4(0, 0, 0, 1);
}
