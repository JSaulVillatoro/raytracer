Saul Villatoro
CSC-473-01
Ray Tracer Part 4

To run: Make using the "make" command. Then run the program with the following syntax: 

./raytrace [image_width] [image_height] -S [p,g] -I [input_file]

the -S flag indicates the shading model, 'p' for Phong, and 'g' for Gaussian.

All the .pov files on your website under "Project 1 - part 4, shading and shadows" are located in the "povray_files" folder.

Once the program has run, the output file will be created wherever the input file was located.

My renders of the .pov files in "povray_files" are located in the "my_renders" folder. They are all rendered using the Phong shading model. I used the Schlick approximation for my defractions, so all objects with refraction are completely transparent.

Problems: I could not get bunny.pov to work. I recall someone running into a similar problem in class, however I fail to remember the solution. Additionally, gnarly.pov looks different from your output,  but looks similar to Povray's output. My times are slower than they should be, however I have found some pieces of code that could be made more efficient and will look into those.

Anti-Aliasing, Boxes, and the Bounding Volume Hierarchy work as intended. All files are run using anti-aliasing, for the next part I will implement an option to enable/disable it (most likely a command line argument).

Times:

my_new_scene.pov: 24.73 seconds
my_new_scene.pov(anti-alias): 212.8 seconds
gnarly.pov: 69.55 seconds
gnarly.pov(anti-alias): 599.05 seconds
balls2.pov: 100.78
balls2.pov(anti-alias): 843.23 seconds
bunny.pov: none
bunny.pov(anti-alias): none

