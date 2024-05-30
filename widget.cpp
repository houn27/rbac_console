#include "widget.h"
#include "./ui_widget.h"
#include "editrolewindow.h"
#include "edituserwindow.h"
#include "newconnectwindow.h"
#include "editperwindow.h"
#include "selectrowwindow.h"
#include "delrowwindow.h"

int connectIdx;
QSqlDatabase db;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->connect_list->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->connect_list->setHeaderHidden(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    //intial pointer
    window=new NewConnectWindow();
    editUserWindow= new EditUserWindow();
    editRoleWindow= new EditRoleWindow();
    editPerWindow= new EditPerWindow();
    selectRowWindow=new SelectRowWindow();
    delRowWindow=new DelRowWindow();
    settings=new QSettings("setting.ini", QSettings::IniFormat);
    model=nullptr;

    connect(ui->new_connect_btn,&QPushButton::clicked,this,&Widget::onNewConnectBtnClicked);
    //connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(on_tableView_customContextMenuRequested(QPoint)));
    connect(window,&NewConnectWindow::CreateConnectSig,this,&Widget::getConnect);
    connect(this,SIGNAL(SelectRowSig(QString,QString)),selectRowWindow,SLOT(getTable(QString,QString)));
    connect(this,SIGNAL(DelRowSig(QString,QString)),delRowWindow,SLOT(getTable(QString,QString)));
    connect(this,SIGNAL(FillConnectSig(int)),window,SLOT(fillTable(int)));
    connect(this,SIGNAL(FillUserSig(int)),editUserWindow,SLOT(fillTable(int)));
    connect(this,SIGNAL(FillRoleSig(int)),editRoleWindow,SLOT(fillTable(int)));
    connect(this,SIGNAL(FillPerSig(int)),editPerWindow,SLOT(fillTable(int)));
    connect(this,SIGNAL(DelConnectSig(int)),window,SLOT(delConnect(int)));
    getConnect();

}

Widget::~Widget()
{
    ui->connect_list->clear();
    delete ui;
    delete window;
    delete editUserWindow;
    delete editRoleWindow;
    delete editPerWindow;
    delete selectRowWindow;
    delete delRowWindow;
    delete settings;
    delete model;
    db.close();
}


void Widget::onNewConnectBtnClicked()
{
    window->show();
    emit FillConnectSig(-1);
}

void Widget::getConnect(){
    ui->connect_list->clear();
    int size = settings->beginReadArray("connects");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        //connection name
        QTreeWidgetItem* connect_item=new QTreeWidgetItem();
        connect_item->setText(0,settings->value("connect_name").toString());
        connect_item->setDisabled(true);
        ui->connect_list->addTopLevelItem(connect_item);

        //table button
        QTreeWidgetItem* user_item=new QTreeWidgetItem();
        user_item->setText(0,"User");
        user_item->setDisabled(true);

        connect_item->addChild(user_item);

        QTreeWidgetItem* role_item=new QTreeWidgetItem();
        role_item->setText(0,"Role");
        role_item->setDisabled(true);
        connect_item->addChild(role_item);

        QTreeWidgetItem* per_item=new QTreeWidgetItem();
        per_item->setText(0,"Permission");
        per_item->setDisabled(true);
        connect_item->addChild(per_item);

    }

    settings->endArray();
}

void Widget::getUserTable(int connect_idx){
    //get table info from QSettings
    //settings=new QSettings("setting.ini", QSettings::IniFormat);
    settings->beginReadArray("tables");
    settings->setArrayIndex(connect_idx);
    QString user_table_name=settings->value("user_table_name").toString();

    //connect db and show in tableview
    if(db.open()){
        model->setTable(user_table_name);
        ui->tableView->setModel(model);
        ui->add_btn->setEnabled(true);
        ui->del_btn->setEnabled(true);
        model->select();

    }
    settings->endArray();

}

void Widget::getRoleTable(int connect_idx){
    //get table info from QSettings
    settings->beginReadArray("tables");
    settings->setArrayIndex(connect_idx);
    QString role_table_name=settings->value("role_table_name").toString();

    //connect db and show in tableview
    if(db.open()){
        model->setTable(role_table_name);
        ui->tableView->setModel(model);
        ui->add_btn->setEnabled(true);
        ui->del_btn->setEnabled(true);
        model->select();
    }
    settings->endArray();
}

void Widget::getPerTable(int connect_idx){
    //get table info from QSettings
    settings->beginReadArray("tables");
    settings->setArrayIndex(connect_idx);
    QString per_table_name=settings->value("per_table_name").toString();

    //connect db and show in tableview
    if(db.open()){
        model->setTable(per_table_name);
        ui->tableView->setModel(model);
        ui->add_btn->setEnabled(true);
        ui->del_btn->setEnabled(true);
        model->select();
    }
    settings->endArray();
}

