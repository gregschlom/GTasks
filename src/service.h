/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_SERVICE_H
#define GTASKS_SERVICE_H

#include <QObject>

#include "simpleoauth/oauth_token.h"

class QNetworkAccessManager;

namespace GTasks {

class ListTasks;

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QNetworkAccessManager* networkManager, QObject *parent = 0);

	void setApiKey(QString key);
	void setToken(OAuth::Token);

	QNetworkAccessManager* networkManager() const;
	QString apiKey() const;
	QString baseUrl() const;
	OAuth::Token token() const;

	ListTasks* listTasks();

private:
	QNetworkAccessManager* m_networkManager;
	QString m_apiKey;
	OAuth::Token m_token;
	const QString m_baseUrl;
};

}

#endif // GTASKS_SERVICE_H
