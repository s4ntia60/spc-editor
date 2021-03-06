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

#include "qneblock.h"

//#include <QPen>
#include <qpen.h>
//#include <QGraphicsScene>
#include <qgraphicsscene.h>
//#include <QFontMetrics>
#include <qfontmetrics.h>
//#include <QPainter>
#include <qpainter.h>
#include <qmessagebox.h>
#include <iostream>
#include <qpushbutton.h>
#include "qneport.h"
#include <iostream>
#include "NodesManager.h"
#include "Form1.h"
#include <qlabel.h>
#include <qtextedit.h>



QNEBlock::QNEBlock(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	std::cout << "Creating Block" << std::endl;
	titulo = "Block Parent";
	QPainterPath p;
	p.addRoundedRect(-50, -15, 100, 30, 5, 5);
	setPath(p);
	setPen(QPen(Qt::darkGreen));
	setBrush(Qt::green);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	horzMargin = 20;
	vertMargin = 5;
	width = horzMargin;
	height = vertMargin;
	


	floatValidator = new QDoubleValidator(0, 100, 3, this);
	
	
	MANAGER->RegisterNode(this);
	std::cout << "Creating Block Completed" << std::endl;

	



}

QNEPort* QNEBlock::addPort(const QString &name, bool isOutput, int flags, int ptr)
{
	QNEPort *port = new QNEPort(this, name);
	port->setName(name);
	port->setIsOutput(isOutput);
	port->setNEBlock(this);
	port->setPortFlags(flags);
	port->setPtr(ptr);
	if (!scene()) std::cout << "Scene is Null" << std::endl; 
	QFontMetrics fm(scene()->font());
	
	int w = fm.width(name);
	int h = fm.height();
	port->setPos(0, height + h/2);
	
	if (w > width - horzMargin)
		width = w + horzMargin;
	
	if (GetOutPutsNumber() > GetInPutsNumber())
		height = h * GetOutPutsNumber() + 25;
	else
		height = h * GetInPutsNumber() + 25;
	
	//height += h;
	
	QPainterPath p;
	p.addRoundedRect(-width/2, -height/2, width, height, 2.5, 2.5);
	setPath(p);
	int y = -height / 2 + vertMargin + port->radius() + 5;
	

	// Ordenar entradas
	foreach(QGraphicsItem *port_, childItems()) 
	{
		if (port_->type() != QNEPort::Type)
			continue;

		QNEPort *port = (QNEPort*) port_;
		if (!port->isOutput())
		{
			port->setPos(-width / 2 - port->radius(), y);
			y += h;
		}
	}
	// Ordenar Salidas
	y = -height / 2 + vertMargin + port->radius() + h + 5;
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() != QNEPort::Type)
			continue;

		QNEPort *port = (QNEPort*)port_;
		if (port->isOutput())
		{
			port->setPos(width / 2 + port->radius(), y);
			y += h;
		}
	}

	return port;
}

QNEPort *  QNEBlock::addInputPort(const QString &name)
{
	return addPort(name, false);
}

QNEPort * QNEBlock::addOutputPort(const QString &name)
{
	return addPort(name, true);
}

void QNEBlock::addInputPorts(const QStringList &names)
{
	foreach(QString n, names)
		addInputPort(n);
}

void QNEBlock::addOutputPorts(const QStringList &names)
{
	foreach(QString n, names)
		addOutputPort(n);
}

void QNEBlock::save(QDataStream &ds)
{
	ds << pos();

	int count(0);

	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() != QNEPort::Type)
			continue;

		count++;
	}

	ds << count;

	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() != QNEPort::Type)
			continue;

		QNEPort *port = (QNEPort*) port_;
		ds << (quint64) port;
		ds << port->portName();
		ds << port->isOutput();
		ds << port->portFlags();
	}
}

void QNEBlock::load(QDataStream &ds, QMap<quint64, QNEPort*> &portMap)
{
	QPointF p;
	ds >> p;
	setPos(p);
	int count;
	ds >> count;
	for (int i = 0; i < count; i++)
	{
		QString name;
		bool output;
		int flags;
		quint64 ptr;

		ds >> ptr;
		ds >> name;
		ds >> output;
		ds >> flags;
		portMap[ptr] = addPort(name, output, flags, ptr);
	}
}

#include <QStyleOptionGraphicsItem>

void QNEBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	if (isSelected())
	{
		painter->setPen(QPen(QColor(203,203,203)));
		painter->setBrush(QBrush(QColor(203,203,203)));
		SetPortFonts(QColor(203, 203, 203));

	} else 
	{
		painter->setPen(QPen(QColor(155, 155, 155)));
		painter->setBrush(QBrush(QColor(155, 155, 155)));
		SetPortFonts(QColor(155, 155, 155));
	}

	painter->drawPath(path());
}


void QNEBlock::SetPortFonts(QColor color)
{
	
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
		{
			QNEPort *port = (QNEPort*)port_;
			if (port)
				port->SetLabelColor(color);
		}
	}
	
}

QNEBlock* QNEBlock::clone()
{
	QNEBlock *b = new QNEBlock(0);
	this->scene()->addItem(b);

	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
		{
			QNEPort *port = (QNEPort*) port_;
			b->addPort(port->portName(), port->isOutput(), port->portFlags(), port->ptr());
		}
	}

	return b;
}

QVector<QNEPort*> QNEBlock::ports()
{
	QVector<QNEPort*> res;
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
			res.append((QNEPort*) port_);
	}
	return res;
}

int QNEBlock::GetOutPutsNumber()
{
	int count = 0;
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
		{
			QNEPort *port = (QNEPort*)port_;
			if (port->isOutput())
				count++;
		}
	}
	return count;
}

int QNEBlock::GetInPutsNumber()
{
	int count = 0;
	foreach(QGraphicsItem *port_, childItems())
	{
		if (port_->type() == QNEPort::Type)
		{
			QNEPort *port = (QNEPort*)port_;
			if (!port->isOutput())
				count++;
		}
	}
	return count;
}

QVariant QNEBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{
	
	std::cout << titulo << std::endl;
	Q_UNUSED(change);

	if (this->isSelected())
	{
		
	}
	if (change == ItemSelectedHasChanged)
	{
		if (value.toBool())
		{
			if (form1)
				form1->ShowNodeMenu(this);
		}
	}

	return value;
}

void QNEBlock::Init()
{

}

std::string QNEBlock::Resolve()
{
	return "";
}

void QNEBlock::SetId(int val)
{
	m_id = val;
}
void QNEBlock::SetGruopId(int val)
{
	m_type = val;
}

int QNEBlock::GetId()
{
	return m_id;
}

int QNEBlock::GetType()
{
	return m_type;
}

void QNEBlock::SetForm1(Form1 * form1)
{
	this->form1 = form1;
}

QGridLayout * QNEBlock::GetPropertiesForm()
{
	return NULL;
}


void  QNEBlock::HandleLostFocusMembers()
{
	// do nothig
}
