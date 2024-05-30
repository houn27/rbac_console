#include "editperwindow.h"
#include "ui_editperwindow.h"
#include "widget.h"

EditPerWindow::EditPerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditPerWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Table Configuration");
}

EditPerWindow::~EditPerWindow()
{
    delete ui;
}

void EditPerWindow::on_cancel_btn_clicked()
{
    this->close();
}


void EditPerWindow::on_save_btn_clicked()
{
    // get QSetting obj
    QSettings settings("./setting.ini", QSettings::IniFormat);

    // get size
    int size = settings.beginReadArray("tables");
    settings.endArray();

    //set value, add existing items back to the array
    settings.beginWriteArray("tables",std::max(size,connectIdx+1));
    for (int i = 0; i <= std::max(size-1,connectIdx); ++i) {
        settings.setArrayIndex(i);

        if(i!=connectIdx){
            settings.setValue("per_table_name",settings.value("per_table_name"));
            settings.setValue("per_id_col",settings.value("per_id_col"));
            settings.setValue("role_per_table_name",settings.value("role_per_table_name"));
            settings.setValue("role_per_role_id_col",settings.value("role_per_role_id_col"));
            settings.setValue("role_per_per_id_col",settings.value("role_per_per_id_col"));
        }else{
            //set value
            settings.setValue("per_table_name",ui->per_table_name_edit->text());
            settings.setValue("per_id_col",ui->per_id_edit->text());
            settings.setValue("role_per_table_name",ui->role_per_table_name_edit->text());
            settings.setValue("role_per_role_id_col",ui->role_per_role_id_edit->text());
            settings.setValue("role_per_per_id_col",ui->role_per_per_id_edit->text());
        }

        settings.setValue("user_table_name", settings.value("user_table_name"));
        settings.setValue("user_id_col", settings.value("user_id_col"));
        settings.setValue("role_table_name",settings.value("role_table_name"));
        settings.setValue("role_id_col",settings.value("role_id_col"));
        settings.setValue("user_role_table_name",settings.value("user_role_table_name"));
        settings.setValue("user_role_role_id_col",settings.value("user_role_role_id_col"));
        settings.setValue("user_role_user_id_col",settings.value("user_role_user_id_col"));
        settings.setValue("default_role_id",settings.value("default_role_id"));
    }

    //save
    settings.endArray();
    settings.sync();
    // emit EditRoleSig();
    this->close();
}

void EditPerWindow::fillTable(int idx){
    //cur_connect_idx=idx;
    QSettings settings("./setting.ini", QSettings::IniFormat);
    settings.beginReadArray("tables");
    settings.setArrayIndex(idx);

    ui->per_table_name_edit->setText(settings.value("per_table_name").toString());
    ui->per_id_edit->setText(settings.value("per_id_col").toString());
    ui->role_per_table_name_edit->setText(settings.value("role_per_table_name").toString());
    ui->role_per_role_id_edit->setText(settings.value("role_per_role_id_col").toString());
    ui->role_per_per_id_edit->setText(settings.value("role_per_per_id_col").toString());

    settings.endArray();
}

