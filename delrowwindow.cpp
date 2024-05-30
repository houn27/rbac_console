#include "delrowwindow.h"
#include "ui_delrowwindow.h"
#include "widget.h"


DelRowWindow::DelRowWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DelRowWindow)
{
    ui->setupUi(this);
    model=nullptr;
    settings=new QSettings("setting.ini", QSettings::IniFormat);
    ui->tableView->setSelectionMode(QTableView::SingleSelection);
}

DelRowWindow::~DelRowWindow()
{
    delete ui;
    delete settings;
    delete model;
}

void DelRowWindow::on_cancel_btn_clicked()
{
    this->close();
}


void DelRowWindow::on_del_btn_clicked()
{
    //get mapping table info
    settings->beginReadArray("tables");
    settings->setArrayIndex(connectIdx);
    QString role_table_name=settings->value("role_table_name").toString();
    QString per_table_name=settings->value("per_table_name").toString();

    //get row in mapping table
    if(cur_table_name==role_table_name){
        QString role_id_col=settings->value("role_id_col").toString();
        QString user_role_user_id_col=settings->value("user_role_user_id_col").toString();
        QString user_role_role_id_col=settings->value("user_role_role_id_col").toString();
        QString user_role_table_name=settings->value("user_role_table_name").toString();

        int role_row_idx = ui->tableView->currentIndex().row();
        int role_col_idx = model->fieldIndex(role_id_col);
        QString role_id =model->data(model->index(role_row_idx,role_col_idx)).toString();
        model->setTable(user_role_table_name);
        model->setQuery("select * from "+user_role_table_name+" where "+user_role_user_id_col+" = "+cur_id+" and "+user_role_role_id_col+" = "+role_id);

    }else if (cur_table_name==per_table_name){
        QString per_id_col=settings->value("per_id_col").toString();
        QString role_per_table_name=settings->value("role_per_table_name").toString();
        QString role_per_role_id_col=settings->value("role_per_role_id_col").toString();
        QString role_per_per_id_col=settings->value("role_per_per_id_col").toString();

        int per_row_idx = ui->tableView->currentIndex().row();
        int per_col_idx = model->fieldIndex(per_id_col);
        QString per_id =model->data(model->index(per_row_idx,per_col_idx)).toString();

        model->setTable(role_per_table_name);
        model->setQuery("select * from "+role_per_table_name+" where "+role_per_role_id_col+" = "+cur_id+" and "+role_per_per_id_col+" = "+per_id);

    }

    settings->endArray();

    //remove the row in mapping table
    if(model->rowCount()>0){
        model->removeRow(0);

        // pop up comfirm window
        int ok = QMessageBox::warning(this, "Delete", "Delete this row？", QMessageBox::No, QMessageBox::Yes);

        if (ok == QMessageBox::No) {
            model->revertAll();
            return;
        }

        // save
        model->submitAll();
    }

    //refresh
    getTable(cur_id, cur_table_name);
}

void DelRowWindow::getTable(QString id, QString table_name){

    settings->beginReadArray("tables");
    settings->setArrayIndex(connectIdx);
    QString role_table_name=settings->value("role_table_name").toString();
    QString per_table_name=settings->value("per_table_name").toString();

    if(db.open()){
        if(model!=nullptr)  delete model;
        model = new QSqlTableModel(this,db);

        model->setTable(table_name);
        ui->tableView->setModel(model);
        model->select();

        cur_table_name=table_name;
        cur_id=id;
        if(cur_table_name==role_table_name){
            QString role_id_col=settings->value("role_id_col").toString();
            QString user_role_user_id_col=settings->value("user_role_user_id_col").toString();
            QString user_role_role_id_col=settings->value("user_role_role_id_col").toString();
            QString user_role_table_name=settings->value("user_role_table_name").toString();

            model->setQuery("select * from "+role_table_name+" where "+role_id_col+" in (select "+user_role_role_id_col+" from "+user_role_table_name+" where "+user_role_user_id_col+"="+cur_id+")");

        }else if (cur_table_name==per_table_name){
            QString per_id_col=settings->value("per_id_col").toString();
            QString role_per_table_name=settings->value("role_per_table_name").toString();
            QString role_per_role_id_col=settings->value("role_per_role_id_col").toString();
            QString role_per_per_id_col=settings->value("role_per_per_id_col").toString();

            model->setQuery("select * from "+per_table_name+" where "+per_id_col+" in (select "+role_per_per_id_col+" from "+role_per_table_name+" where "+role_per_role_id_col+"="+cur_id+")");
        }
    }
    settings->endArray();

}



void DelRowWindow::on_tableView_clicked(const QModelIndex &index)
{
    select_row=index.row();
}


void DelRowWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index=ui->tableView->indexAt(pos);
    if( !index.isValid() )   return;
    else{
        select_row=index.row();
    }
}

