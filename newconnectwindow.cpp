#include "newconnectwindow.h"
#include "ui_newconnectwindow.h"

NewConnectWindow::NewConnectWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewConnectWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Create New Connection");
    cur_connect_idx=-1;
}

NewConnectWindow::~NewConnectWindow()
{
    delete ui;
}

void NewConnectWindow::on_test_btn_clicked()
{
    //close previous connection
    //db.close();

    //QString port=ui->port_edit->text();
    QString host=ui->host_edit->text();
    QString username=ui->username_edit->text();
    QString pwd=ui->pwd_edit->text();
    QString db_name=ui->db_name_edit->text();

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(db_name);
    db.setHostName(host);
    db.setUserName(username);
    db.setPassword(pwd);

    if(db.open()){
        QMessageBox::information(this,"Notice","Connect Successfully");

    }else{
        QMessageBox::information(this,"Notice","Connect Failed");
    }

    db.close();

}


void NewConnectWindow::on_cancel_btn_clicked()
{
    this->close();

}


void NewConnectWindow::on_save_btn_clicked()
{
    // get QSetting obj and its index
    QSettings settings("./setting.ini", QSettings::IniFormat);
    int size = settings.beginReadArray("connects");

    //check connect name
    //QString connect_name=ui->connect_name_edit->text();
    // if(size>0){
    //     for (int i = 0; i < size; ++i) {
    //         settings.setArrayIndex(i);
    //         if(settings.value("connect_name")==connect_name){
    //             QMessageBox::information(this,"Notice","Connect name has been used");
    //             return;
    //         }
    //     }
    // }
    settings.endArray();

    settings.beginWriteArray("connects");
    // Add existing items back to the array
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        if(i!=cur_connect_idx){

            settings.setValue("connect_name", settings.value("connect_name"));
            settings.setValue("host", settings.value("host"));
            settings.setValue("port", settings.value("port"));
            settings.setValue("username", settings.value("username"));
            settings.setValue("pwd", settings.value("pwd"));
            settings.setValue("db_name", settings.value("db_name"));
        }else{
            //set value
            settings.setValue("connect_name",ui->connect_name_edit->text());
            settings.setValue("host",ui->host_edit->text());
            settings.setValue("port",ui->port_edit->text());
            settings.setValue("username",ui->username_edit->text());
            settings.setValue("pwd",ui->pwd_edit->text());
            settings.setValue("db_name",ui->db_name_edit->text());
        }
    }
    if(cur_connect_idx==-1){
        settings.setArrayIndex(size);
        settings.setValue("connect_name",ui->connect_name_edit->text());
        settings.setValue("host",ui->host_edit->text());
        settings.setValue("port",ui->port_edit->text());
        settings.setValue("username",ui->username_edit->text());
        settings.setValue("pwd",ui->pwd_edit->text());
        settings.setValue("db_name",ui->db_name_edit->text());
    }

    //save
    settings.endArray();
    settings.sync();
    emit CreateConnectSig();
    this->close();
}

void NewConnectWindow::fillTable(int idx){
    cur_connect_idx=idx;
    QSettings settings("./setting.ini", QSettings::IniFormat);
    settings.beginReadArray("connects");
    settings.setArrayIndex(idx);

    ui->connect_name_edit->setText(settings.value("connect_name").toString());
    ui->host_edit->setText(settings.value("host").toString());
    ui->port_edit->setText(settings.value("port").toString());
    ui->username_edit->setText(settings.value("username").toString());
    ui->pwd_edit->setText(settings.value("pwd").toString());
    ui->db_name_edit->setText(settings.value("db_name").toString());

    settings.endArray();
}

void NewConnectWindow::delConnect(int idx){
    QSettings settings("./setting.ini", QSettings::IniFormat);
    int size=settings.beginReadArray("connects");
    settings.endArray();

    settings.beginWriteArray("connects",size-1);
    int new_index = 0;
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);

        //get original config
        QString connect_name=settings.value("connect_name").toString();
        QString host=settings.value("host").toString();
        QString port=settings.value("port").toString();
        QString username=settings.value("username").toString();
        QString pwd=settings.value("pwd").toString();
        QString db_name=settings.value("db_name").toString();

        //copy to the new idx
        if (i != idx) {
            settings.setArrayIndex(new_index++);
            settings.setValue("connect_name",connect_name);
            settings.setValue("host", host);
            settings.setValue("port", port);
            settings.setValue("username", username);
            settings.setValue("pwd", pwd);
            settings.setValue("db_name", db_name);
        }
    }
    settings.endArray();
    settings.sync();

    // delete associated table config
    delTableConfigByIdx(idx);

    emit CreateConnectSig();
}

void NewConnectWindow::delTableConfigByIdx(int idx){
    // get QSetting obj
    QSettings settings("./setting.ini", QSettings::IniFormat);

    // get size
    int size = settings.beginReadArray("tables");
    settings.endArray();

    //set value, add existing items back to the array
    settings.beginWriteArray("tables",size-1);
    int new_idx=0;
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        QString user_table_name=settings.value("user_table_name").toString();
        QString user_id_col=settings.value("user_id_col").toString();
        QString user_name_col=settings.value("user_name_col").toString();
        QString role_table_name=settings.value("role_table_name").toString();
        QString role_id_col=settings.value("role_id_col").toString();
        QString user_role_table_name=settings.value("user_role_table_name").toString();
        QString user_role_role_id_col=settings.value("user_role_role_id_col").toString();
        QString user_role_user_id_col=settings.value("user_role_user_id_col").toString();
        QString default_role_id=settings.value("default_role_id").toString();
        QString per_table_name=settings.value("per_table_name").toString();
        QString per_id_col=settings.value("per_id_col").toString();
        QString role_per_table_name=settings.value("role_per_table_name").toString();
        QString role_per_role_id_col=settings.value("role_per_role_id_col").toString();
        QString role_per_per_id_col=settings.value("role_per_per_id_col").toString();

        if(i!=idx){
            settings.setArrayIndex(new_idx++);
            settings.setValue("user_table_name", user_table_name);
            settings.setValue("user_id_col", user_id_col);
            settings.setValue("user_name_col", user_name_col);
            settings.setValue("role_table_name",role_table_name);
            settings.setValue("role_id_col",role_id_col);
            settings.setValue("user_role_table_name",user_role_table_name);
            settings.setValue("user_role_role_id_col",user_role_role_id_col);
            settings.setValue("user_role_user_id_col",user_role_user_id_col);
            settings.setValue("default_role_id",default_role_id);
            settings.setValue("per_table_name",per_table_name);
            settings.setValue("per_id_col",per_id_col);
            settings.setValue("role_per_table_name",role_per_table_name);
            settings.setValue("role_per_role_id_col",role_per_role_id_col);
            settings.setValue("role_per_per_id_col",role_per_per_id_col);
        }

    }

    settings.endArray();
    settings.sync();
}


