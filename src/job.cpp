/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "job.h"
#include "service.h"

#include <QDebug>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include "qjson/parser.h"
#include "qjson/serializer.h"

namespace GTasks {

Job::Job(Service* service, HttpMethod method, QString path, const char* result)
	: QObject(service),
	  m_service(service),
      m_method(method),
      m_path(path),
      m_reply(0),
      m_resultSignal(result),
      m_data()
{
	addRequestParam("key", m_service->apiKey());
}

/*!
  Converts a parameter to the proper string format, and adds it to the request url.
  If the parameter already existed, it is overwritten.

  Bools are converted to "true" or "false"
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

void Job::startAndCallback(QObject* object, const char* callbackSlot)
{
	// Connect the subclass's result signal to the user-provided callback slot
	connect(this, m_resultSignal, object, callbackSlot);
	start();
}

void Job::start()
{
	// Assert that this job isn't already started
	Q_ASSERT(m_reply == 0);

	QUrl url = m_service->baseUrl();
	url.setPath(url.path() + m_path);

	// Add request parameters
	QMapIterator<QString, QString> i(m_parameters);
	while (i.hasNext()) {
		i.next();
		url.addQueryItem(i.key(), i.value());
	}

	OAuth::Token::HttpMethod method;
	switch(m_method) {
	case Get:    method = OAuth::Token::HttpGet;    break;
	case Post:   method = OAuth::Token::HttpPost;   break;
	case Put:    method = OAuth::Token::HttpPut;    break;
	case Delete: method = OAuth::Token::HttpDelete; break;
	}

	QByteArray authHeader = m_service->token().signRequest(url, OAuth::Token::HttpHeader, method);

	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Authorization", authHeader);

	QJson::Serializer json;
	QByteArray data = json.serialize(m_data);
	// Only for POST and PUT
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	// Execution
	switch(m_method) {
	case Get:    m_reply = m_service->networkManager()->get(request);            break;
	case Post:   m_reply = m_service->networkManager()->post(request, data);     break;
	case Put:    m_reply = m_service->networkManager()->put(request, data);      break;
	case Delete: m_reply = m_service->networkManager()->deleteResource(request); break;
	}

    connect(m_reply, SIGNAL(finished()), this, SLOT(parseReply()));
	m_reply->ignoreSslErrors();


	qDebug() << "Requesting... " << request.url() << "with data" << data << "auth:" << request.rawHeader("Authorization");
}

void Job::setRequestData(const QVariantMap &data)
{
	m_data = data;
}

void Job::parseReply()
{
	bool ok;
	QJson::Parser parser;
	QVariantMap response = parser.parse(m_reply->readAll(), &ok).toMap();

	if (m_reply->error() > 0) {
		qDebug() << "Error" << m_reply->error() << m_reply->errorString();
		qDebug() << m_reply->readAll();
	}

	parseReply(response);
	m_reply->deleteLater();
	this->deleteLater();
}

} // namespace GTasks