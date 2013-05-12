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
      rotate <0, 0, 45>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <0.0, 1.0, 0.5>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 135>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <0.5, 0.0, 1.0>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 225>
}

plane {<0, 1, 0>, -6
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8 specular 0.6 roughness 0.05}
      rotate <0, 0, 315>
}

plane {<0, 1, 0>, -25
      pigment {color rgb <1.0, 1.0, 1.0>}
      finish {ambient 0.4 diffuse 0.8 }
      rotate <90, 0, 0>
}

sphere { <0, 0, 0>, 1
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 specular 0.6 roughness 0.05}

}

sphere { <0, 0, 0>, 2
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
  translate <0, 4, 0>
}

sphere { <0, 0, 0>, 2
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
  translate <0, -4, 0>
}

sphere { <0, 0, 0>, 2
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
  translate <4, 0, 1>
}

sphere { <0, 0, 0>, 1.5
  pigment { color rgbf <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.6 refraction 1.0 ior 1.333}
  translate <-4, 0, -1>
}
