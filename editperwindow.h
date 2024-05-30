#ifndef EDITPERWINDOW_H
#define EDITPERWINDOW_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class EditPerWindow;
}

class EditPerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditPerWindow(QWidget *parent = nullptr);
    ~EditPerWindow();

private slots:
    void on_cancel_btn_clicked();

    void on_save_btn_clicked();

    void fillTable(int idx);

private:
    Ui::EditPerWindow *ui;
};

#endif // EDITPERWINDOW_H
