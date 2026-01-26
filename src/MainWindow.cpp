#include "MainWindow.hpp"
#include "Canvas.hpp"
#include "Inspector.hpp"
#include <QToolBar>
#include <QDockWidget>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), canvas(nullptr), inspector(nullptr)
{
    setupUI();
    resize(1024, 768);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI()
{
    // Create file toolbar (A)
    auto *fileToolbar = addToolBar(tr("File"));
    fileToolbar->addAction(tr("New"));
    fileToolbar->addAction(tr("Open"));
    fileToolbar->addAction(tr("Save"));

    // Create tool chest toolbar (B)
    auto *toolsToolbar = addToolBar(tr("Tools"));
    toolsToolbar->addAction(tr("Select"));
    toolsToolbar->addAction(tr("Point"));
    toolsToolbar->addAction(tr("View"));

    // Create canvas (C)
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    // Create inspector dock widget (D)
    inspector = new Inspector(this);
    auto *inspectorDock = new QDockWidget(tr("Inspector"), this);
    inspectorDock->setWidget(inspector);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);
}

