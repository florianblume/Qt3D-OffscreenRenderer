# Qt3D-OfflineRenderer
This project is based on the Qt 3D basic shapes C++ example.

It renders the whole scene using a QOffscreenSurface offline and displays the image in a QLabel.
To get the image to resize adjust the OffscreenEngines rendering size on resize of the widget.
I guess the rest should be self-explanatory.

This is supposed to show how to construct an offline framegraph and save everyone who needs such
a renderer the hours of trial and error and the despair I encountered.

# Disclaimer

Please note that part of the code was written by the Qt Company or KDAB and they hold the respective
copyright. For further information read the copyright notice in the source code.
