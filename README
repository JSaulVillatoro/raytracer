Saul Villatoro
CSC-473-01
Ray Tracer Part 5

To run: Make using the "make" command. Then run the program with the following syntax: 

./raytrace [image_width] [image_height] -S [p,g] -I [input_file]

the -S flag indicates the shading model, 'p' for Phong, and 'g' for Gaussian.

Once the program has run, the output file will be created wherever the input file was located.

My renders of the .pov files in "povray_files" are located in the "my_renders" folder. They are all rendered using the Phong shading model. I used the Schlick approximation for my defractions, so all objects with refraction are completely transparent. There is no anti-aliasing for any of my renders. There is 1 level of recursion in the global illumination.

Problems: While there is some global illumination, I am not sure if it is implemented correctly. global_illum_room.tga shows the global illumination, although very faint. For the cornell.pov file, my output was very dark, however it matches the outcome of the official povray program somewhat, so I feel it is correct. My parser was not written to handle some of the scales in the cornell.pov file, so they are modified in a way my parser can interpret.
