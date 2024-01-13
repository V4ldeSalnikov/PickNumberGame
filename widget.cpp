#include "widget.h"
#include "./ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->firstPlayerScoreLabel->setText("");
    ui->firstPlayerScoreLabel->setText("");
    ui->restartGame->hide();
    ui->closeGame->hide();

    // Connect signals to slots
    connect(ui->restartGame, &QPushButton::clicked, this, &Widget::restart_game);
    connect(ui->closeGame, &QPushButton::clicked, this, &Widget::close_game);
    connect(ui->deleteFirst, &QPushButton::clicked, this, &Widget::delete_first);
    connect(ui->deleteLast, &QPushButton::clicked, this, &Widget::delete_last);
    connect(ui->generateButton, &QPushButton::clicked, this, &Widget::on_generate);
    first_player_score = 0;
    second_player_score = 0;
    isFirstPlayerTurn = true;
    update_score_display();


}

Widget::~Widget()
{
    delete ui;
}
void Widget::update_display() {

    ui->listWidget->clear();
    for (int num : myDeque) {
        ui->listWidget->addItem(QString::number(num));
    }



}

void Widget::delete_last(){

    if (!myDeque.empty()) {
        int deletedValue = myDeque.back();
        myDeque.pop_back();
        update_display();
        if (isFirstPlayerTurn) {
            first_player_score += deletedValue;
        } else {
            second_player_score += deletedValue;
        }
        update_score_display();
        isFirstPlayerTurn = !isFirstPlayerTurn;
    }

    if (myDeque.empty()) {
        display_winner();
    }
}
void Widget::delete_first(){
    if (!myDeque.empty()) {
        int deletedValue = myDeque.front();
        myDeque.pop_front();
        update_display();

        if (isFirstPlayerTurn) {
            first_player_score += deletedValue;
        } else {
            second_player_score += deletedValue;
        }
        update_score_display();
        isFirstPlayerTurn = !isFirstPlayerTurn;
    }

    if (myDeque.empty()) {
        display_winner();
    }
}
void Widget::on_generate(){

    first_player_score = 0;
    second_player_score = 0;
    update_score_display();

    if (myDeque.size()!= 0){
        ui->listWidget->clear();
        myDeque.clear();
    }

    std::srand(std::time(0));
    for (int i = 0; i < 10; ++i) {
        myDeque.push_back(std::rand() % 100);
    }
    update_display();


}

void Widget::update_score_display(){
    ui->firstPlayerScoreLabel->setText("First Player Score: " + QString::number(first_player_score));
    ui->secondPlayerScoreLabel->setText("Second Player Score: " +  QString::number(second_player_score));
}

void Widget::display_winner(){
    ui->listWidget->hide();
    ui->deleteFirst->hide();
    ui->deleteLast->hide();
    ui->firstPlayerScoreLabel->hide();
    ui->secondPlayerScoreLabel->hide();
    ui->generateButton->hide();


    // Determine the winner
    QString winnerText;
    if (first_player_score > second_player_score) {
        winnerText = "First Player Wins!\n     " + QString::number(first_player_score) + " vs "+ QString::number(second_player_score);
    } else if (second_player_score > first_player_score) {
        winnerText = "Second Player Wins!\n     " + QString::number(second_player_score) + " vs " + QString::number(first_player_score);
    } else {
        winnerText = "It's a tie!";
    }

    // Display winner
    ui->displayWinner->setText(winnerText);
    ui->closeGame->show();
    ui->restartGame->show();
    ui->displayWinner->show();
}

void Widget::restart_game(){
    myDeque.clear();
    first_player_score = 0;
    second_player_score = 0;
    update_score_display();
    isFirstPlayerTurn = true;

    ui->restartGame->hide();
    ui->closeGame->hide();
    ui->displayWinner->hide();

    // Show the other UI elements again
    ui->listWidget->show();
    ui->deleteFirst->show();
    ui->deleteLast->show();
    ui->firstPlayerScoreLabel->show();

    ui->secondPlayerScoreLabel->show();
    ui->generateButton->show();
}

void Widget::close_game(){
    this->close();
}

