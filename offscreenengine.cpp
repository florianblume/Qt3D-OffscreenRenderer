#include "offscreenengine.h"

OffscreenEngine::OffscreenEngine(Qt3DRender::QCamera *camera, const QSize &size)
{
    sceneRoot = nullptr;

    // Set up the engine and the aspects that we want to use.
    aspectEngine = new Qt3DCore::QAspectEngine();
    renderAspect = new Qt3DRender::QRenderAspect(Qt3DRender::QRenderAspect::Threaded); // Only threaded mode seems to work right now.
    logicAspect = new Qt3DLogic::QLogicAspect();

    aspectEngine->registerAspect(renderAspect);
    aspectEngine->registerAspect(logicAspect);

    // Create the root entity of the engine.
    // This is not the same as the 3D scene root: the QRenderSettings
    // component must be held by the root of the QEntity tree,
    // so it is added to this one. The 3D scene is added as a subtree later,
    // in setSceneRoot().
    Qt3DCore::QEntityPtr root(new Qt3DCore::QEntity());
    renderSettings = new Qt3DRender::QRenderSettings(root.data());
    root->addComponent(renderSettings);

    // Create the offscreen frame graph, which will manage all of the resources required
    // for rendering without a QWindow.
    offscreenFrameGraph = new OffscreenSurfaceFrameGraph(renderSettings, camera, size);

    // Set this frame graph to be in use.
    renderSettings->setActiveFrameGraph(offscreenFrameGraph);

    // Add a render capture node to the frame graph.
    // This is set as the next child of the render target selector node,
    // so that the capture will be taken from the specified render target
    // once all other rendering operations have taken place.
    renderCapture = new Qt3DRender::QRenderCapture(offscreenFrameGraph->getRenderTargetSelector());

    // Set the root entity of the engine. This causes the engine to begin running.
    aspectEngine->setRootEntity(root);
}

OffscreenEngine::~OffscreenEngine()
{
    // Setting a null root entity shuts down the engine.
    aspectEngine->setRootEntity(Qt3DCore::QEntityPtr());

    // Not sure if the following is strictly required, as it may
    // happen automatically when the engine is destroyed.
    aspectEngine->unregisterAspect(logicAspect);
    aspectEngine->unregisterAspect(renderAspect);
    delete logicAspect;
    delete renderAspect;

    delete aspectEngine;
}

void OffscreenEngine::setSceneRoot(Qt3DCore::QNode *sceneRoot)
{
    // Make sure any existing scene root is unparented.
    if ( this->sceneRoot )
    {
        this->sceneRoot->setParent(static_cast<Qt3DCore::QNode*>(nullptr));
    }

    // Parent the incoming scene root to our current root entity.
    this->sceneRoot = sceneRoot;
    this->sceneRoot->setParent(aspectEngine->rootEntity().data());
}

Qt3DRender::QRenderCapture* OffscreenEngine::getRenderCapture()
{
    return renderCapture;
}

void OffscreenEngine::setSize(const QSize &size)
{
    offscreenFrameGraph->setSize(size);
}
