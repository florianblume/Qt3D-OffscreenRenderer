#include "offscreenenginedelegate.h"

OffscreenEngineDelegate::OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label) :
    engine(engine),
    label(label) {
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}

void OffscreenEngineDelegate::onImageRendered() {
    QImage image = reply->image();
    label->setPixmap(QPixmap::fromImage(image));
    if (numberOfRenderedImages == 1)
        reply->saveImage("test.png");
    numberOfRenderedImages++;
    disconnect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
    delete reply;
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}
