// SPDX-License-Identifier: GPL-2.0+

#include "DsoConfigScopePage.h"

DsoConfigScopePage::DsoConfigScopePage(DsoSettings *settings, QWidget *parent) : QWidget(parent), settings(settings) {
    // Initialize lists for comboboxes
    QStringList interpolationStrings;
    interpolationStrings << tr("Off") << tr("Linear") << tr("Sinc");

    // Initialize elements
    interpolationLabel = new QLabel(tr("Interpolation"));
    interpolationComboBox = new QComboBox();
    interpolationComboBox->addItems(interpolationStrings);
    interpolationComboBox->setCurrentIndex(settings->view.interpolation);
    digitalPhosphorDepthLabel = new QLabel(tr("Digital phosphor depth"));
    digitalPhosphorDepthSpinBox = new QSpinBox();
    digitalPhosphorDepthSpinBox->setMinimum(2);
    digitalPhosphorDepthSpinBox->setMaximum(99);
    digitalPhosphorDepthSpinBox->setValue(settings->view.digitalPhosphorDepth);

    graphLayout = new QGridLayout();
    graphLayout->addWidget(interpolationLabel, 1, 0);
    graphLayout->addWidget(interpolationComboBox, 1, 1);
    graphLayout->addWidget(digitalPhosphorDepthLabel, 2, 0);
    graphLayout->addWidget(digitalPhosphorDepthSpinBox, 2, 1);

    graphGroup = new QGroupBox(tr("Graph"));
    graphGroup->setLayout(graphLayout);

    cursorsLabel = new QLabel(tr("Position"));
    cursorsComboBox = new QComboBox();
    cursorsComboBox->addItem(tr("Left"), Qt::LeftToolBarArea);
    cursorsComboBox->addItem(tr("Right"), Qt::RightToolBarArea);
    cursorsComboBox->setCurrentIndex(settings->view.cursorGridPosition == Qt::LeftToolBarArea ? 0 : 1);

    cursorsLayout = new QGridLayout();
    cursorsLayout->addWidget(cursorsLabel, 0, 0);
    cursorsLayout->addWidget(cursorsComboBox, 0, 1);

    cursorsGroup = new QGroupBox(tr("Cursors"));
    cursorsGroup->setLayout(cursorsLayout);

    slidersLabel = new QLabel(tr("Large size"));
    slidersCheckBox = new QCheckBox();
    slidersCheckBox->setChecked(settings->view.largeSliders);

    slidersLayout = new QGridLayout();
    slidersLayout->addWidget(slidersLabel, 0, 0);
    slidersLayout->addWidget(slidersCheckBox, 0, 1);

    slidersGroup = new QGroupBox(tr("Sliders"));
    slidersGroup->setLayout(slidersLayout);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(graphGroup);
    mainLayout->addWidget(cursorsGroup);
    mainLayout->addWidget(slidersGroup);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

/// \brief Saves the new settings.
void DsoConfigScopePage::saveSettings() {
    settings->view.interpolation = (Dso::InterpolationMode)interpolationComboBox->currentIndex();
    settings->view.digitalPhosphorDepth = digitalPhosphorDepthSpinBox->value();
    settings->view.cursorGridPosition = (Qt::ToolBarArea)cursorsComboBox->currentData().toUInt();
    settings->view.largeSliders = slidersCheckBox->isChecked();
}
