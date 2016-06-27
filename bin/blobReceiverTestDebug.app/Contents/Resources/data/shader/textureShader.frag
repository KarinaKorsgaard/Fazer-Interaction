
////uniform sampler2D tex;
//uniform vec2 iResolution;
//uniform sampler2D tex0;
//uniform sampler2DRect tex1;
//
//void main () {
//    
//    
//    
//    vec2 uv = gl_FragCoord.xy / iResolution.x;
//   
//    vec4 col = texture2DRect(tex1, gl_TexCoord[0].xy);
//   // col.b=0.5;
//   // col+= texture2DRect(tex0, gl_TexCoord[0].xy).r;
////    
//    float noise = (texture2D(tex0, uv * iResolution.x / 256.).r - 0.5) * 0.05;
//    col +=noise;
//
//    
////    col += rTxt.r * 100.5;
////   // col+=rTxt;
//    gl_FragColor = col;
//   // gl_FragColor = texture2D(tex, gl_TexCoord[0].st) * gl_Color;
//    
//}

//uniform vec2 iResolution;
//uniform sampler2DRect tex1;
//
//float normpdf(in float x, in float sigma)
//{
//    return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
//}
//
//
//void main(  )
//{
//
//    
//    vec3 c = texture2DRect(tex1, gl_TexCoord[0].xy).xyz;
//    
//    if (gl_FragCoord.x < .5)
//    {
//       
//        gl_FragColor = c;
//    } else {
//        
//        //declare stuff
//        const int mSize = 31;
//        const int kSize = (mSize-1)/2;
//        float kernel[mSize];
//        vec3 final_colour = vec3(0.0);
//        
//        //create the 1-D kernel
//        float sigma = 7.0;
//        float Z = 0.0;
//        for (int j = 0; j <= kSize; ++j)
//        {
//            kernel[kSize+j] = kernel[kSize-j] = normpdf(float(j), sigma);
//        }
//        
//        //get the normalization factor (as the gaussian has been clamped)
//        for (int j = 0; j < mSize; ++j)
//        {
//            Z += kernel[j];
//        }
//        
//        //read out the texels
//        for (int i=-kSize; i <= kSize; ++i)
//        {
//            for (int j=-kSize; j <= kSize; ++j)
//            {
//                final_colour += kernel[kSize+j]*kernel[kSize+i]*texture2DRect(tex1, (gl_TexCoord[0].xy+vec2(float(i),float(j))) / iResolution.xy).rgb;
//                
//            }
//        }
//        
//        
//        gl_FragColor = vec4(final_colour/(Z*Z), 1.0);
//       // gl_FragColor = vec4(c, 0.5);
//    }
//}

uniform vec2 u_resolution;
uniform float scanline;
uniform sampler2D tex;


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    
    float lod = (5.0 + 5.0*sin( scanline ))*step( uv.x, 0.5 );
    
    vec3 col = texture2D( tex, vec2(uv.x,1.0-uv.y), lod ).xyz;
    
    gl_FragColor = vec4( col, 1.0 );
}