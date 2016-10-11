#ifndef ROFI_WIDGET_H
#define ROFI_WIDGET_H
#include <glib.h>
#include <cairo.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
/**
 * @defgroup widgets widgets
 *
 * Generic abstract widget class. Widgets should 'inherit' from this class (first structure in there structure should be
 * widget).
 * The generic widget implements generic functions like get_width, get_height, draw, resize, update, free and
 * clicked.
 * It also holds information about how the widget should be packed.
 *
 * @{
 */
typedef struct _widget   widget;

/**
 * Callback for when widget is clicked.
 */
typedef gboolean ( *widget_clicked_cb )( widget *, xcb_button_press_event_t *, void * );

/** Macro to get widget from an implementation (e.g. textbox/scrollbar) */
#define WIDGET( a )    ( ( a ) != NULL ? (widget *) ( a ) : NULL )

/**
 * @param widget The widget to check
 * @param x The X position relative to parent window
 * @param y the Y position relative to parent window
 *
 * Check if x,y falls within the widget.
 *
 * @return TRUE if x,y falls within the widget
 */
int widget_intersect ( const widget *widget, int x, int y );

/**
 * @param widget The widget to move
 * @param x The new X position relative to parent window
 * @param y The new Y position relative to parent window
 *
 * Moves the widget.
 */
void widget_move ( widget *widget, short x, short y );

/**
 * @param widget Handle to widget
 *
 * Check if widget is enabled.
 * @returns TRUE when widget is enabled.
 */
gboolean widget_enabled ( widget *widget );
/**
 * @param widget Handle to widget
 *
 * Disable the widget.
 */
void widget_disable ( widget *widget );
/**
 * @param widget Handle to widget
 *
 * Enable the widget.
 */
void widget_enable ( widget *widget );

/**
 * @param tb  Handle to the widget
 * @param draw The cairo object used to draw itself.
 *
 * Render the textbox.
 */
void widget_draw ( widget *widget, cairo_t *d );

/**
 * @param tb  Handle to the widget
 *
 * Free the widget and all allocated memory.
 */
void widget_free ( widget *widget );

/**
 * @param widget The widget toresize
 * @param w The new width
 * @param h The new height
 *
 * Resizes the widget.
 */
void widget_resize ( widget *widget, short w, short h );

int widget_get_height ( widget *widget );
int widget_get_width ( widget *widget );

void widget_update ( widget *widget );
void widget_queue_redraw ( widget *widget );
gboolean widget_need_redraw ( widget *wid );

gboolean widget_clicked ( widget *wid, xcb_button_press_event_t *xbe );

// Signal!
void widget_set_clicked_handler ( widget *wid, widget_clicked_cb cb, void *udata );

/*@}*/
#endif // ROFI_WIDGET_H
