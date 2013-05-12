Saul Villatoro
CSC-473-01
Ray Tracer Part 3

To run: Make using the "make" command. Then run the program with the following syntax: 

./raytrace [image_width] [image_height] -S [p,g] -I [input_file]

the -S flag indicates the shading model, 'p' for Phong, and 'g' for Gaussian.

All the .pov files on your website under "Project 1 - part 3, shading and shadows" are located in the "povray_files" folder.

Once the program has run, the output file will be created wherever the input file was located.

My renders of the .pov files in "povray_files" are located in the "my_renders" folder. They are all rendered using the Phong shading model. I used the Schlick approximation for my defractions, so all objects with refraction are completely transparent.

Problems: My refractions are correct for the most part. There are still some bugs I am trying to find, however i feel my output is satisfactory enough and demonstrates defraction for the most part. recurse_simp.pov, recurse_simp2.pov, and recurses.pov came out much darker than your files. I am not sure if this is due to differences in implemention, or if it is me computing lighting incorrectly. I will look into this. I have altered the two files ("modified_recurse_simp.pov", "modified_recurse_simp2.pov", and "modified_recurses.pov" respectively) to have brighter lights, so that you can see the recursive defraction. (For "recurses.pov" I also commented out the Box and Cone as we have no implemeneted those yet.)

Triangle shading works as intended.

recurse_simp2.pov in the "povray_files" folder was modified only to change some spacing so that it would play nice with my parser.

If you wish to compile and run all .pov files under "Project 1 - part 3, shading and shadows" one after the other, run the "make refraction" command.

Times:

simple_refract.pov: ~6 seconds
(modified_)recurse_simp.pov: ~58 seconds
(modified_)recurse_simp2.pov: ~52 seconds
recurse.pov: ~1542 seconds
simple_tri.pov: ~13 seconds
ugly_part.pov: ~106 seconds
my_scene.pov: ~46 seconds