bool Widget::createConnect(QString db_name,QString host,QString username,QString pwd){
    //stop previous connect
    db.close();

    //create connect db
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(db_name);
    db.setHostName(host);
    db.setUserName(username);
    db.setPassword(pwd);

    if(db.open()){
        if(model!=nullptr)  delete model;
        model = new QSqlTableModel(this,db);
        return true;
    }else{
        return false;
    }
}

void Widget::connectByIdx(int idx){

    //get connect param from Qsetting
    settings->beginReadArray("connects");
    settings->setArrayIndex(idx);
    QString db_name=settings->value("db_name").toString();
    QString host=settings->value("host").toString();
    QString username=settings->value("username").toString();
    QString pwd=settings->value("pwd").toString();

    bool is_open=createConnect(db_name,host,username,pwd);

    if(is_open){
        QMessageBox::information(this,"Notice","Connect Successfully");

        // add table button
        int connect_list_size=ui->connect_list->topLevelItemCount();
        for(int i=0;i<connect_list_size;i++){
            QTreeWidgetItem *item=ui->connect_list->topLevelItem(i);
            if(i==idx){
                item->setDisabled(false);
                item->child(0)->setDisabled(false);
                item->child(1)->setDisabled(false);
                item->child(2)->setDisabled(false);
            }else{
                item->setDisabled(true);
                item->child(0)->setDisabled(true);
                item->child(1)->setDisabled(true);
                item->child(2)->setDisabled(true);
            }
        }

        connectIdx=idx;

    }else{
        QMessageBox::information(this,"Notice","Connect Failed");
    }

    settings->endArray();
}

void Widget::on_connect_list_customContextMenuRequested(const QPoint &pos)
{
    int cur_idx;
    //get selected
    QTreeWidgetItem *curItem=ui->connect_list->itemAt(pos);
    if( curItem == NULL )   return;
    else{
        QTreeWidgetItem *topItem = curItem;
        while (topItem->parent() != nullptr) {
            topItem = topItem->parent();
        }
        cur_idx=ui->connect_list->indexOfTopLevelItem(topItem);
    }

    //create menu
    QMenu *menu=new QMenu;

    //right click at conenct
    if(ui->connect_list->itemAt(pos)->childCount()){
        //fill menu
        QAction* connect_act=menu->addAction("Open Connection");
        QAction* edit_act=menu->addAction("Edit Connection");
        QAction* delete_act=menu->addAction("Delete Connection");

        //show menu
        //QAction *selectedAction=menu->exec(QCursor::pos());
        QAction *selectedAction=menu->exec(ui->connect_list->header()->mapToGlobal(pos));


        //run function based on actions
        if(selectedAction==connect_act){
            connectByIdx(cur_idx);
        }else if(selectedAction==edit_act){
            window->show();
            emit FillConnectSig(cur_idx);
        }else if(selectedAction==delete_act){
            emit DelConnectSig(cur_idx);
        }



    //right click at table
    }else{
        QAction* view_act=menu->addAction("View Table");
        QAction* edit_act=menu->addAction("Edit Table");

        //check if table has been config
        settings->beginReadArray("tables");
        settings->setArrayIndex(cur_idx);
        if((ui->connect_list->indexAt(pos).row()==0 && settings->value("user_table_name").toString().isNull()) || cur_idx!=connectIdx ){
            view_act->setDisabled(true);
        }else if((ui->connect_list->indexAt(pos).row()==1 && settings->value("role_table_name").toString().isNull()) || cur_idx!=connectIdx){
            view_act->setDisabled(true);
        }else if((ui->connect_list->indexAt(pos).row()==2 && settings->value("per_table_name").toString().isNull()) || cur_idx!=connectIdx){
            view_act->setDisabled(true);
        }

        settings->endArray();

        //show menu
        QAction *selectedAction=menu->exec(QCursor::pos());

        //run function based on actions
        if(selectedAction==view_act){
            if(ui->connect_list->indexAt(pos).row()==0) {
                getUserTable(cur_idx);
            }else if(ui->connect_list->indexAt(pos).row()==1){
                getRoleTable(cur_idx);
            }
            else if(ui->connect_list->indexAt(pos).row()==2){
                getPerTable(cur_idx);
            }
        }else if(selectedAction==edit_act){
            //user table
            if(ui->connect_list->indexAt(pos).row()==0) {
                editUserWindow->show();
                emit FillUserSig(cur_idx);
            //role table
            }else if(ui->connect_list->indexAt(pos).row()==1){
                editRoleWindow->show();
                emit FillRoleSig(cur_idx);
            //permission table
            }else if(ui->connect_list->indexAt(pos).row()==2){
                editPerWindow->show();
                emit FillPerSig(cur_idx);
            }
        }
    }

    menu->clear();
    delete menu;
}




