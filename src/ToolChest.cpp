#include "ToolChest.hpp"
#include <QVBoxLayout>
#include <QPushButton>

ToolChest::ToolChest(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    auto *selectBtn = new QPushButton(tr("Select"), this);
    auto *pointBtn = new QPushButton(tr("Point"), this);
    auto *viewBtn = new QPushButton(tr("View"), this);

    layout->addWidget(selectBtn);
    layout->addWidget(pointBtn);
    layout->addWidget(viewBtn);
    layout->addStretch();

    setLayout(layout);
    setMaximumWidth(100);
}
