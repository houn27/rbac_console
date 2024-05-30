#ifndef VIEWROWWINDOW_H
#define VIEWROWWINDOW_H

#include <QWidget>

namespace Ui {
class ViewRowWindow;
}

class ViewRowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ViewRowWindow(QWidget *parent = nullptr);
    ~ViewRowWindow();

private:
    Ui::ViewRowWindow *ui;
};

#endif // VIEWROWWINDOW_H
