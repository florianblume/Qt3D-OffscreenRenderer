#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QStringLiteral("Basic shapes"));

    // The label which will act as the 3D viewport.
    // Frames that are rendered by the offscreen engine will be
    // displayed in this label as QImages.
    QLabel *graphicsLabel = new QLabel();
    graphicsLabel->setGeometry(QRect(0, 0, 1200, 800));
    graphicsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set up layouts for the UI.
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(graphicsLabel, 1);
    hLayout->addLayout(vLayout);

    // Root entity in the 3D scene.
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Set up a camera to point at the shapes.
    Qt3DRender::QCamera *cameraEntity = new Qt3DRender::QCamera(rootEntity);
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 1200.0f/800.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    // Set up a light to illuminate the shapes.
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // Allow the camera to be controlled.
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Create a SceneModifier, which connects UI elements to show or hide their respective shapes.
    // Given the root entity, the SceneModifier internally adds the respective shapes as children.
    modifier = new SceneModifier(rootEntity);

    // Create the offscreen engine. This is the object which is responsible for handling the 3D scene itself.
    offscreenEngine = new OffscreenEngine(cameraEntity, QSize(1200, 800));

    // The offscreen engine delegate handles requesting frames from the engine, and drawing their results in the graphics label.
    offscreenEngineDelegate = new OffscreenEngineDelegate(offscreenEngine, graphicsLabel);

    // Set our scene to be rendered by the offscreen engine.
    offscreenEngine->setSceneRoot(rootEntity);

    // Create UI.
    QCommandLinkButton *info = new QCommandLinkButton();
    info->setText(QStringLiteral("Qt3D ready-made meshes"));
    info->setDescription(QString::fromLatin1("Qt3D provides several ready-made meshes, like torus, cylinder, cone, "
                                             "cube, plane and sphere."));
    info->setIconSize(QSize(0,0));

    QCheckBox *torusCB = new QCheckBox();
    torusCB->setChecked(true);
    torusCB->setText(QStringLiteral("Torus"));

    QCheckBox *coneCB = new QCheckBox();
    coneCB->setChecked(true);
    coneCB->setText(QStringLiteral("Cone"));

    QCheckBox *cylinderCB = new QCheckBox();
    cylinderCB->setChecked(true);
    cylinderCB->setText(QStringLiteral("Cylinder"));

    QCheckBox *cuboidCB = new QCheckBox();
    cuboidCB->setChecked(true);
    cuboidCB->setText(QStringLiteral("Cuboid"));

    QCheckBox *planeCB = new QCheckBox();
    planeCB->setChecked(true);
    planeCB->setText(QStringLiteral("Plane"));

    QCheckBox *sphereCB = new QCheckBox();
    sphereCB->setChecked(true);
    sphereCB->setText(QStringLiteral("Sphere"));

    vLayout->addWidget(info);
    vLayout->addWidget(torusCB);
    vLayout->addWidget(coneCB);
    vLayout->addWidget(cylinderCB);
    vLayout->addWidget(cuboidCB);
    vLayout->addWidget(planeCB);
    vLayout->addWidget(sphereCB);

    // Connect the check boxes to the scene modifier.
    QObject::connect(torusCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enableTorus);
    QObject::connect(coneCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enableCone);
    QObject::connect(cylinderCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enableCylinder);
    QObject::connect(cuboidCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enableCuboid);
    QObject::connect(planeCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enablePlane);
    QObject::connect(sphereCB, &QCheckBox::stateChanged,
                     modifier, &SceneModifier::enableSphere);

    torusCB->setChecked(true);
    coneCB->setChecked(true);
    cylinderCB->setChecked(true);
    cuboidCB->setChecked(true);
    planeCB->setChecked(true);
    sphereCB->setChecked(true);
}

MainWidget::~MainWidget()
{
    // Clean up after ourselves.
    delete offscreenEngineDelegate;
    delete modifier;
    delete offscreenEngine;
}
