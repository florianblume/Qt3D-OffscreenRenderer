#include "offscreenenginedelegate.h"

OffscreenEngineDelegate::OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label) :
    engine(engine),
    label(label) {
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}

void OffscreenEngineDelegate::onImageRendered() {
    label->setPixmap(QPixmap::fromImage(reply->image()));
    disconnect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
    delete reply;
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}
