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


sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.1, 1.0>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05}
translate <0, 2, 0>
velocity <0, 1, 0>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.5, 0.3>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05}
translate <4, 0, 0>
velocity <2, 2, 0>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <0.2, 0.8, 0.1>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05}
translate <-4, -2, 0>
velocity <-3, 1.0, 0>
}

sphere { <0, 0, 0>, 2
pigment { color rgb <1.0, 0.8, 1.0>}
finish {ambient 0.2 diffuse 0.7 specular 0.5 roughness 0.05}
translate <0, -2, 0>
}
