/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_SERVICE_H
#define GTASKS_SERVICE_H

#include <QObject>
#include <QUrl>

#include "simpleoauth/oauth_token.h"

class QNetworkAccessManager;

namespace GTasks {

class Tasklist;
class Task;

class ListTasklistsJob;
class GetTasklistJob;
class InsertTasklistJob;
class UpdateTasklistJob;
class DeleteTasklistJob;
class ListTasksJob;
class GetTaskJob;
class InsertTaskJob;
class UpdateTaskJob;
class DeleteTaskJob;
class MoveTaskJob;
class ClearTasksJob;

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QNetworkAccessManager* networkManager, QObject* parent = 0);

	void setApiKey(const QString& key);
	void setToken(const OAuth::Token& token);

	QNetworkAccessManager* networkManager() const;
	const QString apiKey() const;
	const OAuth::Token token() const;

	ListTasklistsJob& listTasklists();
	GetTasklistJob& getTasklist(const QUrl& selfLink);
	GetTasklistJob& getTasklist(const QString& tasklistId);
	InsertTasklistJob& insertTasklist(const Tasklist& tasklist);
	UpdateTasklistJob& updateTasklist(const Tasklist& tasklist);
	DeleteTasklistJob& deleteTasklist(const Tasklist& tasklist);
	DeleteTasklistJob& deleteTasklist(const QString& tasklistId);
	DeleteTasklistJob& deleteTasklist(const QUrl& selfLink);
	ListTasksJob& listTasks(const Tasklist& tasklist);
	ListTasksJob& listTasks(const QString& tasklistId);
	GetTaskJob& getTask(const QUrl& selfLink);
	GetTaskJob& getTask(const QString& tasklistId, const QString& taskId);
	InsertTaskJob& insertTask(const QString& tasklistId, const Task& task);
	UpdateTaskJob& updateTask(const Task& task);
	DeleteTaskJob& deleteTask(const Task& task);
	DeleteTaskJob& deleteTask(const QUrl& selfLink);
	DeleteTaskJob& deleteTask(const QString& tasklistId, const QString& taskId);
	MoveTaskJob& moveTask(const Task& task);
	MoveTaskJob& moveTask(const QUrl& selfLink);
	MoveTaskJob& moveTask(const QString& tasklistId, const QString& taskId);
	ClearTasksJob& clearTasks(const Tasklist& tasklist);
	ClearTasksJob& clearTasks(const QString& tasklistId);

private:
	QNetworkAccessManager* m_networkManager;
	QString m_apiKey;
	OAuth::Token m_token;
};

}

#endif // GTASKS_SERVICE_H
