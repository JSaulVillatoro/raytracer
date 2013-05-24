// cs473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}




light_source {<0, 0, 25> color rgb <1.5, 1.5, 1.5>}


plane {<0, 1, 0>, -6
      pigment {color rgb <1.0, 0.5, 0.0>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 0>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <0.0, 1.0, 0.5>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 90>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <1.0, 0.0, 0.5>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 180>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 270>
}

plane {<0, 0, 1>, -6
      pigment {color rgb <1.0, 1.0, 1.0>}
      finish {ambient 0.4 diffuse 0.8 }
      rotate <0, 0, 0>
}

box { <-5, -6, -1>, < -3, -4, 1>
  pigment { color rgbf <1.0, 0.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.8 roughness 0.05}
  rotate < 0, -15, 0>
}

box { <-2.5, -6, -1>, < -0.5, -4, 1>
  pigment { color rgbf <0.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.8 roughness 0.05}
  rotate < 0, 10, 0>
}

box { <-3.75, -4, -1>, < -1.75, -2, 1>
  pigment { color rgbf <0.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.8 roughness 0.05}
}

triangle { <-5, 6, -3.5>, <5, 6, -3.5>, <-5, 3, -5.9>
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 1.0}
}

triangle { <5, 3, -5.9>, <5, 6, -3.5>, <-5, 3, -5.9>
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 1.0}
}
sphere { <4, -4, 0>, 2
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
}

sphere { <-1.25, -2, 8>, 0.25
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
}

