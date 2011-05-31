/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_JOB_H
#define GTASKS_JOB_H

#include <QObject>
#include <QVariant>
#include <QUrl>

class QNetworkReply;
class QNetworkRequest;

namespace GTasks {

class Service;
class Error;

class Job : public QObject {
	Q_OBJECT

public:
	enum HttpMethod { Get, Post, Put, Delete, Head };

	explicit Job(Service* service, HttpMethod method, const QUrl& url, const char* result);
	void start();
	void startAndCallback(QObject* object, const char* callbackSlot);

protected:
	void addRequestParam(const QString& param, const QVariant& value);
	void setRequestData(const QVariantMap& data);
	virtual void parseReply(const QVariantMap& response, const GTasks::Error& error) = 0;

private slots:
	void parseReply();

private:
	Service* m_service;
	HttpMethod m_method;
	QUrl m_url;
	QMap<QString, QString> m_parameters;
	QVariantMap m_data;
	QNetworkReply* m_reply;
	const char* m_resultSignal;
};

}
#endif // GTASKS_JOB_H
