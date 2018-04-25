#include "texturerendertarget.h"

TextureRenderTarget::TextureRenderTarget(Qt3DCore::QNode *parent, const QSize &size) :
    Qt3DRender::QRenderTarget(parent),
    size(size)
{
    // The lifetime of the objects created here is managed
    // automatically, as they become children of this object.

    // Create a render target output for rendering colour.
    output = new Qt3DRender::QRenderTargetOutput(this);
    output->setAttachmentPoint(Qt3DRender::QRenderTargetOutput::Color0);

    // Create a texture to render into.
    texture = new Qt3DRender::QTexture2D(output);
    texture->setSize(size.width(), size.height());
    texture->setFormat(Qt3DRender::QAbstractTexture::RGBA8_UNorm);
    texture->setMinificationFilter(Qt3DRender::QAbstractTexture::Linear);
    texture->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);

    // Hook the texture up to our output, and the output up to this object.
    output->setTexture(texture);
    addOutput(output);
}

Qt3DRender::QTexture2D* TextureRenderTarget::getTexture()
{
    return texture;
}

void TextureRenderTarget::setSize(const QSize &size)
{
    this->size = size;
    texture->setSize(size.width(), size.height());
}
