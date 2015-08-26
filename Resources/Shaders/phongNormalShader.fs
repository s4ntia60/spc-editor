#version 400

const int MAX_NUM_LIGHTS = 8; // max number of lights

in vec3 LightDir[MAX_NUM_LIGHTS];
in vec3 VexterPosEye;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 LightDirStaticTan;


uniform sampler2D ColorTex;
uniform sampler2D NormalMapTex;
uniform sampler2D SpecularMapTex;
uniform vec3 LightColor;
uniform float LightDiffuseIntensity;
uniform float LightAmbientIntensity;


layout( location = 0 ) out vec4 FragColor;


vec3 BlinnPhong(vec3 diffR, vec3 norm, vec3 specularLvl, float Shininess)
{
	
	/*float diffuseIntensity = 0.80;
	float ambientIntensity = 0.82;
	float shininess = 25;
	vec3 lighColor = vec3(0.7, 0.7, 0.7);
	*/
	// this is blinn phong
	vec3 h = normalize(LightDirStaticTan + ViewDir); 
    
	vec3 ambient = (LightAmbientIntensity *  LightColor);

    float sDotN = max( dot(LightDirStaticTan, norm), 0.0 );
    
	vec3 diffuse = (LightDiffuseIntensity *  LightColor) * diffR * sDotN;

    vec3 spec = vec3(0.0);
    
	if( sDotN > 0.0 )
		spec =  LightColor * specularLvl * pow(max(dot(h,norm), 0.0), Shininess);	
			
    
	
	//diffuse = vec3(0.0);
	//ambient = vec3(0.0);
	
	//return vec3(1.0, 0.0, 0.0); /*+  /*diffuse /*+ spec*/;
	return ambient +  diffuse + spec;
}



void main() 
{
    // Lookup the normal and color from the normal map and diffuse map
    vec4 normal = 2 * texture( NormalMapTex, TexCoord ) - 1.0;	
	//vec4 normal = texture( NormalMapTex, TexCoord );	
	
	vec4 texColor = texture( ColorTex, TexCoord );
	
	vec4 specularLvl = texture( SpecularMapTex, TexCoord );
	
	vec4 TotalLight =  vec4(0.0);
	
	FragColor = vec4(0.0);

	TotalLight += vec4(BlinnPhong(texColor.rgb, normal.rgb, specularLvl.rgb, 25), 1.0);		
	
	
	FragColor = TotalLight;// * texColor;	
	//FragColor = texColor;
	//FragColor = texture( NormalMapTex, TexCoord );
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);	
	
	FragColor.a = 1;
		
		
}