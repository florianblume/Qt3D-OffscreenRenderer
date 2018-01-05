# Qt3D-OfflineRenderer
This project is based on the Qt 3D basic shapes C++ example (https://doc.qt.io/qt-5.10/qt3d-basicshapes-cpp-example.html).

It renders the whole scene using a QOffscreenSurface offline and displays the image in a QLabel.
To get the image to resize adjust the OffscreenEngines rendering size on resize of the widget.
I guess the rest should be self-explanatory.

This is supposed to show how to construct an offline framegraph and save everyone who needs such
a renderer the hours of trial and error and the despair I encountered.

## Note

Somehow the first image that is captured is blank and without rendered objects. I suspected the problem
to be that the render capture was triggered right after the clear buffers node. But it doesn't seem
to have any effect when we place the capture node anywhere else. So basically the first image has to
be skipped.

To incorporate depth there is some inspiration in https://github.com/alpqr/q3dpostproc. Probably one has
to add another RenderTargetOutput that stores the depth values and add a QDepthTest node to the framegraph.

# Disclaimer

Please note that part of the code was written by the Qt Company or KDAB and they hold the respective
copyright. For further information read the copyright notice in the source code.
