//    level: 1
//    axiom: @60X
//    rules: 
//           X -> "{^FX}{&FX}{^^FX}{&&FX}{>FX}{<FX}{X}{FFX}"
//   result: @60{^FX}{&FX}{^^FX}{&&FX}{>FX}{<FX}{X}{FFX}
//  objects: 
//           X -> "sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }"
//           default -> "sphere { 0, 0.5 }"

#default { pigment { rgb 1 } }

union {
  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate 60*y 
      translate < 0.5, 0, 0.866025>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate -60*y 
      translate < 0.5, 0, -0.866025>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate 60*y rotate 60*y 
      translate < -0.5, 0, 0.866025>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate -60*y rotate -60*y 
      translate < -0.5, 0, -0.866025>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate -60*z 
      translate < 0.5, 0.866025, 0>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      rotate 60*z 
      translate < 0.5, -0.866025, 0>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      
      translate < 0, 0, 0>
      scale 0.707107

    }
  }

  object {
    sphere { 0, 0.5 scale <2, 0.2, 0.2> texture { pigment { rgbf < 1, 1, 1, 0.5> } } }
    transform {
      
      translate < 2, 0, 0>
      scale 0.707107

    }
  }

}
cylinder { -2*x, 2*x, 0.02 pigment { color rgb <1, 0, 0> } }
cone { 2*x, .05, 2.2*x, 0 pigment { color rgb <1, 0, 0> } }
cylinder { -2*y, 2*y, 0.02 pigment { color rgb <0, 1, 0> } }
cone { 2*y, .05, 2.2*y, 0 pigment { color rgb <0, 1, 0> } }
cylinder { -2*z, 2*z, 0.02 pigment { color rgb <0, 0, 1> } }
cone { 2*z, .05, 2.2*z, 0 pigment { color rgb <0, 0, 1> } }

camera {
  location <4,1,2.4> direction <0,1,0> right x*5/4 up y look_at 0
}
light_source { <200,500,100> color rgb 1 }
light_source { <6, 2, 3> color rgb 0.9 }
