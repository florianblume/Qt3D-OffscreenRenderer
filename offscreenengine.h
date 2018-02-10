#ifndef OFFSCREENENGINE_H
#define OFFSCREENENGINE_H

#include "offscreensurfaceframegraph.h"

#include <QSharedPointer>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QNode>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QRenderCapture>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QRenderAspect>
#include <Qt3DLogic/QLogicAspect>

// The OffscreenEngine brings together various Qt3D classes that are required in order to
// perform basic scene rendering. Of these, the most important for this project is the OffscreenSurfaceFrameGraph.
// Render captures can be requested, and the capture contents used within other widgets (see OffscreenEngineDelegate).
class OffscreenEngine
{
public:
    OffscreenEngine(Qt3DRender::QCamera *camera, const QSize &size);
    ~OffscreenEngine();

    void setSceneRoot(Qt3DCore::QNode *sceneRoot);
    Qt3DRender::QRenderCapture *getRenderCapture();
    void setSize(const QSize &size);

private:
    // We need all of the following in order to render a scene:
    Qt3DCore::QAspectEngine *aspectEngine;              // The aspect engine, which holds the scene and related aspects.
    Qt3DRender::QRenderAspect *renderAspect;            // The render aspect, which deals with rendering the scene.
    Qt3DLogic::QLogicAspect *logicAspect;               // The logic aspect, which runs jobs to do with synchronising frames.
    Qt3DRender::QRenderSettings *renderSettings;        // The render settings, which control the general rendering behaviour.
    Qt3DRender::QRenderCapture *renderCapture;          // The render capture node, which is appended to the frame graph.
    OffscreenSurfaceFrameGraph *offscreenFrameGraph;    // The frame graph, which allows rendering to an offscreen surface.
    Qt3DCore::QNode *sceneRoot;                         // The scene root, which becomes a child of the engine's root entity.
};

#endif // OFFSCREENENGINE_H
