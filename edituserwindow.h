#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QWidget>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserWindow(QWidget *parent = nullptr);
    ~EditUserWindow();

// signals:
//     void EditUserSig();

private slots:
    void on_save_btn_clicked();

    void on_cancel_btn_clicked();

    void fillTable(int idx);

private:
    Ui::EditUserWindow *ui;
};

#endif // EDITUSERWINDOW_H
