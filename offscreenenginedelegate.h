#ifndef OFFSCREENENGINEDELEGATE_H
#define OFFSCREENENGINEDELEGATE_H

#include "offscreenengine.h"
#include <QLabel>
#include <Qt3DRender/QRenderCaptureReply>

// Example class that requests frames from the offscreen engine.
// The engine's framegraph generates the frame, which notifies this delegate.
// Once the frame is set in the provided label, a new frame is requested.
class OffscreenEngineDelegate : public QObject
{
    Q_OBJECT
public:
    OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label);
    virtual ~OffscreenEngineDelegate();

private:
    OffscreenEngine *engine;
    QLabel *label;
    Qt3DRender::QRenderCaptureReply *reply;

private slots:
    void onImageRendered();

private:
    void requestRenderCapture();
};

#endif // OFFSCREENENGINEDELEGATE_H
