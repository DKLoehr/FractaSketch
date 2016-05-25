# FractaSketch
=============
This is a remake of an old program, FractaSketch, which was originally created by Peter Van Roy at the Catholic University of Louvain. Its purpose is to generate fractals iteratively from a template.

The source code was written in C++ and uses the SFML Library. The source code is available at https://github.com/DKLoehr/FractaSketch

=========================
## Installation Instructions:
Extract the .zip file to whatever directory you wish to keep it in. 
For Windows, ensure that the file VeraMono.ttf is in the same directory as the executable.
To run, double-click the .exe file (Windows) or the app (Macs)

==================
## Usage Instructions:

### User Interface:
Along the top of the screen there are several buttons. The first 6 refer to line types, and the next three to grid types.

Most lines, when drawn, will have an arrowhead; this will be matched with the arrowhead on the baseline during iterations. Thus the line type determines the orientation of the replacing element after iteration. The line types designate where on the line the arrowhead would appear if line was drawn horizontally to the right. Static lines have no arrowhead and are not replaced during iterations. Hidden lines are "fuzzier", have no arrowhead, and are neither replaced nor shown during iteration.

There are three grid settings (none, square, hex), which you can change by clicking on the appropriate buttons on the top. If there is a grid, everything will snap to it.

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

### Drawing the Fractal
To create a fractal from your template, hit the Draw button. This will create a new window on top of the previous one with your template on it. 

You can then click the buttons on top (or use the number keys again) to go to the corresponding level of iteration. Note that due to its position, the 0 key is mapped to level 10, not level 0. The tilde key is mapped to level 0 instead. Currently, the maximum level is 10. However, the drawing is currently highly unoptimized, so it is not recommended that you go above level 5 or 6 except on any but the simplest templates.

There is a known issue where you have to click on the titlebar of the new window before you can click on the buttons; the number keys seem to work regardless. 

To exit the program, close the main window. Feel free to close the iteration window when you're done with it; it won't stop the program and will come back next time you draw.

Changelog:

v0.2 Beta:
* Added ability to select lines and points on the template
* Lines and points can now be deleted
* Lines can change type after being placed
* Points can be moved
* The entire template can be moved around the window

v0.1:
*Initial Release!