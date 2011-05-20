/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "jobs.h"
#include "service.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QDateTime>
#include <QStringList>

#include "qjson/parser.h"

namespace GTasks {

Job::Job(Service* service, QString method, QString path, const char* result)
	: QObject(service),
	  m_service(service),
      m_method(method),
      m_path(path),
      m_reply(0),
      m_result(result)
{
	addRequestParam("key", m_service->apiKey());
}

/*!
  Adds a parameter to the request url.
  If the parameter already existed, it is overwritten.

  Dates are converted to the RFC 3339 timestamp format.

  @note By default, Qt's datetimes are expressed in local time. Don't forget to call
  QDateTime::setUtcOffset to set the correct timezone, otherwise, it will likely have the incorrect
  timezone.
*/
void Job::addRequestParam(const QString& name, const QVariant& value)
{
	switch (value.type()) {

	case QVariant::Date:
	case QVariant::DateTime:
		m_parameters.insert(name, value.toDateTime().toString("yyyy-MM-ddThh:mm:ss.zzzZ"));
		break;

	default:
	case QVariant::Int:
	case QVariant::Bool:
	case QVariant::String:
		m_parameters.insert(name, value.toString());
		break;
	}
}

void Job::startAndCallback(QObject* object, const char* member)
{
	Q_ASSERT(m_reply == 0); // Assert that we are not trying to start the same job twice
	connect(this, m_result, object, member);
	//doStart();

	QUrl url(m_service->baseUrl() + m_path);

	QMapIterator<QString, QString> i(m_parameters);
	while (i.hasNext()) {
		i.next();
		url.addQueryItem(i.key(), i.value());
	}

	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Authorization", m_service->token().signRequest(request.url()));

	execute(request);

}

void Job::execute(const QNetworkRequest& request)
{
	m_reply = m_service->networkManager()->get(request);
    connect(m_reply, SIGNAL(finished()), this, SLOT(parseReply()));
	m_reply->ignoreSslErrors();
	qDebug() << "Requesting... " << request.url();
}

void Job::parseReply()
{
	parseReply(m_reply);
	m_reply->deleteLater();
	this->deleteLater();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////

ListTasksJob::ListTasksJob(Service* service, const QString& tasklistId)
	: Job(service,
          "GET", QString("/lists/" + tasklistId + "/tasks"),
          SIGNAL(result(GTasks::TaskCollection)))
{
}

void ListTasksJob::parseReply(QNetworkReply* reply)
{
	bool ok;
	QJson::Parser parser;
	QVariantMap response = parser.parse(reply->readAll(), &ok).toMap();

	// Do error handling
	if (!response.contains("kind") || response["kind"] != "tasks#tasks") {
		qDebug() << "Error" << reply->error() << reply->errorString();
		qDebug() << reply->readAll();
		return;
	}

	TaskCollection tasks;
	tasks.deserialize(response);
	emit result(tasks);
}

// Optional parameters setters
ListTasksJob& ListTasksJob::maxResults(int max)                    { addRequestParam("maxResults",      max); return *this; }
ListTasksJob& ListTasksJob::completedBefore(const QDateTime& date) { addRequestParam("completedBefore", date); return *this; }
ListTasksJob& ListTasksJob::completedAfter(const QDateTime& date)  { addRequestParam("completedAfter",  date); return *this; }
ListTasksJob& ListTasksJob::dueBefore(const QDateTime& date)       { addRequestParam("dueBefore",       date); return *this; }
ListTasksJob& ListTasksJob::dueAfter(const QDateTime& date)        { addRequestParam("dueAfter",        date); return *this; }
ListTasksJob& ListTasksJob::updatedAfter(const QDateTime& date)    { addRequestParam("updatedAfter",    date); return *this; }
ListTasksJob& ListTasksJob::showCompleted(bool flag)               { addRequestParam("showCompleted",   flag); return *this; }
ListTasksJob& ListTasksJob::showDeleted(bool flag)                 { addRequestParam("showDeleted",     flag); return *this; }
ListTasksJob& ListTasksJob::showHidden(bool flag)                  { addRequestParam("showHidden",      flag); return *this; }
ListTasksJob& ListTasksJob::pageToken(const QString& pageToken)    { addRequestParam("pageToken",       pageToken); return *this; }

} // namespace GTasks

