/*
  This file is part of the Better Inbox project
  Copyright (c) 2010 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#include "error.h"
#include "error_p.h"

#include <QString>

namespace GTasks {

Error::Error()
	: d(new ErrorPrivate)
{
}

Error::~Error()
{
}

Error::Error(const Error& other)
	: d(other.d)
{
}

Error& Error::operator=(const Error& other)
{
	if (this != &other) {
		d = other.d;
	}
	return *this;
}

ErrorPrivate::ErrorPrivate()
	: QSharedData(),
	  code(QNetworkReply::NoError),
	  message(""),
	  httpCode(0),
	  gtasksMessage("")
{
}

ErrorPrivate::ErrorPrivate(const ErrorPrivate& other)
	: QSharedData(other),
	  code(other.code),
	  message(other.message),
	  httpCode(other.httpCode),
	  gtasksMessage(other.gtasksMessage)
{
}

// Getters
QNetworkReply::NetworkError Error::code()          const { return d->code; }
QString                     Error::message()       const { return d->message; }
int                         Error::httpCode()      const { return d->httpCode; }
QString                     Error::gtasksMessage() const { return d->gtasksMessage; }

// Setters
void Error::setCode(QNetworkReply::NetworkError code) { d->code = code; }
void Error::setMessage(const QString& message) { d->message = message; }
void Error::setHttpCode(int httpCode) { d->httpCode = httpCode; }
void Error::setGtasksMessage(const QString& gtasksMessage) { d->gtasksMessage = gtasksMessage; }

} // namespace GTasks
