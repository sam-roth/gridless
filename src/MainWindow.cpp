#include "MainWindow.hpp"
#include "Canvas.hpp"
#include "Inspector.hpp"
#include <QToolBar>
#include <QDockWidget>
#include <QAction>
#include <QActionGroup>
#include <QUndoStack>
#include <QUndoView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), canvas(nullptr), inspector(nullptr), undoStack(nullptr)
{
    setupUI();
    resize(1024, 768);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI()
{
    // Create undo stack
    undoStack = new QUndoStack(this);

    // Create file toolbar (A)
    auto *fileToolbar = addToolBar(tr("File"));
    fileToolbar->addAction(tr("New"));
    fileToolbar->addAction(tr("Open"));
    fileToolbar->addAction(tr("Save"));

    fileToolbar->addSeparator();

    auto *undoAction = undoStack->createUndoAction(this, tr("Undo"));
    undoAction->setShortcut(QKeySequence::Undo);
    fileToolbar->addAction(undoAction);

    auto *redoAction = undoStack->createRedoAction(this, tr("Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    fileToolbar->addAction(redoAction);

    fileToolbar->addSeparator();

    auto deleteAction = fileToolbar->addAction(tr("Delete Object"));
    deleteAction->setShortcut(QKeySequence::Delete);

    // Create tool chest toolbar (B)
    auto *toolsToolbar = new QToolBar(tr("Tools"), this);
    addToolBar(Qt::LeftToolBarArea, toolsToolbar);

    // Create action group for mutually exclusive tool selection
    auto *toolGroup = new QActionGroup(this);

    auto *selectAction = toolsToolbar->addAction(tr("Select"));
    selectAction->setCheckable(true);
    selectAction->setChecked(true);
    selectAction->setActionGroup(toolGroup);
    selectAction->setShortcut(QKeySequence(Qt::Key_S));

    auto *pointAction = toolsToolbar->addAction(tr("Point"));
    pointAction->setCheckable(true);
    pointAction->setActionGroup(toolGroup);
    pointAction->setShortcut(QKeySequence(Qt::Key_P));

    auto *viewAction = toolsToolbar->addAction(tr("View"));
    viewAction->setCheckable(true);
    viewAction->setActionGroup(toolGroup);
    viewAction->setShortcut(QKeySequence(Qt::Key_V));

    // Create canvas (C)
    canvas = new Canvas(undoStack, this);
    setCentralWidget(canvas);

    // Connect tool actions
    connect(selectAction, &QAction::triggered, this, &MainWindow::onSelectToolActivated);
    connect(pointAction, &QAction::triggered, this, &MainWindow::onPointToolActivated);
    connect(viewAction, &QAction::triggered, this, &MainWindow::onViewToolActivated);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteObjectTriggered);

    // Create inspector dock widget (D)
    inspector = new Inspector(canvas, undoStack, this);
    auto *inspectorDock = new QDockWidget(tr("Inspector"), this);
    inspectorDock->setWidget(inspector);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);

    // Connect canvas selection to inspector
    connect(canvas, &Canvas::selectionChanged, inspector, &Inspector::setSelectedObject);
}

void MainWindow::onSelectToolActivated()
{
    canvas->setToolMode("Select");
}

void MainWindow::onPointToolActivated()
{
    canvas->setToolMode("Point");
}

void MainWindow::onViewToolActivated()
{
    canvas->setToolMode("View");
}

void MainWindow::onDeleteObjectTriggered()
{
    canvas->deleteSelectedItems();
}

