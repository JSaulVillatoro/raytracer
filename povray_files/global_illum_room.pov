// cs473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}




light_source {<0, 0, 0> color rgb <1.5, 1.5, 1.5>}


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


