#version 120

// -----------------------------------------------------------
void main()
{
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	gl_Position = ftransform();
}
//
//#version 120
//#extension GL_ARB_texture_rectangle : enable
//
//void main()
//{
//    gl_FrontColor = gl_Color;
//    gl_TexCoord[0] = gl_MultiTexCoord0;
//    gl_Position = gl_Vertex;
//}
