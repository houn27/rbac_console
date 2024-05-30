#include "selectrowwindow.h"
#include "ui_selectrowwindow.h"
#include "widget.h"

SelectRowWindow::SelectRowWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SelectRowWindow)
{
    ui->setupUi(this);
    model=nullptr;
    settings=new QSettings("setting.ini", QSettings::IniFormat);
    //ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setSelectionMode(QTableView::SingleSelection);
}

SelectRowWindow::~SelectRowWindow()
{
    delete settings;
    delete model;
    delete ui;
}

void SelectRowWindow::on_cancel_btn_clicked()
{
    this->close();
}



void SelectRowWindow::on_add_btn_clicked()
{
    //get table name
    settings->beginReadArray("tables");
    settings->setArrayIndex(connectIdx);
    QString role_table_name=settings->value("role_table_name").toString();
    QString per_table_name=settings->value("per_table_name").toString();
    QString user_role_table_name=settings->value("user_role_table_name").toString();
    QString role_per_table_name=settings->value("role_per_table_name").toString();
    QString user_role_role_id_col=settings->value("user_role_role_id_col").toString();
    QString user_role_user_id_col=settings->value("user_role_user_id_col").toString();
    QString role_per_role_id_col=settings->value("role_per_role_id_col").toString();
    QString role_per_per_id_col=settings->value("role_per_per_id_col").toString();
    QString role_id_col=settings->value("role_id_col").toString();
    QString per_id_col=settings->value("per_id_col").toString();

    // insert row in mapping table
    if(cur_table_name==role_table_name){
        //insert {user_id,selected_role_id} in user_role table
        QString role_id=model->data(model->index(select_row, model->fieldIndex(role_id_col))).toString();

        model->setTable(user_role_table_name);

        //check if add an existing role
        model->setQuery("select * from "+user_role_table_name+" where "+user_role_user_id_col+" = "+cur_id+" and "+user_role_role_id_col+" = "+role_id);
        int mapping_row_count=model->rowCount();
        if(mapping_row_count!=0){
            QMessageBox::information(this,"Notice","This role has been assigned to the user");
        }else{
            // add
            model->select();
            mapping_row_count=model->rowCount();
            model->insertRow(mapping_row_count);
            model->setData(model->index(mapping_row_count, model->fieldIndex(user_role_role_id_col)), QVariant::fromValue(role_id.toLong()));
            model->setData(model->index(mapping_row_count, model->fieldIndex(user_role_user_id_col)), QVariant::fromValue(cur_id.toLong()));
            model->submit();
        }

    }else if(cur_table_name==per_table_name){
        //insert {per_id,selected_role_id} in role_per table
        QString per_id=model->data(model->index(select_row, model->fieldIndex(per_id_col))).toString();
        model->setTable(role_per_table_name);
        model->select();

        model->setQuery("select * from "+role_per_table_name+" where "+role_per_role_id_col+" = "+cur_id+" and "+role_per_per_id_col+" = "+per_id);
        int mapping_row_count=model->rowCount();
        if(mapping_row_count!=0){
            QMessageBox::information(this,"Notice","This permission has been assigned to the role");
        }else{
            int mapping_row_count=model->rowCount();
            model->insertRow(mapping_row_count);
            model->setData(model->index(mapping_row_count, model->fieldIndex(role_per_per_id_col)), QVariant::fromValue(per_id.toLong()));
            model->setData(model->index(mapping_row_count, model->fieldIndex(role_per_role_id_col)), QVariant::fromValue(cur_id.toLong()));
            model->submit();

        }

    }
    settings->endArray();
    this->close();
}



void SelectRowWindow::getTable(QString id, QString table_name){
    qDebug()<<id<<table_name;

    if(db.open()){
        if(model!=nullptr)  delete model;
        model = new QSqlTableModel(this,db);

        model->setTable(table_name);
        ui->tableView->setModel(model);
        model->select();

        cur_table_name=table_name;
        cur_id=id;
    }

}


void SelectRowWindow::on_tableView_clicked(const QModelIndex &index)
{
    select_row=index.row();
}


void SelectRowWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index=ui->tableView->indexAt(pos);
    if( !index.isValid() )   return;
    else{
        select_row=index.row();
    }
}

