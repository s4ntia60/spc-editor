/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of STANISLAW ADASZEWSKI nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef QNEBLOCK_H
#define QNEBLOCK_H

//#include <QGraphicsPathItem>
#include <qgraphicsitem.h>
#include <qstring.h>
#include <string>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <qtextedit.h>
#include <qvalidator.h>


class Form1;
class QNEPort;
class QNEBlock : public QGraphicsPathItem, public QObject
{

//Q_OBJECT

//signals :
//	virtual void valueChanged();

public:
	enum { Type = QGraphicsItem::UserType + 3 };

	QNEBlock(QGraphicsItem *parent = 0);

	QNEPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
	QNEPort * addInputPort(const QString &name);
	QNEPort * addOutputPort(const QString &name);
	void addInputPorts(const QStringList &names);
	void addOutputPorts(const QStringList &names);
	void save(QDataStream&);
	void load(QDataStream&, QMap<quint64, QNEPort*> &portMap);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QNEBlock* clone();
	QVector<QNEPort*> ports();
	int GetOutPutsNumber();
	int GetInPutsNumber();


	QTextEdit * descTextEdit;
	int type() const { return Type; }
	virtual void Init();
	virtual std::string Resolve();
	std::string  titulo;
	std::string  description;
	void SetId(int val);
	void SetGruopId(int val);
	int GetId();
	int GetType();	
	void SetForm1(Form1 * form1);
	virtual QGridLayout * GetPropertiesForm();
	virtual void HandleLostFocusMembers();

	QSizePolicy * policy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QSize minSizeField = QSize(150, 25); QSize maxSizeField = QSize(200, 25);
	QSize minSizeLabel = QSize(50, 25);	QSize maxSizeLabel = QSize(50, 25);
	QDoubleValidator * floatValidator;


	QNEPort * ROutPut;
	QNEPort * GOutPut;
	QNEPort * BOutPut;
	QNEPort * AOutPut;


protected:
	Form1 *  form1 = NULL;
	int m_type = 0;
	int m_id;

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	int horzMargin;
	int vertMargin;
	int width;
	int height;
	void SetPortFonts(QColor color);
};

#endif // QNEBLOCK_H
