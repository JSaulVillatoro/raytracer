// cs473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}




light_source {<-100, 100, 80> color rgb <1.5, 1.5, 1.5>}


plane {<0, 1, 0>, -6
      pigment {color rgb <0.3, 0.3, 0.8>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 0>
}

sphere { <-5, 0, 0>, 2.5
pigment { color rgb <1.0, 0.1, 1.0>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05 reflection 0.8 gloss 1.0}
}

sphere { <0, 0, 0>, 1.5
translate <3, 4, 0>
pigment { color rgb <1.0, 0.1, 0.3>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05 reflection 0.7 gloss 0.5}
}

sphere { <0, 0, 0>, 2
pigment { color rgb <0.5, 1.0, 1.0>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05}
}

box { <-2, -2, -2>, <2, 2, 2>
   rotate <0, -45, 0>
   translate <6, 0, 0>
   pigment { color rgb <0.2, 0.8, 0.3> }
   finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05 reflection 0.6 gloss 0.0}
}

