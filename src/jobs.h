/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_JOBS_H
#define GTASKS_JOBS_H

#include <QObject>

#include "task.h"
#include "taskcollection.h"

class QNetworkReply;
class QNetworkRequest;

namespace GTasks {

class Service;

class Job : public QObject {
	Q_OBJECT

public:
	explicit Job(Service* service, QString method, QString path, const char* result);

	void startAndCallback(QObject* object, const char* member);

protected:
	void execute(const QNetworkRequest& request);
	//virtual void doStart() = 0;

	void addRequestParam(const QString& param, const QVariant& value);

protected slots:
	virtual void parseReply(QNetworkReply*) = 0;

protected:
	Service* m_service;
	QString m_method;
	QString m_path;

private slots:
	void parseReply();

private:
	QNetworkReply* m_reply;
	const char* m_result;
	QMap<QString, QString> m_parameters;
};

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
	void parseReply(QNetworkReply* reply);
};

}
#endif // GTASKS_JOBS_H
