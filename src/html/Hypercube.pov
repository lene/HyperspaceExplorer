
#version 3.1;

#include "colors.inc"
#include "textures.inc"

global_settings {
  max_trace_level 15
  assumed_gamma 2.2
  }

light_source {<5, 10, -20> color <1,1,1>}
light_source {<-60, -30, -40> color <0.54,1,0.5>}

camera {
    location <0,0,-16>
    right x
    up y
    angle 45
    look_at <0, 0, 0>
}



#declare     x0 = array[16][4]
#declare xtrans = array[16][4]
#declare   xscr = array[16][3]
#declare Square = array[24][4]

#macro InitHypercube ()    
    #declare xx = 0;
    #while (xx <= 1)
        #declare yy = 0;
        #while (yy <= 1)
            #declare zz = 0;
            #while (zz <= 1)
                #declare ww = 0;
                #while (ww <= 1)
                    #declare x0[xx+2*(yy+2*(zz+2*ww))][0] = 2*xx-1;
                    #declare x0[xx+2*(yy+2*(zz+2*ww))][1] = 2*yy-1;
                    #declare x0[xx+2*(yy+2*(zz+2*ww))][2] = 2*zz-1;
                    #declare x0[xx+2*(yy+2*(zz+2*ww))][3] = 2*ww-1;
                    
                    #declare ww = ww+1;
                #end
                
                #declare zz = zz+1;
            #end
            
            #declare yy = yy+1;
        #end
        
        #declare xx = xx+1;
    #end
#end                            //  InitHypercube


#macro TransformX (Rxw)
    #declare s = sin (Rxw);
    #declare c = cos (Rxw);
    #declare i = 0;
    #while (i < 16)
        #declare X = x0[i][0];
        #declare xtrans[i][0] = c*X+s*x0[i][3];
        #declare xtrans[i][1] = x0[i][1];
        #declare xtrans[i][2] = x0[i][2];
        #declare xtrans[i][3] = c*x0[i][3]-s*X;
        
        #declare i = i+1;
    #end
#end             

#macro TransformY (Ryw)
    #declare s = sin (Ryw);
    #declare c = cos (Ryw);
    #declare i = 0;
    #while (i < 16)
        #declare Y = x0[i][1];
        #declare xtrans[i][0] = xtrans[i][0];
        #declare xtrans[i][1] = c*Y+s*xtrans[i][3];
        #declare xtrans[i][2] = xtrans[i][2];
        #declare xtrans[i][3] = c*xtrans[i][3]-s*Y;
        
        #declare i = i+1;
    #end
#end             

#macro TransformZ (Rzw)
    #declare s = sin (Rzw);
    #declare c = cos (Rzw);
    #declare i = 0;
    #while (i < 16)
        #declare Z = x0[i][2];
        #declare xtrans[i][0] = xtrans[i][0];
        #declare xtrans[i][1] = xtrans[i][1];
        #declare xtrans[i][2] = c*Z-s*xtrans[i][3];
        #declare xtrans[i][3] = c*xtrans[i][3]+s*Z;
        
        #declare i = i+1;
    #end
#end             
                   
#macro TranslateW (Tw)
    #declare i = 0;
    #while (i < 16)    
        #declare xtrans[i][3] = xtrans[i][3]+Tw;
        #declare i = i+1;
    #end
#end             
                   
#macro Project (Wscr, Wcam)
    #declare i = 0;
    #while (i < 16)
        #declare ProjectionFactor = (Wscr - Wcam)/xtrans[i][3];
        #declare j = 0;
        #while (j < 3)
            #declare xscr[i][j] = xtrans[i][j]*ProjectionFactor;
            #declare j = j+1;
        #end
        
        #declare i = i+1;
    #end
#end

#macro DeclareSquare (i, a, b, c, d)
    #declare Square[i][0] = a;
    #declare Square[i][1] = b;
    #declare Square[i][2] = c;
    #declare Square[i][3] = d;      
#end                             

#declare rmax = -10;
#declare rmin =  10;
#declare gmax = -10;
#declare gmin =  10;
#declare bmax = -10;
#declare bmin =  10;
#declare fmax = -10;
#declare fmin =  10;
#macro DeclareColor (i)
    #declare R = (x0[Square[i][0]][0] + x0[Square[i][1]][0]
                + x0[Square[i][2]][0] + x0[Square[i][3]][0] + 8)/12;   //  1/3 <= R <= 1 
#   if (R > rmax)
        #declare rmax = R;
#   end        
#   if (R < rmin)
        #declare rmin = R;
#   end        
                
    #declare G = (x0[Square[i][0]][1] + x0[Square[i][1]][1]
                + x0[Square[i][2]][1] + x0[Square[i][3]][1] + 8)/12;
