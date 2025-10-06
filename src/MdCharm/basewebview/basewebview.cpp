#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QApplication>
#include <QClipboard>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

#include "basewebview.h"
#include "resource.h"

BaseWebView::BaseWebView(QWidget *parent) :
    QWebEngineView(parent)
{
    // Enable scrolling for WebEngine
    setFocusPolicy(Qt::WheelFocus);
    // Ensure wheel events are properly handled
    setAttribute(Qt::WA_AcceptTouchEvents, false);
}

void BaseWebView::wheelEvent(QWheelEvent *event)
{
    // Ensure wheel events are passed to WebEngine
    QWebEngineView::wheelEvent(event);
}

void BaseWebView::contextMenuEvent(QContextMenuEvent *e)
{
    e->accept();
    QMenu *menu = new QMenu(this);
    QAction *copyAction = new QAction(QIcon(Resource::CopyIcon), tr("Copy"), menu);
    // Note: WebEngine doesn't provide direct access to selection state
    // Adding copy action unconditionally for now
    menu->addAction(copyAction);
    menu->addSeparator();
    
    QAction *printAction = new QAction(QIcon(Resource::PrintLargeIcon), tr("Print..."), menu);
    menu->addAction(printAction);
    QAction *printPreviewAction = new QAction(tr("Print Preview..."), menu);
    menu->addAction(printPreviewAction);
    QAction *action = menu->exec(e->globalPos());
    if(action==copyAction){
        // WebEngine uses different approach for copying
        page()->triggerAction(QWebEnginePage::Copy);
    } else if(action==printAction){
        QPrinter webViewPrinter(QPrinter::HighResolution);
        QPrintDialog printDialog(&webViewPrinter, this);
        printDialog.setWindowTitle(tr("Print..."));
        if(printDialog.exec()==QDialog::Accepted) {
            // WebEngine printing is handled differently
            page()->print(&webViewPrinter, [](bool success){});
        }
    } else if(action==printPreviewAction){
        QPrinter printer(QPrinter::HighResolution);
        QPrintPreviewDialog ppd(&printer, this, Qt::WindowMaximizeButtonHint);
        ppd.setWindowTitle(tr("Print Preview..."));
        // WebEngine print preview needs different handling
        ppd.showMaximized();
        ppd.exec();
    }
    menu->deleteLater();
}
