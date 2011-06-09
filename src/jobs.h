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

#ifndef GTASKS_JOBS_H
#define GTASKS_JOBS_H

#include "job.h"
#include "task.h"
#include "tasklist.h"
#include "tasklistcollection.h"
#include "taskcollection.h"
#include "error.h"

namespace GTasks {

class ListTasklistsJob : public Job
{
    Q_OBJECT
public:
    explicit ListTasklistsJob(Service* service);
	ListTasklistsJob& maxResults(int max);
	ListTasklistsJob& pageToken(const QString& pageToken);

signals:
	void result(GTasks::TasklistCollection, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);

};

class GetTasklistJob : public Job
{
    Q_OBJECT
public:
	explicit GetTasklistJob(Service* service, const QUrl& selfLink);

signals:
	void result(GTasks::Tasklist, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class UpdateTasklistJob : public Job
{
    Q_OBJECT
public:
    explicit UpdateTasklistJob(Service* service, const Tasklist& tasklist);

signals:
	void result(GTasks::Tasklist, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class InsertTasklistJob : public Job
{
    Q_OBJECT
public:
    explicit InsertTasklistJob(Service* service, const Tasklist& tasklist);

signals:
	void result(GTasks::Tasklist, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class DeleteTasklistJob : public Job
{
    Q_OBJECT
public:
	explicit DeleteTasklistJob(Service* service, const QUrl& selfLink);

signals:
	void result(GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class ListTasksJob : public Job
{
    Q_OBJECT
public:
    explicit ListTasksJob(Service* service, const QString& tasklistId);

	// Optional parameters
	ListTasksJob& maxResults(int max);                     // default 20, max 100
	ListTasksJob& pageToken(const QString& pageToken);
	ListTasksJob& completedBefore(const QDateTime& date);
	ListTasksJob& completedAfter(const QDateTime& date);
	ListTasksJob& dueBefore(const QDateTime& date);
	ListTasksJob& dueAfter(const QDateTime& date);
	ListTasksJob& updatedAfter(const QDateTime& date);
	ListTasksJob& showCompleted(bool flag);                // default true
	ListTasksJob& showDeleted(bool flag);                  // default false
	ListTasksJob& showHidden(bool flag);                   // default true

signals:
	void result(GTasks::TaskCollection, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class GetTaskJob : public Job
{
    Q_OBJECT
public:
	explicit GetTaskJob(Service* service, const QUrl& selfLink);

signals:
	void result(GTasks::Task, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class InsertTaskJob : public Job
{
    Q_OBJECT
public:
    explicit InsertTaskJob(Service* service, const QString& tasklistId, const Task& task);

	InsertTaskJob& asChildOf(const QString& taskId);
	InsertTaskJob& after(const QString& taskId);

signals:
	void result(GTasks::Task, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class UpdateTaskJob : public Job
{
    Q_OBJECT
public:
    explicit UpdateTaskJob(Service* service, const Task& task);

signals:
	void result(GTasks::Task, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class DeleteTaskJob : public Job
{
    Q_OBJECT
public:
	explicit DeleteTaskJob(Service* service, const QUrl& selfLink);

signals:
	void result(GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class MoveTaskJob : public Job
{
    Q_OBJECT
public:
	explicit MoveTaskJob(Service* service, const QUrl& selfLink);

	MoveTaskJob& asChildOf(const QString& taskId);
	MoveTaskJob& after(const QString& taskId);
signals:
	void result(GTasks::Task, GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

class ClearTasksJob : public Job
{
    Q_OBJECT
public:
	explicit ClearTasksJob(Service* service, const QString& tasklistId);

signals:
	void result(GTasks::Error);

protected:
	void parseReply(const QVariantMap& response, const GTasks::Error& error);
};

}
#endif // GTASKS_JOBS_H
