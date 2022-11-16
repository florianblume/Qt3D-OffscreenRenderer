#include "offscreenenginedelegate.h"

#include <QTimer>

OffscreenEngineDelegate::OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label) :
    engine(engine),
    label(label),
    reply(nullptr)
{
    // Immediately request a render capture.
    // Every time we receive a reply, we then
    // re-request a new capture.
    QTimer::singleShot(200, this, &OffscreenEngineDelegate::requestRenderCapture); // Rendering MUST called after QApplication::exec() call
}

OffscreenEngineDelegate::~OffscreenEngineDelegate()
{
    delete reply;
}

void OffscreenEngineDelegate::requestRenderCapture()
{
    delete reply;
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}

void OffscreenEngineDelegate::onImageRendered()
{
    // Get the image from the reply and display it in the label.
    label->setPixmap(QPixmap::fromImage(reply->image()));

    // Request another render capture.
    requestRenderCapture();
}
