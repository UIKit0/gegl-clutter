/*
 * ClutterGegl.
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

#ifndef _HAVE_CLUTTER_GEGL_H
#define _HAVE_CLUTTER_GEGL_H

#include <glib-object.h>

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <clutter/clutter.h>

#include <gegl.h>

G_BEGIN_DECLS

#define CLUTTER_TYPE_GEGL    clutter_gegl_get_type ()

#define CLUTTER_GEGL(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                               CLUTTER_TYPE_GEGL, ClutterGegl))

#define CLUTTER_GEGL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
                            CLUTTER_TYPE_GEGL, ClutterGeglClass))

#define CLUTTER_IS_GEGL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                               CLUTTER_TYPE_GEGL))

#define CLUTTER_IS_GEGL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                            CLUTTER_TYPE_GEGL))

#define CLUTTER_GEGL_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                              CLUTTER_TYPE_GEGL, ClutterGeglClass))

typedef struct _ClutterGegl        ClutterGegl;
typedef struct _ClutterGeglClass   ClutterGeglClass;
typedef struct _ClutterGeglPrivate ClutterGeglPrivate;

struct _ClutterGegl
{
  ClutterTexture        parent;
#if 0
  /*< private >*/
  ClutterGeglPrivate   *priv;
#endif
};

struct _ClutterGeglClass
{
  /*< private >*/
  ClutterTextureClass parent_class;

  void (*_clutter_gegl_1)(void);
  void (*_clutter_gegl_2)(void);
  void (*_clutter_gegl_3)(void);
  void (*_clutter_gegl_4)(void);
};

GType
clutter_gegl_get_type                          (void) G_GNUC_CONST;

ClutterActor * clutter_gegl_parse_xml          (const gchar *xml);

ClutterActor * clutter_gegl_new_from_gegl_node (GeglNode    *node);

ClutterActor * clutter_gegl_new_from_gegl_node_with_size (GeglNode    *node,
                                                          guint        width,
                                                          guint        height);
                                                

G_END_DECLS

#endif
