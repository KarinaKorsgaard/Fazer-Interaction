//
//uniform sampler2D tex;
//
//void main (void) {
//    
//    gl_FragColor = texture2D(tex, gl_TexCoord[0].st) * gl_Color;
//    
//}

uniform sampler2D tex;


void main (void) {
  //  vec4 inputCol = vec4(col.x/255.,col.y/255.,col.z/255.,1.8);
    //1.8; for gray
    gl_FragColor = texture2D(tex, gl_TexCoord[0].st) * gl_Color;
    
}