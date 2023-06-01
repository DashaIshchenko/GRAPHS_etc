/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include "renderarea.h"
/*
 * bst_properties_window.h includes:
 * QMainWindow, QVBoxLayout, QHBoxLayout, QScrollArea, QWidget, QLabel, QLineEdit
 */
#include "bst_properties_window.h"
//#include "bst_about_window.h"
#include "BinarySearchTree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea *renderArea;
    QPushButton *propertyButton;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QPushButton *Balancing;
    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;
    QScrollArea *treeScrollArea;
    QVBoxLayout *mainLayout;
    QLabel *statusLabel;
    QAction *loadAction;
    QAction *saveAction;
    BST_Properties_Window *prop;
    BinarySearchTree<int> *bst;

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void resizeEvent(QResizeEvent* event);

private slots:
    void propertyClicked() const;
    void insertClicked() const;
    void deleteClicked() const;
    void BalancingClicked() const;
};

#endif // MAINWINDOW_H
