#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"
#include <QWidget>
#include <deque>
#include <QHBoxLayout>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void on_generate();
    std::deque<int> myDeque;
    int first_player_score{0};
    int second_player_score{0};
    bool isFirstPlayerTurn;
    void update_display();
    void delete_first();
    void delete_last();
    void update_score_display();
    void display_winner();
    void restart_game();
    void close_game();
    QWidget *container;
    QHBoxLayout *layout;


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