#   if (G > gmax)
        #declare gmax = G;
#   end        
#   if (G < gmin)
        #declare gmin = G;
#   end        
    #declare B = (x0[Square[i][0]][2] + x0[Square[i][1]][2]
                + x0[Square[i][2]][2] + x0[Square[i][3]][2] + 8)/12;               
#   if (B > bmax)
        #declare bmax = B;
#   end        
#   if (B < bmin)
        #declare bmin = B;
#   end        
    #declare F = (x0[Square[i][0]][3] + x0[Square[i][1]][3]
                + x0[Square[i][2]][3] + x0[Square[i][3]][3] + 4)/8;
#   if (F > fmax)
        #declare fmax = F;
#   end        
#   if (F < fmin)
        #declare fmin = F;
#   end        
    #declare F = 0.9-0.8*F;            //  0.25 <= F <= 0.75
    
    pigment { color rgbf < R, G, B, F> }                    
#end

    
#macro InitSquares ()
    DeclareSquare (0,  0, 1, 2, 3)    
    DeclareSquare (1,  0, 1, 4, 5)    
    DeclareSquare (2,  0, 1, 8, 9)    
    DeclareSquare (3,  0, 2, 4, 6)    
    DeclareSquare (4,  0, 2, 8,10)    
    DeclareSquare (5,  0, 4, 8,12)    
    DeclareSquare (6,  1, 3, 5, 7)    
    DeclareSquare (7,  1, 3, 9,11)    
    DeclareSquare (8,  1, 5, 9,13)    
    DeclareSquare (9,  2, 3, 6, 7)    
    DeclareSquare (10, 2, 3,10,11)    
    DeclareSquare (11, 2, 6,10,14)    
    DeclareSquare (12, 3, 7,11,15)    
    DeclareSquare (13, 4, 5, 6, 7)    
    DeclareSquare (14, 4, 5,12,13)    
    DeclareSquare (15, 4, 6,12,14)    
    DeclareSquare (16, 5, 7,13,15)    
    DeclareSquare (17, 6, 7,14,15)    
    DeclareSquare (18, 8, 9,10,11)    
    DeclareSquare (19, 8, 9,12,13)    
    DeclareSquare (20, 8,10,12,14)    
    DeclareSquare (21, 9,11,13,15)    
    DeclareSquare (22,10,11,14,15)    
    DeclareSquare (23,12,13,14,15)    

    #declare i = 0;
    #while (i < 24)
        triangle {
            <xscr[Square[i][0]][0], xscr[Square[i][0]][1], xscr[Square[i][0]][2]>,
            <xscr[Square[i][1]][0], xscr[Square[i][1]][1], xscr[Square[i][1]][2]>,
            <xscr[Square[i][2]][0], xscr[Square[i][2]][1], xscr[Square[i][2]][2]>

            texture {
                Chrome_Metal
                DeclareColor (i)
            }
            interior { ior 1.2 }
        }
        triangle {
            <xscr[Square[i][1]][0], xscr[Square[i][1]][1], xscr[Square[i][1]][2]>,
            <xscr[Square[i][2]][0], xscr[Square[i][2]][1], xscr[Square[i][2]][2]>,
            <xscr[Square[i][3]][0], xscr[Square[i][3]][1], xscr[Square[i][3]][2]>
            
            texture { 
                Chrome_Metal           
                DeclareColor (i)
            }                    
            interior { ior 1.2 }
        }        
        
        #declare i = i+1;
    #end
    
#end


InitHypercube ()

#switch (clock)
    #range (0.0, 1.0)
        TransformX (pi*clock)  
    #break
    #range (1.0, 2.0)
        TransformX (pi)
        TransformY (pi*(clock-1))  
    #break
    #range (2.0, 3.0)
        TransformX (pi)
        TransformY (pi)  
        TransformZ (pi*(clock-2))  
    #break    
    #range (3.0, 4.0)
        TransformX (pi*(4-clock))
        TransformY (pi*(4-clock))  
        TransformZ (pi*(4-clock))  
    #break    
#end
TranslateW (2.1)


Project (3, 0)

union {
    InitSquares ()
    
    rotate <0, 180*clock, 0>
}
     
     
#debug concat ("rmin = ", str (rmin, 5, 2), "\trmax = ", str (rmax, 5, 2), 
             "\ngmin = ", str (gmin, 5, 2), "\tgmax = ", str (gmax, 5, 2),
             "\nbmin = ", str (bmin, 5, 2), "\tbmax = ", str (bmax, 5, 2),
             "\nfmin = ", str (fmin, 5, 2), "\tfmax = ", str (fmax, 5, 2))