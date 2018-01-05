#ifndef OFFSCREENENGINEDELEGATE_H
#define OFFSCREENENGINEDELEGATE_H

#include "offscreenengine.h"
#include <QLabel>
#include <Qt3DRender/QRenderCaptureReply>

class OffscreenEngineDelegate : public QObject
{

    Q_OBJECT

public:
    OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label);

private:
    OffscreenEngine *engine;
    QLabel *label;
    Qt3DRender::QRenderCaptureReply *reply;

private slots:
    void onImageRendered();
};

#endif // OFFSCREENENGINEDELEGATE_H
