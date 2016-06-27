//void main() {
//    
//    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
//    float r   = gl_Normal.x / 255.;
//    float g   = gl_Normal.y / 255.;
//    float b   = gl_Normal.z / 255.;
//    
//    gl_PointSize  = gl_Vertex.z * 10.;
//    gl_FrontColor = gl_Color*vec4(vec3(r,g,b),1.);
//    
//    
//}

void main() {
    
    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    //float alpha   = gl_Normal.y;
    
    float r   = gl_Normal.x / 255.;
    float g   = gl_Normal.y / 255.;
    float b   = gl_Normal.z / 255.;
    
    gl_PointSize  = gl_Vertex.z*5.;
    vec4 col =gl_Color*vec4(vec3(r,g,b),1.);

    
    gl_FrontColor =col;
    
    
}