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
}

void Job::startAndCallback(QObject* object, const char* member)
{
	Q_ASSERT(m_reply == 0); // Assert that we are not trying to start the same job twice
	connect(this, m_result, object, member);
	doStart();
}

void Job::startRequest(const QNetworkRequest& request)
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
	: Job(service, "GET", "/lists/{tasklist}/tasks", SIGNAL(result(QList<GTasks::Task>))),
      m_tasklist(tasklistId)
{
}

void ListTasksJob::doStart()
{
	QNetworkRequest request;
	QString path = m_path.replace("{tasklist}", m_tasklist);
	request.setUrl(QUrl(m_service->baseUrl() + path + "?key=" + m_service->apiKey()));
	request.setRawHeader("Authorization", m_service->token().signRequest(request.url()));

	startRequest(request);
}

void ListTasksJob::parseReply(QNetworkReply* reply)
{
	bool ok;
	QJson::Parser parser;
	QVariantMap response = parser.parse(reply->readAll(), &ok).toMap();

	// Do error handling
	//qDebug() << "Error status:" << reply->error() << reply->errorString();
	//if (!response.contains("kind") || response["kind"] != "tasks#tasks") {

	TaskCollection tasks;
	tasks.deserialize(response);
	emit result(tasks);
}

} // namespace GTasks

