/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "jobs.h"

//#include <QDebug>

namespace GTasks {

/*!
  ListTasklistsJob
*/
ListTasklistsJob::ListTasklistsJob(Service* service)
	: Job(service,
          Job::Get, Tasklist::generateSelfLink(""),
          SIGNAL(result(GTasks::TasklistCollection)))
{
}

void ListTasklistsJob::parseReply(const QVariantMap& response)
{
	emit result(TasklistCollection(response));
}

ListTasklistsJob& ListTasklistsJob::maxResults(int max)                    { addRequestParam("maxResults", max); return *this; }
ListTasklistsJob& ListTasklistsJob::pageToken(const QString& pageToken)    { addRequestParam("pageToken",  pageToken); return *this; }

/*!
  GetTasklistJob
*/
GetTasklistJob::GetTasklistJob(Service* service, const QString& tasklistId)
	: Job(service,
          Job::Get, Tasklist::generateSelfLink(tasklistId),
          SIGNAL(result(GTasks::Tasklist)))
{
}

void GetTasklistJob::parseReply(const QVariantMap& response)
{
	emit result(Tasklist(response));
}

/*!
  UpdateTasklistJob
*/
UpdateTasklistJob::UpdateTasklistJob(Service* service, const Tasklist& tasklist)
	: Job(service,
          Job::Put, tasklist.selfLink(),
          SIGNAL(result(GTasks::Tasklist)))
{
	setRequestData(tasklist.serialize());
}

void UpdateTasklistJob::parseReply(const QVariantMap& response)
{
	emit result(Tasklist(response));
}

/*!
  InsertTasklistJob
*/
InsertTasklistJob::InsertTasklistJob(Service* service, const Tasklist& tasklist)
	: Job(service,
          Job::Post, Tasklist::generateSelfLink(""),
          SIGNAL(result(GTasks::Tasklist)))
{
	QVariantMap data;
	data.insert("title", tasklist.title());
	setRequestData(data);
}

void InsertTasklistJob::parseReply(const QVariantMap& response)
{
	emit result(Tasklist(response));
}

/*!
  DeleteTasklistJob
*/
DeleteTasklistJob::DeleteTasklistJob(Service* service, const QString& tasklistId)
	: Job(service,
          Job::Delete, Tasklist::generateSelfLink(tasklistId),
          SIGNAL(result()))
{
}

void DeleteTasklistJob::parseReply(const QVariantMap& response)
{
	Q_UNUSED(response);
	emit result();
}

/*!
  ListTasksJob
*/
ListTasksJob::ListTasksJob(Service* service, const QString& tasklistId)
	: Job(service,
          Job::Get, Task::generateSelfLink(tasklistId, ""),
          SIGNAL(result(GTasks::TaskCollection)))
{
}

void ListTasksJob::parseReply(const QVariantMap& response)
{
	emit result(TaskCollection(response));
}

// Optional parameters setters
ListTasksJob& ListTasksJob::maxResults(int max)                    { addRequestParam("maxResults",   max); return *this; }
ListTasksJob& ListTasksJob::pageToken(const QString& pageToken)    { addRequestParam("pageToken",    pageToken); return *this; }
ListTasksJob& ListTasksJob::completedBefore(const QDateTime& date) { addRequestParam("completedMax", date); return *this; }
ListTasksJob& ListTasksJob::completedAfter(const QDateTime& date)  { addRequestParam("completedMin", date); return *this; }
ListTasksJob& ListTasksJob::dueBefore(const QDateTime& date)       { addRequestParam("dueMax",       date); return *this; }
ListTasksJob& ListTasksJob::dueAfter(const QDateTime& date)        { addRequestParam("dueMin",       date); return *this; }
ListTasksJob& ListTasksJob::updatedAfter(const QDateTime& date)    { addRequestParam("updatedMin",   date); return *this; }
ListTasksJob& ListTasksJob::showCompleted(bool flag)               { addRequestParam("showCompleted",flag); return *this; }
ListTasksJob& ListTasksJob::showDeleted(bool flag)                 { addRequestParam("showDeleted",  flag); return *this; }
ListTasksJob& ListTasksJob::showHidden(bool flag)                  { addRequestParam("showHidden",   flag); return *this; }

/*!
  GetTaskJob
*/
GetTaskJob::GetTaskJob(Service* service, const QUrl& selfLink)
	: Job(service,
          Job::Get, selfLink,
          SIGNAL(result(GTasks::Task)))
{
}

void GetTaskJob::parseReply(const QVariantMap& response)
{
	emit result(Task(response));
}

/*!
  InsertTaskJob
*/
InsertTaskJob::InsertTaskJob(Service* service, const QString& tasklistId, const Task& task)
	: Job(service,
          Job::Post, Task::generateSelfLink(tasklistId, ""),
          SIGNAL(result(GTasks::Task)))
{
	setRequestData(task.serialize());
}

void InsertTaskJob::parseReply(const QVariantMap& response)
{
	emit result(Task(response));
}

InsertTaskJob& InsertTaskJob::asChildOf(const QString& taskId) { addRequestParam("parent",   taskId); return *this; }
InsertTaskJob& InsertTaskJob::after(const QString& taskId)     { addRequestParam("previous", taskId); return *this; }

/*!
  UpdateTaskJob
*/
UpdateTaskJob::UpdateTaskJob(Service* service, const Task& task)
	: Job(service,
          Job::Put, task.selfLink(),
          SIGNAL(result(GTasks::Task)))
{
	setRequestData(task.serialize());
}

void UpdateTaskJob::parseReply(const QVariantMap& response)
{
	emit result(Task(response));
}

/*!
  DeleteTaskJob
*/
DeleteTaskJob::DeleteTaskJob(Service* service, const QUrl& selfLink)
	: Job(service,
          Job::Delete, selfLink,
          SIGNAL(result()))
{
}

void DeleteTaskJob::parseReply(const QVariantMap& response)
{
	Q_UNUSED(response);
	emit result();
}

/*!
  MoveTaskJob
*/
MoveTaskJob::MoveTaskJob(Service* service, const QUrl& selfLink)
	: Job(service,
          Job::Post, QUrl(selfLink.toString() + "/move"),
          SIGNAL(result(GTasks::Task)))
{
}

void MoveTaskJob::parseReply(const QVariantMap& response)
{
	emit result(Task(response));
}

MoveTaskJob& MoveTaskJob::asChildOf(const QString& taskId) { addRequestParam("parent",   taskId); return *this; }
MoveTaskJob& MoveTaskJob::after(const QString& taskId)     { addRequestParam("previous", taskId); return *this; }

/*!
  ClearTasksJob
*/
ClearTasksJob::ClearTasksJob(Service* service, const QString& tasklistId)
	: Job(service,
          Job::Post, QUrl("https://www.googleapis.com/tasks/v1/lists/" + tasklistId + "/clear"),
          SIGNAL(result()))
{
}

void ClearTasksJob::parseReply(const QVariantMap& response)
{
	Q_UNUSED(response);
	emit result();
}

} // namespace GTasks

