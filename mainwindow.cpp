#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(300, 100, 1000, 800);
    setMinimumSize(1000, 800);

    layout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    menu = new QMenu("&File");
    about = new QMenu("&About");
    open = new QAction("Open");
    open->setShortcut(tr("Ctrl+O"));
    exit = new QAction("Exit");
    exit->setShortcut(tr("Ctrl+E"));
    info = new QAction("Information");
    info->setShortcut(tr("Ctrl+I"));
    menuBar()->addMenu(menu);
    menuBar()->addMenu(about);
    menu->addAction(open);
    menu->addAction(exit);
    about->addAction(info);

    table = new QTableWidget();
    QStringList name_table;
    name_table << "file name" << "file type" << "image size" << "resolution" << "color depth" << "compression";
    table->setColumnCount(6);
    table->setRowCount(100000);
    table->setHorizontalHeaderLabels(name_table);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView *headerGoods = table->horizontalHeader();

    headerGoods->setSortIndicator(0, Qt::AscendingOrder);

    headerGoods->setSortIndicatorShown(true);

    table->setFocusPolicy(Qt::NoFocus);
    table->verticalHeader()->setVisible(false);

    layout->addWidget(table);

    mainLayout->addLayout(layout);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    setCentralWidget(window);

    connect(headerGoods, SIGNAL(sectionClicked(int)), table, SLOT (sortByColumn(int)));
    connect(info, SIGNAL(triggered()), this, SLOT(about_clicked()));
    connect(open, SIGNAL(triggered()), this, SLOT(file_open()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::about_clicked()
{
    QMessageBox::about(this, tr("About me"),
            tr("<p>Mironovski Ivan, 14 group</p>"));
}

void MainWindow::file_open()
{
    QFileDialog w;
    w.setFileMode(QFileDialog::Directory);
    w.setOption(QFileDialog::DontUseNativeDialog, true);
    QListView *lView = w.findChild<QListView*>("listView");
    if(lView) {
        lView->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    QTreeView *tView = w.findChild<QTreeView*>();
    if(tView) {
        tView->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    w.exec();
    dirs.clear();
    dirs = w.selectedFiles();
    update();
}

void MainWindow::update()
{
    int index = 0;
    table->clear();
    QStringList name_table;
    name_table << "file name" << "file type" << "image size" << "resolution" << "color depth" << "compression";
    table->setHorizontalHeaderLabels(name_table);
    for(int i = 0; i < dirs.size(); i++) {
        QString path = dirs[i];
        QDir dir(path);
        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.png" << "*.gif" << "*.tif" << "*.bmp" << "*.pcx";
        dir.setNameFilters(nameFilters);
        QFileInfoList files = dir.entryInfoList();
        for(int j = index; j < index + files.size(); j++) {
            QFileInfo fileInfo = files[j];
            QImageWriter comp;
            comp.setFileName(fileInfo.fileName());
            QImage img;
            QString path = fileInfo.path();
            QString name = fileInfo.fileName();
            path = path + "/" + name;
            img.load(path);
            int size = fileInfo.size();
            QTableWidgetItem *itm_0 = new QTableWidgetItem(name);
            QTableWidgetItem *itm_1 = new QTableWidgetItem(fileInfo.suffix());
            QTableWidgetItem *itm_2 = new QTableWidgetItem(QVariant(size).toString() + " bits");
            QTableWidgetItem *itm_3 = new QTableWidgetItem(QVariant(img.width()).toString()+ "x" + QVariant(img.height()).toString());
            QTableWidgetItem *itm_4 = new QTableWidgetItem(QVariant(img.depth()).toString());
            QTableWidgetItem *itm_5 = new QTableWidgetItem(QVariant(comp.compression()).toString());
            table->setItem(j, 0, itm_0);
            table->setItem(j, 1, itm_1);
            table->setItem(j, 2, itm_2);
            table->setItem(j, 3, itm_3);
            table->setItem(j, 4, itm_4);
            table->setItem(j, 5, itm_5);
        }
        index += files.size();
    }
}

MainWindow::~MainWindow()
{
}
