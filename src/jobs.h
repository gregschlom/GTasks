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
#include "taskcollection.h"

namespace GTasks {

class ListTasksJob : public Job
{
    Q_OBJECT
public:
    explicit ListTasksJob(Service* service, const QString& tasklistId);

	// Optional parameters
	ListTasksJob& maxResults(int max);                     // default 20, max 100
	ListTasksJob& completedBefore(const QDateTime& date);
	ListTasksJob& completedAfter(const QDateTime& date);
	ListTasksJob& dueBefore(const QDateTime& date);
	ListTasksJob& dueAfter(const QDateTime& date);
	ListTasksJob& updatedAfter(const QDateTime& date);
	ListTasksJob& showCompleted(bool flag);                // default true
	ListTasksJob& showDeleted(bool flag);                  // default false
	ListTasksJob& showHidden(bool flag);                   // default true
	ListTasksJob& pageToken(const QString& pageToken);

signals:
	void result(GTasks::TaskCollection);

protected slots:
	void parseReply(const QVariantMap& response);
};


class InsertTasklistJob : public Job
{
    Q_OBJECT
public:
    explicit InsertTasklistJob(Service* service, const Tasklist& tasklist);

signals:
	void result(GTasks::Tasklist);

protected slots:
	void parseReply(const QVariantMap& response);
};

}
#endif // GTASKS_JOBS_H
