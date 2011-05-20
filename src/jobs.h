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
	virtual void requestFinished(QNetworkReply*) = 0;

protected:
	Service* m_service;
	QString m_method;
	QString m_path;

private slots:
	void requestFinished();

private:
	QNetworkReply* m_reply;
	const char* m_result;
};

class ListTasks : public Job
{
    Q_OBJECT
public:
    explicit ListTasks(Service* service);
	ListTasks* tasklist(QString tasklist);

signals:
	void result(QList<GTasks::Task>);

protected slots:
	void requestFinished(QNetworkReply* reply);

private:
	void doStart();

private:
	QString m_tasklist;
};

}
#endif // GTASKS_JOBS_H
