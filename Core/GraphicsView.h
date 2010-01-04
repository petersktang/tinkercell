/****************************************************************************

Copyright (c) 2008 Deepak Chandran
Contact: Deepak Chandran (dchandran1@gmail.com)
See COPYRIGHT.TXT

This is one of the main classes in Tinkercell
This file defines the GraphicsView class that is used to view the contents
of a GraphicsScene. The class inherits from QGraphicsView. The main capability
this class provides is the ability to show/hide items in this view without
affecting other views.

****************************************************************************/

#ifndef TINKERCELL_GRAPHICSVIEW_H
#define TINKERCELL_GRAPHICSVIEW_H

#include <stdlib.h>
#include <QtGui>
#include <QString>
#include <QPair>
#include <QFileDialog>
#include <QtDebug>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QAction>
#include <QPixmap>
#include <QMenu>
#include <QFile>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QHash>
#include <QUndoCommand>
#include <QGraphicsItemAnimation>
#include <QPrinter>

#include "DataTable.h"
#include "HistoryWindow.h"
#include "SymbolsTable.h"
#include "CloneItems.h"

#ifdef Q_WS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

namespace Tinkercell
{

	class NodeGraphicsItem;
	class ConnectionGraphicsItem;
	class ItemHandle;
	class ItemData;
	class NetworkWindow;
	class GraphicsScene;
	
	/*! \brief view for a graphics scene. 
		Provides the ability to set specific items invisible when they might
		might be visible in other views.
		\ingroup helper
	*/
	class MY_EXPORT GraphicsView : public QGraphicsView
	{
	public:
		/*! \brief background */
		QPixmap background;
		/*! \brief foreground */
		QPixmap foreground;
		/*! \brief the scene displayed by this view */
		GraphicsScene * scene;
		/*! \brief the network window that this view belongs to */
		NetworkWindow * networkWindow;
		/*! \brief default constructor
		*	\param NetworkWindow * window that this view belongs with
		*	\param QWidget * parent
		*/
		GraphicsView(NetworkWindow * networkWindow = 0, QWidget * parent = 0);
		/*! \brief show the given item in this view (does not affect other views of the same the scene)
		*	\param QGraphicsView* 
		*/
		virtual void showItem(QGraphicsItem*);
		/*! \brief hide the given item in this view (does not affect other views of the same the scene)
		*	\param QGraphicsView* 
		*/
		virtual void hideItem(QGraphicsItem*);
		/*! \brief show the given items in this view (does not affect other views of the same the scene)
		*	\param QList<QGraphicsItem*>&* 
		*/
		virtual void showItems(const QList<QGraphicsItem*>&);
		/*! \brief hide the given items in this view (does not affect other views of the same the scene)
		*	\param QList<QGraphicsItem*>&* 
		*/
		virtual void hideItems(const QList<QGraphicsItem*>&);

	protected:
		/*! \brief close window event -- removes this view from the network window's views list
		* \param QCloseEvent * event
		* \return void*/
		virtual void closeEvent(QCloseEvent *event);
		/*! \brief draw background*/
		virtual void drawBackground( QPainter * painter, const QRectF & rect );
		/*! \brief draw foreground*/
		virtual void drawForeground( QPainter * painter, const QRectF & rect );
		/*! \brief draw all items not in the hiddenItems list*/
		virtual void drawItems(QPainter *painter, int numItems,
                           QGraphicsItem *items[],
                           const QStyleOptionGraphicsItem options[]);
		/*! \brief drag on top event */
		virtual void dropEvent(QDropEvent *);
		/*! \brief drag and drop event*/
		virtual void dragEnterEvent(QDragEnterEvent *event);
		/*! \brief mouse wheel event*/
		virtual void wheelEvent(QWheelEvent * event);
		/*! \brief scroll event*/
		virtual void scrollContentsBy ( int dx, int dy );
		/*! \brief mouse event. sets the currentGraphicsView for NetworkWindow*/
		virtual void mousePressEvent ( QMouseEvent * event );
		/*! \brief mouse event. sets the currentGraphicsView for NetworkWindow*/
		virtual void keyPressEvent ( QKeyEvent * event );
		/*! \brief list of items to hide*/
		QHash<QGraphicsItem*,bool> hiddenItems;
		
		friend class GraphicsScene;
		friend class NetworkWindow;
	};
}

#endif
