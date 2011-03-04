/****************************************************************************
 Copyright (c) 2008 Deepak Chandran
 Contact: Deepak Chandran (dchandran1@gmail.com)
 see COPYRIGHT.TXT

 This tool displays a plot based on the DataTable contained.
 
****************************************************************************/

#ifndef TINKERCELL_PLOT2DWIDGET_H
#define TINKERCELL_PLOT2DWIDGET_H

#include <QButtonGroup>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QColorDialog>
#include <QPen>
#include <QList>
#include <QColor>
#include <QDialog>
#include "PlotWidget.h"
#include "qwt_plot.h"
#include "qwt_color_map.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_curve.h"
#include "qwt_legend.h"
#include "qwt_data.h"
#include "qwt_text.h"
#include "qwt_symbol.h"
#include "qwt_plot_layout.h"
#include "qwt_plot_zoomer.h"
#include "qwt_legend_item.h"
#include "qwt_scale_draw.h"

namespace Tinkercell
{

	class PlotTool;
	class PlotWidget;
	class Plot2DWidget;
	class DataPlot;
	class GetPenInfoDialog;
	class ShowHideLegendItemsWidget;
	class PlotCurve;

	class DataColumn : public QwtData
	{
	public:
		DataColumn(const NumericalDataTable * data, int,int,int dt=1);
		virtual QwtData * copy() const;
		virtual size_t size() const;
		virtual double x(size_t index) const;
		virtual double y(size_t index) const;
	private:
		const NumericalDataTable * dataTable;
		int column, xaxis, dt;
				
		friend class DataPlot;
		friend class Plot2DWidget;
		friend class PlotCurve;
	};
	
	class PlotCurve: public QwtPlotCurve
	{
	public:
		PlotCurve(const QString& title, DataPlot * dataplot, int xaxis, int index, int dt);
	protected:
		void drawCurve (QPainter *p, int style, const QwtScaleMap &xMap, const QwtScaleMap &yMap, int from, int to) const;
		void 	drawSymbols (QPainter *p, const QwtSymbol &, const QwtScaleMap &xMap, const QwtScaleMap &yMap, int from, int to) const;
		DataColumn dataColumn;
		DataPlot * dataPlot;
		
		friend class DataPlot;
		friend class Plot2DWidget;
		friend class DataColumn;
	};
	
	class DataAxisLabelDraw : public QwtScaleDraw
	{
		public:
			DataAxisLabelDraw(const QStringList&);
			virtual QwtText label(double v) const;
			Qt::Orientation orientation() const;
		protected:
			QStringList labels;
	};
	
	class DataPlot : public QwtPlot
	{
		Q_OBJECT
	public:
		DataPlot(QWidget * parent = 0);
		void plot(const NumericalDataTable&,int x, const QString& title,  bool append = false);
		virtual QSize minimumSizeHint() const;
		virtual QSize sizeHint() const;
		virtual void setLogX(bool);
		virtual void setLogY(bool);
		
	protected:
		QList< NumericalDataTable* > dataTables;
		QwtPlotZoomer * zoomer;
		static QStringList hideList;
		static QList<QPen> penList;
		int xcolumn, numBars;
		PlotTool::PlotType type;
		void processData(NumericalDataTable *);
		void replotUsingHideList();
		bool usesRowNames() const;
		
	protected slots:
		void itemChecked(QwtPlotItem *,	bool);
		void setXAxis(int);
		
		friend class PlotCurve;
		friend class Plot2DWidget;
		friend class GetPenInfoDialog;
		friend class ShowHideLegendItemsWidget;
	};
	
	class GetPenInfoDialog : public QDialog
	{	
		Q_OBJECT
	public:
		GetPenInfoDialog(QWidget * parent);
		void setPen(const QPen&, int);
		QPen getPen() const;
		int currentIndex() const;
	private slots:
		void currentColorChanged ( const QColor & color );
	private:
		int index;
		QColor color;
		QColorDialog colorDialog;
		QDoubleSpinBox spinBox;
		QComboBox comboBox;
	};
	
	class ShowHideLegendItemsWidget : public QDialog
	{
		Q_OBJECT
	public:
		ShowHideLegendItemsWidget(DataPlot * plot, QWidget * parent);
		
	private slots:
		void updatePlot();
		void checkAll();
		void checkNone();
		
	private:
		DataPlot * plot;
		QStringList names;
		QList<QCheckBox*> checkBoxes;
	};

	/*!
	\brief A widget containing a data plot, legend and options. Can be used to plot
		line-plots, bar-plots, or histograms
	\ingroup plotting
	*/
	class TINKERCELLEXPORT Plot2DWidget : public PlotWidget
	{
		Q_OBJECT
		
	public:
		Plot2DWidget(PlotTool * parent = 0);
		virtual NumericalDataTable* data();
		virtual bool canAppendData() const;
		virtual void appendData(const NumericalDataTable&);
		virtual void plot(const NumericalDataTable& matrix,const QString& title,int x=0);
		virtual void updateData(const NumericalDataTable&);
		
	public slots:
		void setLogScale(int index, bool set=true);
		void print(QPaintDevice&);
		void exportData(const QString&, const QString &);
		void logX(bool);
		void logY(bool);
		void logAxis(int,bool);
		void setTitle();
		void setXLabel();
		void setYLabel();
		
		void setTitle(const QString&);
		void setXLabel(const QString&);
		void setYLabel(const QString&);
		
		void replotAllOther2DWidgets();
	
	private slots:
		void buttonPressed(int);
		void penSet();
		void legendConfigure();
		void mouseMoved(const QPoint&);
	
	private:
		QWidget * dialogWidget();
		GetPenInfoDialog * dialog;
		QString latex();
		DataPlot * dataPlot;
		QComboBox * axisNames;
		QComboBox * lineTypes;
		QButtonGroup buttonsGroup;
	};

}
#endif