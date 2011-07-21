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

/**
 * SECTION:clutter-gegl
 * @short_description: Actor for displaying
 *
 * #ClutterGegl is a #ClutterTexture that displays text.
 */
#include "clutter-gegl.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

G_DEFINE_TYPE (ClutterGegl, clutter_gegl, CLUTTER_TYPE_TEXTURE);

enum
{
  PROP_0,
  PROP_RENDER_WIDTH,
  PROP_RENDER_HEIGHT,
  PROP_NODE,
  PROP_X,
  PROP_Y,
  PROP_SCALE
};

#define CLUTTER_GEGL_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), CLUTTER_TYPE_GEGL, ClutterGeglPrivate))

struct _ClutterGeglPrivate
{
  GeglNode      *node;
  guchar        *buffer;
  gint           width, height;
  gint           x, y;

  gdouble        scale;

  guint          monitor_id;
  GeglProcessor *processor;
};

void
gegl_view_repaint (ClutterGegl *view);
static void clutter_gegl_render (ClutterGegl *view);

static void
computed_event (GeglNode      *self,
                GeglRectangle *rect,
                ClutterGegl   *view)
{
  ClutterGeglPrivate  *priv;
  guchar              *buffer;

  g_assert (CLUTTER_IS_ACTOR (view));

  priv = CLUTTER_GEGL_GET_PRIVATE (view);

  if (!priv->node)
    return;

  /* XXX: should reuse a buffer allocation, to reduce alloc/free load */
  buffer = g_malloc (rect->width * rect->height * 4);
  gegl_node_blit (priv->node, priv->scale,
                  rect,
                  babl_format ("R'G'B'A u8"),
                  buffer,
                  rect->width * 4,
                  GEGL_BLIT_CACHE);

  clutter_texture_set_area_from_rgb_data (CLUTTER_TEXTURE (view),
                                          buffer,
                                          TRUE,
                                          rect->x, rect->y,
                                          rect->width, rect->height,
                                          rect->width * 4,  /* rowstride */
                                          4,                /* bpp   */
                                          0,                /* flags */
                                          NULL);            /* error */
  g_free (buffer);
}

static void
invalidated_event (GeglNode      *self,
                   GeglRectangle *rect,
                   ClutterGegl   *view)
{
  gegl_view_repaint (view);
  clutter_gegl_render (view); /* */
  clutter_actor_queue_redraw (CLUTTER_ACTOR (view));
}

static guint rerender_idle = 0;

static gboolean invalidate_idle (gpointer view)
{
  invalidated_event (NULL, NULL, view);
  rerender_idle = 0;
  return FALSE;
}

static void
queue_invalidated (ClutterGegl *view)
{
  if (!rerender_idle)
    rerender_idle = g_idle_add_full (G_PRIORITY_DEFAULT_IDLE+1000, invalidate_idle, view, NULL);
}

