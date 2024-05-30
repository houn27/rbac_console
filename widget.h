#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSettings>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QPoint>
#include <QSqlTableModel>


extern int connectIdx;
extern QSqlDatabase db;

class EditUserWindow;
class EditRoleWindow;
class EditPerWindow;
class NewConnectWindow;
class SelectRowWindow;
class DelRowWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}

QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void getConnect();
    void getUserTable(int connect_idx);
    void getRoleTable(int connect_idx);
    void getPerTable(int connect_idx);
    bool createConnect(QString db_name,QString host,QString username,QString pwd);
    void connectByIdx(int idx);


private slots:
    void onNewConnectBtnClicked();


    void on_connect_list_customContextMenuRequested(const QPoint &pos);

    // void connectListHeaderRightClicked(const QPoint &pos);

    // void on_connect_list_itemDoubleClicked(QTreeWidgetItem *item, int column);


    void on_add_btn_clicked();

    void on_del_btn_clicked();


    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_connect_list_itemDoubleClicked(QTreeWidgetItem *item, int column);

signals:
    void SelectRowSig(QString id,QString table_name);
    void DelRowSig(QString id,QString table_name);
    void FillConnectSig(int idx);
    void FillUserSig(int idx);
    void FillRoleSig(int idx);
    void FillPerSig(int idx);
    void DelConnectSig(int idx);

private:
    Ui::Widget *ui;
    NewConnectWindow *window;
    EditUserWindow *editUserWindow;
    EditRoleWindow *editRoleWindow;
    EditPerWindow *editPerWindow;
    SelectRowWindow *selectRowWindow;
    DelRowWindow *delRowWindow;
    QSettings *settings;
    QSqlTableModel *model;
};
#endif // WIDGET_H
