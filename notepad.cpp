#include "notepad.h"
#include "ui_notepad.h"

#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionNew_triggered()
{

    file_path_ = "";
    ui->textEdit->setText("");
}

void Notepad::on_actionOpen_triggered()
{
   QString file_name = QFileDialog::getOpenFileName(this,"Open The File");
   QFile file(file_name);
   file_path_ = file_name;
   if(!file.open(QFile::ReadOnly | QFile::Text)){

       QMessageBox::warning(this,"..","File is not open");
       return;
   }
   QTextStream in(&file);
   QString text = in.readAll();
   ui->textEdit->setText(text);
   file.close();
}

void Notepad::on_actionSave_triggered()
{

    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)){

        QMessageBox::warning(this,"..","File is not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<< text;
     file.flush();
    file.close();
}

void Notepad::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save The File");

    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){

        QMessageBox::warning(this,"..","File is not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();



}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();

}

void Notepad::on_actionRedo_triggered()
{

     ui->textEdit->redo();
}

void Notepad::on_actionUndo_triggered()
{

    ui->textEdit->undo();
}

void Notepad::on_actionAbout_Notepad_triggered()
{
  QString about_text;
about_text = "Creator : Ansah Kelvin" ;
about_text += " Date  : 19/01/2019 ";
about_text += "(c)  Personal NotePad (R)" ;


    QMessageBox::about(this,"About NotePad",about_text);
}
