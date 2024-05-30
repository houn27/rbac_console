#ifndef EDITTABLEWINDOW_H
#define EDITTABLEWINDOW_H

#include <QWidget>

namespace Ui {
class EditTableWindow;
}

class EditTableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditTableWindow(QWidget *parent = nullptr);
    ~EditTableWindow();

private:
    Ui::EditTableWindow *ui;
};

#endif // EDITTABLEWINDOW_H
