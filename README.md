# FractaSketch
=============
This is a remake of an old program, FractaSketch, which was originally created by Peter Van Roy at the Catholic University of Louvain. Its purpose is to generate fractals iteratively from a template.

The source code was written in C++ and uses the SFML Library. The source code is available at https://github.com/DKLoehr/FractaSketch

=========================
## Installation Instructions:
Extract the .zip file to whatever directory you wish to keep it in. That's it!

==================
## Usage Instructions:

### Running the program:
To run, double-click the .exe file (Windows) or the app (Macs).
If the application fails to load, look for a FractaSketch_log.txt file in the same directory as the executable. Examine the contents of the file for more information. If the file does not exist, then the program never got a chance to start at all; this likely means that your operating system is preventing it from running.

The most common cause of failed starts is a missing font file; if so, the log will contain a message to this effect. If you are on Windows, ensure that the VeraMono.ttf file which came with the program is in the same directory as the executable (this file is not needed on Macs).

### User Interface:
Along the top of the screen there are several buttons. The first 6 refer to line types, and the next three to grid types.

Most lines, when drawn, will have an arrowhead; this will be matched with the arrowhead on the baseline during iterations. Thus the line type determines the orientation of the replacing element after iteration. The line types designate where on the line the arrowhead would appear if line was drawn horizontally to the right. Static lines have no arrowhead and are not replaced during iterations. Hidden lines are "fuzzier", have no arrowhead, and are neither replaced nor shown during iteration.

There are three grid settings (none, square, triangle), which you can change by clicking on the appropriate buttons on the top. If there is a grid, everything will snap to it.

### Creating a Template:
Click once on the grid to start drawing. Click again to put down a line of whatever type you have selected. You can change the type by clicking the buttons or using the number keys 1-6 (not the numpad, though).

Keep doing this until you have all the lines you want. When you're done, right click to finish drawing. A dotted line will appear between your first and last points; this is the __baseline__. The entire figure is called the __template__.

Once your template has been drawn, you can edit it in various ways. 
* To select a line or point, click on it; it will turn red. Only one line or point can be selected at a time. To deselect it, click anywhere not on the template.
* To change a line's type, select it and then select a new type by clicking the buttons or using the number keys.
* To move a point, select it and then click and drag to move it around the screen.
* To split a line, select it and then again to bifurcate it. This will create a two new lines that meet at the midpoint of the original line.
* To delete a line or point, select it and then hit Backspace or Delete.
* To move the entire template around on the screen, click and drag anywhere not on the template.

To erase the template completely, click the Clear button. Note that once you have finished your template (i.e. a baseline has appeared), the only way to add new lines is by splitting segments.

If weird stuff is happening and you can't edit your template, hit Clear.

If you've got a template you particularly like, you can save it to a file and load it again later! To save a template, simply click on the box next to the "Save" button, and type in the filename you wish to use, then click Save. If the filename does not end in ".fsk", then the extension ".fsk" will be appended to it. 

To load a file later, type the filename of the file you wish to load (including the .fs extension), and hit the Load button. This will overwrite your existing template, if any.

### Drawing the Fractal
To create a fractal from your template, hit the Draw button. This will create a new window on top of the previous one with your template on it. 

You can then click the buttons on top (you can't use the number keys here) to go to the corresponding level of iteration. Note that due to its position, the 0 key is mapped to the special level "Infinity", not level 0. The tilde key is mapped to level 0 instead.

Iterating fractals to high levels of complexity is a very slow operation. To speed this up, the program stops replacing lines once they have reached a certain length (currently a few pixels). The special level "Infinity" will iterate the fractal until all lines are at or below that length. Accordingly, attempting to reach the infinity level for a template whose lines shrink slowly will take a while and may cause the program to run out of memory. Attempty to reach the infinity level for a template whose lines grow is a Bad Idea.

You can save the results of your iteration to a file by specifying the file name and hitting the "save" button. The path may be either absolute or relative; in the latter case, the base directory is the one with the FractaSketch executable. Make sure you use '\' and not '/' if you're on Windows! When saving, the extension must be ".png"; this will be appended to the filename if it is not already present.

To exit the program, close the main window. Feel free to close the iteration window when you're done with it; it won't stop the program and will come back next time you draw.

=============
## Configuring FractaSketch

Some of FractaSketch's parameters can be configured by the user. To edit them, open the "FractaSketch_config.txt" file in the same directory as the FractaSketch executable. To modify a value, simply change the number on the right-hand side of the equals sign.

=============
## Changelog:

##### v0.2.5:
* Add config file
* Add log file

##### v0.2.4:
* Add ability to save/load templates
* Add ability to save iteration results to a file

###### v0.2.3:
* Make high-level iteration MUCH faster
* Add infinity level
* Change triangle grid back to hex grid by popular demand

###### v0.2.2:
* Changed hex grid to triangle grid (same as before, but also displays the midpoint of each hex)
* Fix bug on macs where the progra would not correctly detect when the mouse was being held down
* Fix bug causing program to crash when removing the last points or lines from a template

###### v0.2.1:
* Added ability to select lines and points on the template
* Lines and points can now be deleted
* Lines can change type after being placed
* Points can be moved
* The entire template can be moved around the window

###### v0.1:
* Initial Release!