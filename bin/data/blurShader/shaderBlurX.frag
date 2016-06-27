//#version 120
//
//uniform sampler2DRect tex0;
//
//
//
//varying vec2 texCoordVarying;
//
//void main()
//{
//    vec4 color;
//    float blurAmnt = 6.0;
//    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -4.0, 0.0));
//    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -3.0, 0.0));
//    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -2.0, 0.0));
//    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * -1.0, 0.0));
//    
//    color += 5.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt, 0));
//	
//    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 1.0, 0.0));
//    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 2.0, 0.0));
//    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 3.0, 0.0));
//    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(blurAmnt * 4.0, 0.0));
//
//    color /= 25.0;
//    color.w = color.x;
//    color.z *= 1.1;
//    color.y *= 1.1;
////    if( color.x < .2){
////        color.w = 0;
////    }
////    else if( color.x > .2){
//
////    }
//
//    gl_FragColor = color;
//}

#version 120

uniform sampler2DRect tex0;

uniform float blurAmnt;

varying vec2 texCoordVarying;

void main()
{
    vec4 color;
    float blurAmnt = 6.;
    
    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 4.0));
    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 3.0));
    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 2.0));
    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 1.0));
    
    color += 5.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt));
    
    color += 4.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -1.0));
    color += 3.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -2.0));
    color += 2.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -3.0));
    color += 1.0 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -4.0));
    
  //  color /= 25.0;
        color /= 25.0;
        color.w = color.x;
        color.z *= 1.1;
        color.y *= 1.1;
    //    if( color.x < .2){
    //        color.w = 0;
    //    }
    //    else if( color.x > .2){
    
    //    }
    
    gl_FragColor = color;
}