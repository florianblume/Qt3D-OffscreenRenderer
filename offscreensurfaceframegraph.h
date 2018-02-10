#ifndef OFFSCREENLAYER_H
#define OFFSCREENLAYER_H

#include "texturerendertarget.h"

#include <QOffscreenSurface>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QRenderTargetSelector>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QCamera>

// The OffscreenSurfaceFrameGraph class is where the magic happens.
// It is responsible for rendering the scene to an "offscreen" surface (ie. a texture),
// rather than directly to a QWindow. This means that the render contents can be
// taken and used within other QWidgets.
class OffscreenSurfaceFrameGraph : public Qt3DRender::QRenderSurfaceSelector
{
    Q_OBJECT
public:
    OffscreenSurfaceFrameGraph(Qt3DCore::QNode* parent = nullptr, Qt3DRender::QCamera *camera = nullptr, const QSize &size = QSize(500, 500));

    void setSize(const QSize &size);
    Qt3DCore::QNode *getRenderTargetSelector();

private:
    TextureRenderTarget *textureTarget;
    QOffscreenSurface *offscreenSurface;
    Qt3DRender::QRenderTargetSelector *renderTargetSelector;
    Qt3DRender::QViewport *viewport;
    Qt3DRender::QClearBuffers *clearBuffers;
    Qt3DRender::QCameraSelector *cameraSelector;
    Qt3DRender::QCamera *camera;
};

#endif // OFFSCREENLAYER_H
