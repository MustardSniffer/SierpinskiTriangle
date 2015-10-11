## E10 - Sierpinski Triangle

In-class exercise 10 for generating a Sierpinski triangle.

### Controls

* `+` / `-` = Increase / decrease number of iterations
* `up` / `down` = Increase / decrease scale

Because the assignment is to draw everything in a single draw call,
the number of iterations is clamped to the range [0, 5]. However,
if you want to go crazy you can edit `AppClass.cpp` near the top
and set `DRAW_ALL_INSTANCES` to true. This will allow you to go up
to 13 iterations while drawing the entire thing in batches of 250
triangles (which is what the shader supports).