/*
  This file is part of the Better Inbox project
  Copyright (c) 2011 Better Inbox and/or Gregory Schlomoff.
  All rights reserved.
  contact@betterinbox.com
*/

#ifndef MODEL_H
#define MODEL_H

#include <QSharedData>
#include <QString>
#include <QVariant>

class Model : public QSharedData
{
public:
    //Model();

	QVariantMap serialize();
	void deserialize(QVariantMap data);
};

#endif // MODEL_H
