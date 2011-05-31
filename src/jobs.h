/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
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
