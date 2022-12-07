#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QListView>
#include <QTreeView>
#include <QDir>
#include <QPixmap>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *menu;
    QMenu *about;
    QAction *open;
    QAction *exit;
    QAction *info;
    QTableWidget *table;
    QHBoxLayout *layout;
    QVBoxLayout *mainLayout;
    QStringList dirs;
private slots:
    void about_clicked();
    void file_open();
    void update();
};
#endif // MAINWINDOW_H
