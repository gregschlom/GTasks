/*
 *  GTasks - A C++/Qt API client for Google Tasks
 *
 *  Copyright (C) 2011 Gregory Schlomoff <gregory.schlomoff@gmail.com>
 *                     http://gregschlom.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
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
