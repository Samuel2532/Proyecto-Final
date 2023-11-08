#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warnign","Cannot open file: "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,"Guardar archivo", currentFile, "Archivos de texto (*.txt);;Archivos HTML (*.html);;Todos los archivos (*)");
    QFile file(fileName);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
    }
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warnign","Cannot save file: "+file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning","Cannot Access Printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &font)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();
    charFormat.setFont(font);
    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (!cursor.isNull() && cursor.hasSelection()) {
        QTextCharFormat charFormat = cursor.charFormat();
        QFont font = charFormat.font();
        font.setPointSize(arg1);
        charFormat.setFont(font);
        cursor.mergeCharFormat(charFormat);
    }
}
void MainWindow::on_pushButton_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();
    charFormat.setFontItalic(!charFormat.fontItalic());
    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::on_pushButton_2_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();
    charFormat.setFontWeight(charFormat.fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::on_pushButton_3_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();

    // Toggle the background color for highlighting
    if (charFormat.background().style() == Qt::NoBrush) {
        charFormat.setBackground(QBrush(Qt::yellow));
    } else {
        charFormat.setBackground(Qt::NoBrush);
    }

    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}

void MainWindow::on_pushButton_4_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat charFormat = cursor.charFormat();

    // Toggle underline style
    charFormat.setFontUnderline(!charFormat.fontUnderline());

    cursor.mergeCharFormat(charFormat);
    ui->textEdit->mergeCurrentCharFormat(charFormat);
}


void MainWindow::on_pushButton_5_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    // Toggle text alignment between left-aligned and justified
    if (blockFormat.alignment() == Qt::AlignLeft) {
        blockFormat.setAlignment(Qt::AlignJustify);
    } else {
        blockFormat.setAlignment(Qt::AlignLeft);
    }

    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::on_pushButton_6_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    // Set text alignment to centered
    blockFormat.setAlignment(Qt::AlignCenter);

    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::on_pushButton_7_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    // Set text alignment to centered
    blockFormat.setAlignment(Qt::AlignRight);

    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}
