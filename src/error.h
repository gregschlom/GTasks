/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef ERROR_H
#define ERROR_H

#include <QSharedData>
#include <QNetworkReply>

class QString;

namespace GTasks {

class ErrorPrivate;

class Error
{
public:
	Error();
	Error(const Error& other);
	Error &operator=(const Error&);
	~Error();

	QNetworkReply::NetworkError code() const;
	QString message() const;
	int httpCode() const;
	QString gtasksMessage() const;

	void setCode(QNetworkReply::NetworkError code);
	void setMessage(const QString& message);
	void setHttpCode(int httpCode);
	void setGtasksMessage(const QString& gtasksMessage);

private:
	friend class ErrorPrivate;
	QSharedDataPointer<ErrorPrivate> d;
};

}

#endif // ERROR_H
