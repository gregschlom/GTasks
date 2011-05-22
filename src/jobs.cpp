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
  ListTasksJob
*/
ListTasksJob::ListTasksJob(Service* service, const QString& tasklistId)
	: Job(service,
          Job::Get, QString("/lists/" + tasklistId + "/tasks"),
          SIGNAL(result(GTasks::TaskCollection)))
{
}

void ListTasksJob::parseReply(const QVariantMap& response)
{
	emit result(TaskCollection(response));
}

// Optional parameters setters
ListTasksJob& ListTasksJob::maxResults(int max)                    { addRequestParam("maxResults",      max); return *this; }
ListTasksJob& ListTasksJob::pageToken(const QString& pageToken)    { addRequestParam("pageToken",       pageToken); return *this; }
ListTasksJob& ListTasksJob::completedBefore(const QDateTime& date) { addRequestParam("completedBefore", date); return *this; }
ListTasksJob& ListTasksJob::completedAfter(const QDateTime& date)  { addRequestParam("completedAfter",  date); return *this; }
ListTasksJob& ListTasksJob::dueBefore(const QDateTime& date)       { addRequestParam("dueBefore",       date); return *this; }
ListTasksJob& ListTasksJob::dueAfter(const QDateTime& date)        { addRequestParam("dueAfter",        date); return *this; }
ListTasksJob& ListTasksJob::updatedAfter(const QDateTime& date)    { addRequestParam("updatedAfter",    date); return *this; }
ListTasksJob& ListTasksJob::showCompleted(bool flag)               { addRequestParam("showCompleted",   flag); return *this; }
ListTasksJob& ListTasksJob::showDeleted(bool flag)                 { addRequestParam("showDeleted",     flag); return *this; }
ListTasksJob& ListTasksJob::showHidden(bool flag)                  { addRequestParam("showHidden",      flag); return *this; }


/*!
  ListTasklistsJob
*/
ListTasklistsJob::ListTasklistsJob(Service* service)
	: Job(service,
          Job::Get, "/users/@me/lists",
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
  InsertTasklistJob
*/
InsertTasklistJob::InsertTasklistJob(Service* service, const Tasklist& tasklist)
	: Job(service,
          Job::Post, "/users/@me/lists",
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
          Job::Delete, "/users/@me/lists/" + tasklistId,
          SIGNAL(result()))
{
}

void DeleteTasklistJob::parseReply(const QVariantMap& response)
{
	Q_UNUSED(response);
	emit result();
}


} // namespace GTasks

