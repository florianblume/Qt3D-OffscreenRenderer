#include "offscreensurfaceframegraph.h"
/*
 * An overview of the frame graph used by this class:
 *
 *                 (1)| RenderTargetSelector |
 *                               |
 *                      +=================+
 *                      V                 V
 *              (2)| ClearBuffers |  (3)| Viewport |
 *                                           V
 *                                  (4)| CameraSelector |
 *
 * To summarise the Qt3D documentation, the frame graph is processed in depth-first order.
 * Each node sets some state. Therefore you can read the graph as saying:
 * "Given the action for this node, perform the actions of each of its children in order."
 *
 * 1. The render target selector sets the current render target (an OpenGL texture buffer).
 * 2. The specified buffers (here, colour and depth) are cleared.
 * 3. The viewport area to render into is set up.
 * 4. The appropriate camera is chosen.
 *
 * Further children can be added to the render target selector in order to perform subsequent
 * actions. In this example project, the offscreen engine adds a render capture node after
 * the existing children in the frame graph.
 *
 * An example extension of the framegraph can be the one that draws an image in the background:
 *
 *      https://github.com/Sonnentierchen/Qt3D-BackgroundImage
 */

OffscreenSurfaceFrameGraph::OffscreenSurfaceFrameGraph(Qt3DCore::QNode* parent, Qt3DRender::QCamera *camera, const QSize &size) :
    Qt3DRender::QRenderSurfaceSelector(parent),
    camera(camera)
{
    // Firstly, create the offscreen surface. This will take the place
    // of a QWindow, allowing us to render our scene without one.
    offscreenSurface = new QOffscreenSurface();
    offscreenSurface->setFormat(QSurfaceFormat::defaultFormat());
    offscreenSurface->create();

    // Hook it up to the frame graph.
    setSurface(offscreenSurface);
    setExternalRenderTargetSize(size);

    // Create a texture to render into. This acts as the buffer that
    // holds the rendered image.
    renderTargetSelector = new Qt3DRender::QRenderTargetSelector(this);
    textureTarget = new TextureRenderTarget(renderTargetSelector, size);
    renderTargetSelector->setTarget(textureTarget);

    // Create a node used for clearing the required buffers.
    clearBuffers = new Qt3DRender::QClearBuffers(renderTargetSelector);
    clearBuffers->setClearColor(QColor(100, 100, 100, 255));
    clearBuffers->setBuffers(Qt3DRender::QClearBuffers::ColorDepthBuffer);

    // Create a viewport node. The viewport here just covers the entire render area.
    viewport = new Qt3DRender::QViewport(renderTargetSelector);
    viewport->setNormalizedRect(QRectF(0.0, 0.0, 1.0, 1.0));

    // Create a camera selector node, and tell it to use the camera we've ben given.
    cameraSelector = new Qt3DRender::QCameraSelector(viewport);
    cameraSelector->setCamera(camera);
}

void OffscreenSurfaceFrameGraph::setSize(const QSize &size)
{
    textureTarget->setSize(size);
    setExternalRenderTargetSize(size);
}

Qt3DCore::QNode *OffscreenSurfaceFrameGraph::getRenderTargetSelector()
{
    return renderTargetSelector;
}
