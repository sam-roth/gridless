#include "Inspector.hpp"
#include <QVBoxLayout>
#include <QLabel>

Inspector::Inspector(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->addStretch();

    setLayout(layout);
    setMaximumWidth(200);
}
