#ifndef SELECTROWWINDOW_H
#define SELECTROWWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class SelectRowWindow;
}

class SelectRowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SelectRowWindow(QWidget *parent = nullptr);
    ~SelectRowWindow();


private slots:
    void on_cancel_btn_clicked();

    void on_add_btn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void getTable(QString id, QString table_name);

private:
    Ui::SelectRowWindow *ui;
    QSettings *settings;
    QSqlTableModel *model;
    int select_row;
    QString cur_table_name;
    QString cur_id;
};

#endif // SELECTROWWINDOW_H