static void
clutter_gegl_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  ClutterGegl        *gegl;
  ClutterGeglPrivate *priv;

  gegl = CLUTTER_GEGL (object);
  priv = CLUTTER_GEGL_GET_PRIVATE (gegl);

  switch (prop_id)
    {
      case PROP_RENDER_WIDTH:
        priv->width = g_value_get_int (value);
        if (priv->buffer)
          {
            g_free (priv->buffer);
            priv->buffer = NULL;
          }
        clutter_actor_queue_redraw (CLUTTER_ACTOR(gegl));
        break;

      case PROP_RENDER_HEIGHT:
        priv->height = g_value_get_int (value);
        if (priv->buffer)
          {
            g_free (priv->buffer);
            priv->buffer = NULL;
          }
        clutter_actor_queue_redraw (CLUTTER_ACTOR(gegl));
        break;

    case PROP_NODE:
      if (priv->node)
        {
          g_object_unref (priv->node);
        }

      if (g_value_get_object (value))
        {
          priv->node = GEGL_NODE (g_value_dup_object (value));

          g_signal_connect_object (priv->node, "computed",
                                   G_CALLBACK (computed_event),
                                   gegl, 0);
          g_signal_connect_object (priv->node, "invalidated",
                                   G_CALLBACK (invalidated_event),
                                   gegl, 0);
          clutter_actor_queue_redraw (CLUTTER_ACTOR(gegl));
        }
      else
        {
          priv->node = NULL;
        }
      break;
    case PROP_X:
      priv->x = g_value_get_int (value);
      queue_invalidated (gegl);
      break;
    case PROP_Y:
      priv->y = g_value_get_int (value);
      queue_invalidated (gegl);
      break;
    case PROP_SCALE:
      priv->scale = g_value_get_double (value);
      queue_invalidated (gegl);
      break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
clutter_gegl_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  ClutterGegl        *gegl;
  ClutterGeglPrivate *priv;

  gegl = CLUTTER_GEGL (object);
  priv = CLUTTER_GEGL_GET_PRIVATE (gegl);

  switch (prop_id)
    {
      case PROP_RENDER_WIDTH:
        g_value_set_int (value, priv->width);
        break;

      case PROP_RENDER_HEIGHT:
        g_value_set_int (value, priv->height);
        break;

      case PROP_NODE:
        g_value_set_object (value, priv->node);
        break;

      case PROP_X:
        g_value_set_int (value, priv->x);
        break;

      case PROP_Y:
        g_value_set_int (value, priv->y);
        break;

      case PROP_SCALE:
        g_value_set_double (value, priv->scale);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
clutter_gegl_dispose (GObject *object)
{
  ClutterGegl         *self = CLUTTER_GEGL (object);
  ClutterGeglPrivate  *priv;

  priv = CLUTTER_GEGL_GET_PRIVATE (self);

  if (priv->node)
    {
      g_object_unref (priv->node);
      priv->node = NULL;
    }
  if (priv->processor)
    {
      gegl_processor_destroy (priv->processor);
      priv->processor = NULL;
    }
  if (priv->monitor_id)
    {
      g_source_remove (priv->monitor_id);
      priv->monitor_id = 0;
    }

  G_OBJECT_CLASS (clutter_gegl_parent_class)->dispose (object);
}

static void
clutter_gegl_finalize (GObject *object)
{
  ClutterGegl         *self = CLUTTER_GEGL (object);
  ClutterGeglPrivate  *priv;

  priv = CLUTTER_GEGL_GET_PRIVATE (self);

  if (priv->buffer)
    {
      g_free (priv->buffer);
      priv->buffer = NULL;
    }
  G_OBJECT_CLASS (clutter_gegl_parent_class)->finalize (object);
}


static GObject*
clutter_gegl_constructor (GType                  type,
                          guint                  n_construct_properties,
                          GObjectConstructParam *construct_properties)
{
  ClutterGegl         *view;
  ClutterGeglPrivate  *priv;
  GObject             *obj;

  obj = G_OBJECT_CLASS (clutter_gegl_parent_class)->constructor
        (type, n_construct_properties, construct_properties);

  /* Now all of the object properties are set */

  view = CLUTTER_GEGL (obj);
  priv = CLUTTER_GEGL_GET_PRIVATE (view);

  /*g_return_val_if_fail (priv->width && priv->height, NULL);*/

  if (priv->width == 0 ||
      priv->height == 0)
    {
      GeglRectangle r = gegl_node_get_bounding_box (priv->node);
      priv->width = r.width;
      priv->height = r.height;
    }


  clutter_actor_set_size (CLUTTER_ACTOR (view), priv->width, priv->height);
  gegl_view_repaint (view);
  clutter_gegl_render (view);
  return obj;
}

static void
clutter_gegl_class_init (ClutterGeglClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize     = clutter_gegl_finalize;
  gobject_class->dispose      = clutter_gegl_dispose;
  gobject_class->set_property = clutter_gegl_set_property;
  gobject_class->get_property = clutter_gegl_get_property;
  gobject_class->constructor  = clutter_gegl_constructor;

  g_type_class_add_private (gobject_class, sizeof (ClutterGeglPrivate));

#define PARAM_FLAGS    (G_PARAM_CONSTRUCT_ONLY | \
                        G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | \
                        G_PARAM_STATIC_BLURB | \
                        G_PARAM_READABLE | G_PARAM_WRITABLE)

  g_object_class_install_property (gobject_class,
                                   PROP_RENDER_WIDTH,
                                   g_param_spec_int ("render-width",
                                                     "Render-Width",
                                                     "Base width of rectangle to render",
                                                     0, G_MAXINT,
                                                     0,
                                                     PARAM_FLAGS));
  g_object_class_install_property (gobject_class,
                                   PROP_RENDER_HEIGHT,
                                   g_param_spec_int ("render-height",
                                                     "Render-Height",
                                                     "Base height of rectangle to render",
                                                     0, G_MAXINT,
                                                     0,
                                                     PARAM_FLAGS));

  g_object_class_install_property (gobject_class, PROP_X,
                                   g_param_spec_int ("x0",
                                                     "X",
                                                     "X origin",
                                                     G_MININT, G_MAXINT, 0,
                                                     G_PARAM_CONSTRUCT |
                                                     G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_Y,
                                   g_param_spec_int ("y0",
                                                     "Y",
                                                     "Y origin",
                                                     G_MININT, G_MAXINT, 0,
                                                     G_PARAM_CONSTRUCT |
                                                     G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_SCALE,
                                   g_param_spec_double ("scale",
                                                        "Scale",
                                                        "Zoom factor",
                                                        0.0, 100.0, 1.00,
                                                        G_PARAM_CONSTRUCT |
                                                        G_PARAM_READWRITE));
  g_object_class_install_property (gobject_class, PROP_NODE,
                                   g_param_spec_object ("node",
                                                        "Node",
                                                        "The node to render",
                                                        G_TYPE_OBJECT,
                                                        G_PARAM_CONSTRUCT |
                                                        G_PARAM_READWRITE));



#undef PARAM_FLAGS
}

static void
clutter_gegl_init (ClutterGegl *self)
{
  ClutterGeglPrivate *priv;
  priv = CLUTTER_GEGL_GET_PRIVATE (self);
  priv++; /* shut up gcc */
}

/**
 * clutter_gegl_new
 * @width: clutter gegl surface width
 * @height: clutter gegl surface height
 *
 * Creates a new #ClutterGegl texture.
 *
 * Return value: a #ClutterGegl texture
 */
ClutterActor*
clutter_gegl_new (guint width,
                  guint height)
{
  return g_object_new (CLUTTER_TYPE_GEGL,
                       "render-width", width,
                       "render-height", height,
                       NULL);
}


ClutterActor * clutter_gegl_new_from_gegl_node (GeglNode *node)
{
  GeglRectangle extent = gegl_node_get_bounding_box (node);
  return clutter_gegl_new_from_gegl_node_with_size (node, extent.width, extent.height);
}



ClutterActor * clutter_gegl_new_from_gegl_node_with_size (GeglNode *node,
                                                          guint     width,
                                                          guint     height)
{
  return g_object_new (CLUTTER_TYPE_GEGL,
                       "render-width", width,
                       "render-height", height,
                       "node", node,
                       NULL);
}

static void
clutter_gegl_render (ClutterGegl *view)
{
  /* FIXME: should be optimized and handle ROIs (and still keep the buffer around) */
  ClutterGeglPrivate  *priv;
  GeglRectangle        roi;
  guchar              *buffer;

  g_assert (CLUTTER_IS_ACTOR (view));
  priv = CLUTTER_GEGL_GET_PRIVATE (view);

  if (!priv->node)
    return;

  buffer = g_malloc (priv->width * priv->height * 4);

  roi.x = priv->x;
  roi.y = priv->y;
  roi.width = priv->width;
  roi.height = priv->height;

  gegl_node_blit (priv->node, priv->scale,
                  &roi,
                  babl_format ("R'G'B'A u8"),
                  buffer,
                  GEGL_AUTO_ROWSTRIDE,
                  GEGL_BLIT_CACHE|GEGL_BLIT_DIRTY);

  clutter_texture_set_from_rgb_data (CLUTTER_TEXTURE (view),
                                     buffer,
                                     TRUE,               /* has_alpha */
                                     priv->width,
                                     priv->height,
                                     priv->width * 4,   /*(4 * priv->width + 3) &~ 3,*/
                                     4,
                                     0,
                                     NULL);
  g_free (buffer);

  if (CLUTTER_ACTOR_IS_VISIBLE (CLUTTER_ACTOR (view)))
    clutter_actor_queue_redraw (CLUTTER_ACTOR (view));
}

/**
 * clutter_gegl_create
 * @gegl:  A #ClutterGegl texture.
 *
 * Creates a new gegl context #ClutterGegl texture.
 *
 * Return value: a newly created gegl context. Free with gegl_destroy()
 * when you are done drawing.
 */
ClutterActor * clutter_gegl_parse_xml (const gchar *xml)
{
  return NULL;
}

static gboolean
task_monitor (ClutterGegl *view)
{
  ClutterGeglPrivate *priv = CLUTTER_GEGL_GET_PRIVATE (view);
  if (priv->processor == NULL ||
      priv->monitor_id == 0)
    {
      priv->monitor_id = 0;
      return FALSE;
    }
  if (gegl_processor_work (priv->processor, NULL))
    return TRUE;

  priv->monitor_id = 0;
  return FALSE;
}

void
gegl_view_repaint (ClutterGegl *view)
{
  ClutterGeglPrivate *priv = CLUTTER_GEGL_GET_PRIVATE (view);
#if 0
  ClutterActor  *actor = CLUTTER_ACTOR (view);
  GeglRectangle  roi    = { priv->x / priv->scale, priv->y / priv->scale,
                            ceil(clutter_actor_get_width (actor) / priv->scale+1),
                            ceil(clutter_actor_get_height (actor) / priv->scale+1) };
#endif
  GeglRectangle  roi    = { 0, 0, priv->width, priv->height };

  if (priv->monitor_id == 0)
    {
      priv->monitor_id = g_idle_add_full (G_PRIORITY_LOW,
                                          (GSourceFunc) task_monitor, view,
                                          NULL);

      if (priv->processor == NULL)
        {
          if (priv->node)
            priv->processor = gegl_node_new_processor (priv->node, &roi);
        }
    }
  if (priv->processor)
    gegl_processor_set_rectangle (priv->processor, &roi);
}

GeglProcessor *gegl_view_get_processor (ClutterGegl *view)
{
  ClutterGeglPrivate *priv = CLUTTER_GEGL_GET_PRIVATE (view);
  return priv->processor;
}
