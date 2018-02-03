# Qt3D-OffscreenRenderer
This project is based on the Qt 3D basic shapes C++ example (https://doc.qt.io/qt-5.10/qt3d-basicshapes-cpp-example.html).

It renders the whole scene using a QOffscreenSurface offline and displays the image in a QLabel.
To get the image to resize adjust the OffscreenEngines rendering size on resize of the widget.
I guess the rest should be self-explanatory.

This is supposed to show how to construct an offline framegraph and save everyone who needs such
a renderer the hours of trial and error and the despair I encountered.

## The framegraph

                                root
                                 |
                            renderSettings
                                 |
                         renderSurfaceSelector
                                 |
                          renderTargetSelector
                                 |
             ---------------------------------------
             |                   |                 |
        renderTarget        clearBuffers        viewport
             |                                     |
     renderTargetOutput                      cameraSelector
             |
         texture2D

## Note

Somehow the first image that is captured is blank and without rendered objects. I suspected the problem
to be that the render capture was triggered right after the clear buffers node. But it doesn't seem
to have any effect when we place the capture node anywhere else. So basically the first image has to
be skipped.

To enable depth tests just add a QRenderStateSet as a child to the camera selector and a QDepthTest as a child to the render state set and add it as a state. Then, in the render target add a texture to the depth attatchment point. This is it.

I experiemented with multisampling, and added a QMultiSampleAntiAliasing render state to the render state set and instead of adding a QTexture2D used a QMultisampleTexture2D but it gave me version errors with OpenGL. If maybe someone gets it running they can fork the project and I can then do a pull.

# Disclaimer

Please note that part of the code was written by the Qt Company or KDAB and they hold the respective
copyright. For further information read the copyright notice in the source code.
