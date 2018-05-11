#include <QStringList>
#include <QStringListModel>

#include "userprofilewindow.h"
#include "ui_userprofilewindow.h"

#include "postwindow.h"

UserProfileWindow::UserProfileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserProfileWindow)
{
    ui->setupUi(this);

    postsModel = new QStringListModel(this);
    historyModel = new QStringListModel(this);
}

UserProfileWindow::~UserProfileWindow()
{
    delete ui;
}

void UserProfileWindow::setApi(CourseAPI *api) {
    this->api = api;
    ui->usernameLabel->setText(api->username);
}

void UserProfileWindow::setUserInfo() {
    QStringList userPosts;
    QList<Regex> apiUserPosts = api->authorPosts();

    ui->postsCountLabel->setText(QString::number(apiUserPosts.count()));

    foreach (Regex r, apiUserPosts) {
        userPosts.append(QString("%1 | %2 | Views: %3 Mark: %4 | Created: %5").arg(QString::number(r.id), r.expression, QString::number(r.views), QString::number(r.avgMark), r.date));
    }

    QStringList userHistory;
    QList<Regex> apiHistory = api->userViewsHistory();

    ui->historyCountLabel->setText(QString::number(apiHistory.count()));

    foreach (Regex r, apiHistory) {
        userHistory.append(QString("%1 | %2 | Views: %3 Mark: %4 | Created: %5").arg(QString::number(r.id), r.expression, QString::number(r.views), QString::number(r.avgMark), r.date));
    }

    postsModel->setStringList(userPosts);
    historyModel->setStringList(userHistory);

    ui->postsView->setModel(postsModel);
    ui->historyView->setModel(historyModel);
}

void UserProfileWindow::on_postsView_clicked(const QModelIndex &index)
{
    QString text = postsModel->itemData(index).first().toString();
    ui->postsView->clearSelection();
    qDebug() << text;
    postWindow = new PostWindow(this);
    postWindow->setWindowTitle(text);
    postWindow->setPostInfo(text);
    postWindow->show();
}

void UserProfileWindow::on_historyView_clicked(const QModelIndex &index)
{
    QString text = historyModel->itemData(index).first().toString();
    ui->historyView->clearSelection();
    qDebug() << text;
    postWindow = new PostWindow(this);
    postWindow->setWindowTitle(text);
    postWindow->setPostInfo(text);
    postWindow->show();
}
