
#version 3.1;

#include "colors.inc"
#include "textures.inc"

global_settings {
  max_trace_level 15
  assumed_gamma 2.2
  }

light_source {<5, 10, -20> color <1,1,1>}
light_source {<-30, 5, -20> color <0.94,1,0.9>}

camera {
    location <0,0,-8>
    right x
    up y
    angle 40
    look_at <0, 0, 0>
}



#declare     x0 = array[5][4]
#declare xtrans = array[5][4]
#declare   xscr = array[5][3]
#declare    Tri = array[10][3]

             
#macro DeclareVec (i, a, b, c, d)
    #declare x0[i][0] = a;
    #declare x0[i][1] = b;
    #declare x0[i][2] = c;
    #declare x0[i][3] = d;      
#end                             
                  
#macro Center (a, b, c, d)
    #declare i = 0;
    #while (i < 5)
        #declare  x0[i][0] = x0[i][0] + a;
        #declare  x0[i][1] = x0[i][1] + b;
        #declare  x0[i][2] = x0[i][2] + c;
        #declare  x0[i][3] = x0[i][3] + d;
        
        #declare i = i+1;
    #end
#end                  
             
#macro InitHypersimplex ()    
        DeclareVec (0,  0, 0, 0, 0)
        DeclareVec (1,  1, 0, 0, 0)
        DeclareVec (2,  0.5, sqrt (3)/2, 0, 0)
        DeclareVec (3,  0.5, sqrt (3)/6, sqrt (2./3.), 0)
        DeclareVec (4,  0.5, sqrt (3)/6, 1./sqrt (6.), 1./sqrt (2))
        
        Center (-0.5, -sqrt (3)/6, -1./sqrt (6.), 0)
#end                            //  InitHypersimplex


#macro TransformX (Rxw)
    #declare s = sin (Rxw);
    #declare c = cos (Rxw);
    #declare i = 0;
    #while (i < 5)
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
    #while (i < 5)
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
    #while (i < 5)
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
    #while (i < 5)
        #declare xtrans[i][3] = xtrans[i][3]+Tw;
        #declare i = i+1;
    #end
#end             
                   
#macro Project (Wscr, Wcam)
    #declare i = 0;
    #while (i < 5)
        #declare ProjectionFactor = (Wscr - Wcam)/xtrans[i][3];
        #declare j = 0;
        #while (j < 3)
            #declare xscr[i][j] = xtrans[i][j]*ProjectionFactor;
            #declare j = j+1;
        #end
        
        #declare i = i+1;
    #end
#end

#macro DeclareTriangle (i, a, b, c)
    #declare Tri[i][0] = a;
    #declare Tri[i][1] = b;
    #declare Tri[i][2] = c;
#end           

#declare Fmin = 10;
#declare Fmax = -10;                  

#macro DeclareColor (i)
    #declare R = (x0[Tri[i][0]][0] + x0[Tri[i][1]][0]
                + x0[Tri[i][2]][0]+.5);         //  0 <= R <= 1   
//    #if (R < 0.3)
//        #declare R = 0.3;
//    #end
    #declare G = (x0[Tri[i][0]][1] + x0[Tri[i][1]][1]
                + x0[Tri[i][2]][1]+sqrt (3)/2-0.29)/1.15;
//    #if (G < 0.3)
//        #declare G = 0.3;
//    #end
    #declare B = (x0[Tri[i][0]][2] + x0[Tri[i][1]][2]
                + x0[Tri[i][2]][2]+3/sqrt (6))/1.22;               
//    #if (B < 0.3)
//        #declare B = 0.3;
//    #end          
    
    #declare F = (x0[Tri[i][0]][3] + x0[Tri[i][1]][3]
                + x0[Tri[i][2]][3]);         //  0 <= F <= sqrt (0.5)
                
    #if (F > Fmax)
        #declare Fmax = F;
    #end
    #if (F < Fmin)
        #declare Fmin = F;
    #end
    #declare F = 1-F/4;
               // (2+sqrt (2))/4-F;           //  0.146 <= F <= 0.854
    
    pigment { color rgbf < R, G, B, F> }                    
#end

    
#macro InitTriangles ()
    DeclareTriangle (0,  0, 1, 2)    
    DeclareTriangle (1,  0, 1, 3)    
    DeclareTriangle (2,  0, 1, 4)    
    DeclareTriangle (3,  0, 2, 3)    
    DeclareTriangle (4,  0, 2, 4)    
    DeclareTriangle (5,  0, 3, 4)    
    DeclareTriangle (6,  1, 2, 3)    
    DeclareTriangle (7,  1, 2, 4)    
    DeclareTriangle (8,  1, 3, 4)    
    DeclareTriangle (9,  2, 3, 4)

    #declare i = 0;
    #while (i < 10)
        triangle {
            <xscr[Tri[i][0]][0], xscr[Tri[i][0]][1], xscr[Tri[i][0]][2]>,
            <xscr[Tri[i][1]][0], xscr[Tri[i][1]][1], xscr[Tri[i][1]][2]>,
            <xscr[Tri[i][2]][0], xscr[Tri[i][2]][1], xscr[Tri[i][2]][2]>

            texture {
                Silver1 // Chrome_Metal   
                finish { ambient 0.3 }
                DeclareColor (i)
            }
            interior { ior 1.1 }
        }
        
        #declare i = i+1;
    #end
    
#end


InitHypersimplex ()

#switch (clock)
    #range (0.0, 1)
        TransformX (pi*clock)  
    #break
    #range (1.0, 2)
        TransformX (pi)
        TransformY (pi*(clock-1))  
    #break
    #range (2.0, 3)
        TransformX (pi)
        TransformY (pi)  
        TransformZ (pi*(clock-2))  
    #break    
    #range (3.0, 4)
        TransformX (pi*(4-clock))
        TransformY (pi*(4-clock))  
        TransformZ (pi*(4-clock))  
    #break    
#end
TranslateW (1)


Project (3, 0)

union {
    InitTriangles ()
    
    rotate <0, 180*clock, 0>
}
        
plane { y, -3
    pigment { color rgb <0.56, 0.56, 0.56 > } 
}
       
sphere { 0, 80
    pigment { color rgb <0.5, 0.5, 0.5 > } 
    hollow 
}       

