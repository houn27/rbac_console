#include "viewrowwindow.h"
#include "ui_viewrowwindow.h"

ViewRowWindow::ViewRowWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewRowWindow)
{
    ui->setupUi(this);
}

ViewRowWindow::~ViewRowWindow()
{
    delete ui;
}
