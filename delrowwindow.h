#ifndef DELROWWINDOW_H
#define DELROWWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class DelRowWindow;
}

class DelRowWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DelRowWindow(QWidget *parent = nullptr);
    ~DelRowWindow();

private slots:
    void on_cancel_btn_clicked();

    void on_del_btn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void getTable(QString id, QString table_name);

private:
    Ui::DelRowWindow *ui;
    QSettings *settings;
    QSqlTableModel *model;
    int select_row;
    QString cur_table_name;
    QString cur_id;
};

#endif // DELROWWINDOW_H
