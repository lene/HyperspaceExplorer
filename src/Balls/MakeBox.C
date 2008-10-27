

void MakeBox (Vec<3> x1, Vec<3> x2, Vec<3> x3, Vec<3> x4,
	      Vec<3> x5, Vec<3> x6, Vec<3> x7, Vec<3> x8) {
  glBegin( GL_LINE_LOOP );
    glVertex3f(x1[0],x1[1],x1[2]);
    glVertex3f(x2[0],x2[1],x2[2]);
    glVertex3f(x4[0],x4[1],x4[2]);
    glVertex3f(x3[0],x3[1],x3[2]);
  glEnd();

  glBegin( GL_LINE_LOOP );
    glVertex3f(x5[0],x5[1],x5[2]);
    glVertex3f(x6[0],x6[1],x6[2]);
    glVertex3f(x8[0],x8[1],x8[2]);
    glVertex3f(x7[0],x7[1],x7[2]);
  glEnd();

  glBegin( GL_LINES );
    glVertex3f(x1[0],x1[1],x1[2]);    glVertex3f(x5[0],x5[1],x5[2]);
    glVertex3f(x2[0],x2[1],x2[2]);    glVertex3f(x6[0],x6[1],x6[2]);
    glVertex3f(x3[0],x3[1],x3[2]);    glVertex3f(x7[0],x7[1],x7[2]);
    glVertex3f(x4[0],x4[1],x4[2]);    glVertex3f(x8[0],x8[1],x8[2]);
  glEnd();
}

GLint MakeBox() {       
    GLuint list = glGenLists( 1 );
    glNewList( list, GL_COMPILE );

    glMaterial (1.0,0.9,1.0);    
    glLineWidth( 2.0 );

    Box<num_dimensions>::DefineHypercube ();
    DrawHypercube (num_dimensions, Box<num_dimensions>::vertices);

    glEndList();

    return list;
}


    
