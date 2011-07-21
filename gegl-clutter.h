/*
 * GeglClutter.
 *
 * An simple Clutter GEGL viewer actor:
 *
 * Created By Øyvind Kolås <pippin@gimp.org>/<pippin@o-hand.com> (c) 2007,
 * based on on Clutter cairo, authored By Matthew Allum
 * <mallum@openedhand.com> (C) 2006.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _HAVE_GEGL_CLUTTER_H
#define _HAVE_GEGL_CLUTTER_H

#include <glib-object.h>

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <clutter/clutter.h>

#include <gegl.h>

G_BEGIN_DECLS

#define GEGL_TYPE_CLUTTER    gegl_clutter_get_type ()

#define GEGL_CLUTTER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                               GEGL_TYPE_CLUTTER, GeglClutter))

#define GEGL_CLUTTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
                            GEGL_TYPE_CLUTTER, GeglClutterClass))

#define CLUTTER_IS_GEGL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                               GEGL_TYPE_CLUTTER))

#define CLUTTER_IS_GEGL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                            GEGL_TYPE_CLUTTER))

#define GEGL_CLUTTER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                              GEGL_TYPE_CLUTTER, GeglClutterClass))

typedef struct _GeglClutter        GeglClutter;
typedef struct _GeglClutterClass   GeglClutterClass;
typedef struct _GeglClutterPrivate GeglClutterPrivate;

struct _GeglClutter
{
  ClutterTexture        parent;
#if 0
  /*< private >*/
  GeglClutterPrivate   *priv;
#endif
};

struct _GeglClutterClass
{
  /*< private >*/
  ClutterTextureClass parent_class;

  void (*_gegl_clutter_1)(void);
  void (*_gegl_clutter_2)(void);
  void (*_gegl_clutter_3)(void);
  void (*_gegl_clutter_4)(void);
};

GType
gegl_clutter_get_type                          (void) G_GNUC_CONST;

ClutterActor * gegl_clutter_parse_xml          (const gchar *xml);

ClutterActor * gegl_clutter_new_from_gegl_node (GeglNode    *node);

ClutterActor * gegl_clutter_new_from_gegl_node_with_size (GeglNode    *node,
                                                          guint        width,
                                                          guint        height);

G_END_DECLS

#endif
