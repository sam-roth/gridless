#include "Inspector.hpp"
#include <QVBoxLayout>
#include <QLabel>

Inspector::Inspector(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    auto *titleLabel = new QLabel(tr("Inspector"), this);
    QFont font = titleLabel->font();
    font.setBold(true);
    titleLabel->setFont(font);

    layout->addWidget(titleLabel);
    layout->addStretch();

    setLayout(layout);
    setMaximumWidth(200);
}
