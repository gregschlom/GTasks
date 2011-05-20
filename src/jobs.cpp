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

ListTasks::ListTasks(Service* service)
	: Job(service, "GET", "/lists/{tasklist}/tasks", SIGNAL(result(QList<GTasks::Task>))),
      m_tasklist("@default")
{
}

ListTasks* ListTasks::tasklist(QString tasklist)
{
	m_tasklist = tasklist;
	return this;
}

void ListTasks::doStart()
{
	QNetworkRequest request;
	QString path = m_path.replace("{tasklist}", m_tasklist);
	request.setUrl(QUrl(m_service->baseUrl() + path + "?key=" + m_service->apiKey()));
	request.setRawHeader("Authorization", m_service->token().signRequest(request.url()));

	startRequest(request);
}

void ListTasks::parseReply(QNetworkReply* reply)
{
	qDebug() << "Error status:" << reply->error() << reply->errorString();

	//return;

	QJson::Parser parser;
	bool ok;
	QVariantMap response = parser.parse(reply->readAll(), &ok).toMap();

	TaskCollection tasks;
	if (!response.contains("kind") || response["kind"] != "tasks#tasks") {
		qDebug() << "Error, unexpected format " << response["kind"] << ". Was expecting tasks#tasks";
	} else {
		tasks.deserialize(response);
	}

	emit result(tasks.items());
}

} // namespace GTasks

