#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class Canvas;
class Inspector;
class QUndoStack;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectToolActivated();
    void onPointToolActivated();
    void onViewToolActivated();
    void onDeleteObjectTriggered();

private:
    void setupUI();

    Canvas *canvas;
    Inspector *inspector;
    QUndoStack *undoStack;
};

#endif // MAINWINDOW_HPP
