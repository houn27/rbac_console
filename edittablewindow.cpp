#include "edittablewindow.h"
#include "ui_edittablewindow.h"

EditTableWindow::EditTableWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditTableWindow)
{
    ui->setupUi(this);
}

EditTableWindow::~EditTableWindow()
{
    delete ui;
}
