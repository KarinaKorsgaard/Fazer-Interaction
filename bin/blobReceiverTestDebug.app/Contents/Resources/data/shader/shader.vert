uniform float varyByColor;
void main() {

    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
	
    //float alpha   = gl_Normal.y;
    
    gl_PointSize  = gl_Vertex.z*5.5;
    vec4 col =gl_Color*vec4(vec3(1.),.5);
//    if(gl_Vertex.z>10.){
//        col.r=1.-gl_Vertex.z/20.;
//        col.g=gl_Vertex.z/20.;
//    }
    if(varyByColor>0.5){
        gl_PointSize  = gl_Vertex.z*7.5;
       
    }
    gl_FrontColor =col;
    

}