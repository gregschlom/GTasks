/*
 *  GTasks - A C++/Qt API client for Google Tasks
 *
 *  Copyright (C) 2011 Gregory Schlomoff <gregory.schlomoff@gmail.com>
 *                     http://gregschlom.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include "job.h"
#include "service.h"
#include "error.h"

#include <QDebug>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include "qjson/parser.h"
#include "qjson/serializer.h"

namespace GTasks {

Job::Job(Service* service, HttpMethod method, const QUrl& url, const char* result)
	: QObject(service),
	  m_service(service),
      m_method(method),
      m_url(url),
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

	// Add request parameters
	QMapIterator<QString, QString> i(m_parameters);
	while (i.hasNext()) {
		i.next();
		m_url.addQueryItem(i.key(), i.value());
	}

	OAuth::Token::HttpMethod method;
	switch(m_method) {
	case Get:    method = OAuth::Token::HttpGet;    break;
	case Post:   method = OAuth::Token::HttpPost;   break;
	case Put:    method = OAuth::Token::HttpPut;    break;
	case Delete: method = OAuth::Token::HttpDelete; break;
	}

	QByteArray authHeader = m_service->token().signRequest(m_url, OAuth::Token::HttpHeader, method);

	QNetworkRequest request;
	request.setUrl(m_url);
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
	Error error;
	QByteArray responseString = m_reply->readAll();

	bool ok;
	QJson::Parser parser;
	QVariantMap response = parser.parse(responseString, &ok).toMap();

	// Set error codes and messages if any
	error.setCode(m_reply->error());
	error.setMessage(m_reply->errorString());
	error.setHttpCode(m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
	if (response.contains("error")) {
		error.setGtasksMessage(response.value("error").toMap().value("message").toString());
	}

	// Deal with parsing errors
	if (!ok) {
		error.setCode(QNetworkReply::ProtocolFailure);
		error.setMessage("Google Tasks server returned an invalid JSON string");
		error.setGtasksMessage(responseString);
	}

	parseReply(response, error);
	m_reply->deleteLater();
	this->deleteLater();
}

} // namespace GTasks
