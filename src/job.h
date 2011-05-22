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

class QNetworkReply;
class QNetworkRequest;

namespace GTasks {

class Service;

class Job : public QObject {
	Q_OBJECT

public:
	enum HttpMethod { Get, Post, Put, Delete, Head };

	explicit Job(Service* service, HttpMethod method, QString path, const char* result);
	void start();
	void startAndCallback(QObject* object, const char* callbackSlot);

protected:
	void addRequestParam(const QString& param, const QVariant& value);
	void setRequestData(const QVariantMap& data);

protected slots:
	virtual void parseReply(const QVariantMap& response) = 0;

private slots:
	void parseReply();

private:
	Service* m_service;
	HttpMethod m_method;
	QString m_path;
	QMap<QString, QString> m_parameters;
	QVariantMap m_data;
	QNetworkReply* m_reply;
	const char* m_resultSignal;
};

}
#endif // GTASKS_JOB_H
