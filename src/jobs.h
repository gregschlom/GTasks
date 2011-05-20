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
	void startRequest(const QNetworkRequest& request);
	virtual void doStart() = 0;

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
};

class ListTasksJob : public Job
{
    Q_OBJECT
public:
    explicit ListTasksJob(Service* service, const QString& tasklistId);

signals:
	void result(GTasks::TaskCollection);

protected slots:
	void parseReply(QNetworkReply* reply);

private:
	void doStart();

private:
	QString m_tasklist;
};

}
#endif // GTASKS_JOBS_H
