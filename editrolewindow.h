#ifndef EDITROLEWINDOW_H
#define EDITROLEWINDOW_H

#include <QWidget>
#include <QSettings>


namespace Ui {
class EditRoleWindow;
}

class EditRoleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditRoleWindow(QWidget *parent = nullptr);
    ~EditRoleWindow();

// signals:
//     void EditRoleSig();

private slots:
    void on_save_btn_clicked();

    void on_cancel_btn_clicked();

    void fillTable(int idx);

private:
    Ui::EditRoleWindow *ui;
};

#endif // EDITROLEWINDOW_H