void Widget::on_add_btn_clicked()
{
    //get table name
    settings->beginReadArray("tables");
    settings->setArrayIndex(connectIdx);


    //model fetch 256 rows by default
    while (model->canFetchMore()) {
        model->fetchMore();
    }

    // insert an empty row
    int row_count=model->rowCount();
    model->insertRow(row_count);
    model->setData(model->index(row_count, 1), "");
    model->submit();

    // enable edit
    ui->tableView->setEditTriggers(QTableView::DoubleClicked);
    ui->tableView->scrollToBottom();


    settings->endArray();
}


void Widget::on_del_btn_clicked()
{
    // remove the row
    auto index = ui->tableView->currentIndex();
    model->removeRow(index.row());

    // pop up comfirm window
    int ok = QMessageBox::warning(this, "Delete", "Delete this row？", QMessageBox::No, QMessageBox::Yes);

    if (ok == QMessageBox::No) {
        model->revertAll();
        return;
    }

    // save
    model->submitAll();

    //refresh
    model->select();
}



void Widget::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    int row_count=0;
    QModelIndex index=ui->tableView->indexAt(pos);
    if( !index.isValid() )   return;
    else{
        row_count=index.row();
    }

    //get table name
    settings->beginReadArray("tables");
    settings->setArrayIndex(connectIdx);
    QString role_table_name=settings->value("role_table_name").toString();
    QString user_table_name=settings->value("user_table_name").toString();
    QString per_table_name=settings->value("per_table_name").toString();

    //show menu
    QMenu *menu=new QMenu;
    if(model->tableName()==user_table_name){
        QAction* role_act=menu->addAction("Go to role...");
        QAction* add_act=menu->addAction("Add belonging role...");
        QAction* del_act=menu->addAction("Delete belonging role...");
        QAction *selectedAction=menu->exec(QCursor::pos());

        QString user_id_col=settings->value("user_id_col").toString();
        QString user_id=model->data(model->index(row_count, model->fieldIndex(user_id_col))).toString();
        if(selectedAction==role_act){

            QString role_id_col=settings->value("role_id_col").toString();
            QString user_role_user_id_col=settings->value("user_role_user_id_col").toString();
            QString user_role_role_id_col=settings->value("user_role_role_id_col").toString();
            QString user_role_table_name=settings->value("user_role_table_name").toString();
            model->setTable(role_table_name);
            ui->tableView->setModel(model);
            ui->add_btn->setEnabled(false);
            ui->del_btn->setEnabled(false);
            model->setQuery("select * from "+role_table_name+" where "+role_id_col+" in (select "+user_role_role_id_col+" from "+user_role_table_name+" where "+user_role_user_id_col+"="+user_id+")");
            //cur_user_id=user_id;
        }else if(selectedAction==add_act){
            selectRowWindow->show();
            emit SelectRowSig(user_id,role_table_name);
        }else if(selectedAction==del_act){
            delRowWindow->show();
            emit DelRowSig(user_id,role_table_name);
        }
    }else if(model->tableName()==role_table_name){
        QAction* per_act=menu->addAction("Go to permission...");
        QAction* add_act=menu->addAction("Add belonging permission...");
        QAction* del_act=menu->addAction("Delete belonging permission...");
        QAction *selectedAction=menu->exec(QCursor::pos());

        QString role_id_col=settings->value("role_id_col").toString();
        QString role_id=model->data(model->index(row_count, model->fieldIndex(role_id_col))).toString();
        if(selectedAction==per_act){
            QString per_id_col=settings->value("per_id_col").toString();
            QString role_per_table_name=settings->value("role_per_table_name").toString();
            QString role_per_role_id_col=settings->value("role_per_role_id_col").toString();
            QString role_per_per_id_col=settings->value("role_per_per_id_col").toString();
            model->setTable(per_table_name);
            ui->tableView->setModel(model);
            ui->add_btn->setEnabled(false);
            ui->del_btn->setEnabled(false);
            model->setQuery("select * from "+per_table_name+" where "+per_id_col+" in (select "+role_per_per_id_col+" from "+role_per_table_name+" where "+role_per_role_id_col+"="+role_id+")");
            //cur_role_id=role_id;
        }else if(selectedAction==add_act){
            selectRowWindow->show();
            emit SelectRowSig(role_id,per_table_name);
        }else if(selectedAction==del_act){
            delRowWindow->show();
            emit DelRowSig(role_id,per_table_name);
        }
    }else{
        menu->clear();
    }

    settings->endArray();
    menu->clear();
    delete menu;

}


void Widget::on_connect_list_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int cur_idx;
    QTreeWidgetItem *topItem = item;
    while (topItem->parent() != nullptr) {
        topItem = topItem->parent();
    }
    cur_idx=ui->connect_list->indexOfTopLevelItem(topItem);

    if(item->childCount()){
        connectByIdx(cur_idx);
    }else{
        if(ui->connect_list->indexFromItem(item,column).row()==0) {
            getUserTable(cur_idx);
        }else if(ui->connect_list->indexFromItem(item,column).row()==1){
            getRoleTable(cur_idx);
        }
        else if(ui->connect_list->indexFromItem(item,column).row()==2){
            getPerTable(cur_idx);
        }
    }

}

