/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef GTASKS_CACHE_H
#define GTASKS_CACHE_H

#include <QByteArray>

namespace GTasks {

class Cache
{
public:
	virtual QByteArray get(const QString& url, QString* etag) = 0;
	virtual void set(const QString& url, const QString& etag, const QByteArray& content) = 0;
};

}

#endif // GTASKS_CACHE_H
