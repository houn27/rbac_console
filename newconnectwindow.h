#ifndef NEWCONNECTWINDOW_H
#define NEWCONNECTWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
class NewConnectWindow;
}

class NewConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewConnectWindow(QWidget *parent = nullptr);
    ~NewConnectWindow();
    void delTableConfigByIdx(int idx);

signals:
    void CreateConnectSig();


private slots:
    void on_test_btn_clicked();

    void on_cancel_btn_clicked();

    void on_save_btn_clicked();

    void fillTable(int idx);

    void delConnect(int idx);


private:
    Ui::NewConnectWindow *ui;
    int cur_connect_idx;
};

#endif // NEWCONNECTWINDOW_H
