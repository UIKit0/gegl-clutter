/*
 * ClutterGegl.
 *
 * An simple Clutter GEGL viewer actor:
 *
 * Created By Øyvind Kolås <pippin@gimp.org|o-hand.com> (c) 2007,
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

#include <clutter/clutter.h>
#include "clutter-gegl.h"
#include "math.h"

#define DEFAULT_COMPOSITION \
"<?xml version='1.0' encoding='UTF-8'?> <gegl> <node operation='gegl:crop'> <params> <param name='x'>0</param> <param name='y'>0</param> <param name='width'>690</param> <param name='height'>670</param> </params> </node> <node operation='gegl:over'> <node operation='gegl:translate'> <params> <param name='x'>14</param> <param name='y'>613</param> </params> </node> <node operation='gegl:opacity'> <params> <param name='value'>0.59999999999999998</param> </params> </node> <node name='text' operation='gegl:text'> <params> <param name='string'>2000-2008 ? Calvin Williamson, Caroline Dahloff, Manish Singh, Jay Cox, Daniel Rogers, Sven Neumann, Michael Natterer,  ?yvind Kol?s, Philip Lafleur, Dominik Ernst, Richard Kralovic, Kevin Cozens, Victor Bogado, Martin Nordholts, Geert Jordaens, Michael Schumacher, John Marshall, ?tienne Bersac, Mark Probst, H?kon Hitland, Tor Lillqvist, Hans Breuer, Deji Akingunola, Bradley Broom, Hans Petter Jansson, Jan Heller, dmacks@netspace.org, Sven Anders, Hubert Figui?re, Sam Hocevar, yahvuu at gmail.com, Nicolas Robidoux, Garry R. Osgood, Shlomi Fish, Jakub Steiner and Tonda Tavalec</param> <param name='font'>Sans</param> <param name='size'>8</param> <param name='color'>rgb(0.0000, 0.0000, 0.0000)</param> <param name='wrap'>628</param> <param name='alignment'>0</param> <param name='width'>622</param> <param name='height'>40</param> </params> </node> </node> <node operation='gegl:over'> <node operation='gegl:translate'> <params> <param name='x'>300</param> <param name='y'>500</param> </params> </node> <node operation='gegl:over'> <node operation='gegl:translate'> <params> <param name='x'>0</param> <param name='y'>0</param> </params> </node> <node operation='gegl:dropshadow'> <params> <param name='opacity'>1.2</param> <param name='x'>0</param> <param name='y'>0</param> <param name='radius'>8</param> </params> </node> <gegl:path d='M0,50 C0,78 24,100 50,100 C77,100 100,78 100,50 C100,45 99,40 98,35 C82,35 66,35 50,35 C42,35 35,42 35,50 C35,58 42,65 50,65 C56,65 61,61 64,56 C67,51 75,55 73,60 C69,69 60,75 50,75 C36,75 25,64 25,50 C25,36 36,25 50,25 L93,25 C83,9 67,0 49,0 C25,0 0,20 0,50 z' fill='white'/> </node> <node operation='gegl:over'> <node operation='gegl:translate'> <params> <param name='x'>88</param> <param name='y'>0</param> </params> </node> <node operation='gegl:dropshadow'> <params> <param name='opacity'>1.2</param> <param name='x'>0</param> <param name='y'>0</param> <param name='radius'>8</param> </params> </node> <node operation='gegl:path'> <params> <param name='d'>M50,0 C23,0 0,22 0,50 C0,77 22,100 50,100 C68,100 85,90 93,75 L40,75 C35,75 35,65 40,65 L98,65 C100,55 100,45 98,35 L40,35 C35,35 35,25 40,25 L93,25 C84,10 68,0 50,0 z</param> <param name='fill'>rgb(1.0000, 1.0000, 1.0000)</param> </params> </node> </node> <node operation='gegl:over'> <node operation='gegl:translate'> <params> <param name='x'>176</param> <param name='y'>0</param> </params> </node> <node operation='gegl:dropshadow'> <params> <param name='opacity'>1.2</param> <param name='x'>0</param> <param name='y'>0</param> <param name='radius'>8</param> </params> </node> <node operation='gegl:path'> <params> <param name='d'>M0,50 C0,78 24,100 50,100 C77,100 100,78 100,50 C100,45 99,40 98,35 C82,35 66,35 50,35 C42,35 35,42 35,50 C35,58 42,65 50,65 C56,65 61,61 64,56 C67,51 75,55 73,60 C69,69 60,75 50,75 C36,75 25,64 25,50 C25,36 36,25 50,25 L93,25 C83,9 67,0 49,0 C25,0 0,20 0,50 z</param> <param name='fill'>rgb(1.0000, 1.0000, 1.0000)</param> </params> </node> </node> <node operation='gegl:translate'> <params> <param name='x'>264</param> <param name='y'>0</param> </params> </node> <node operation='gegl:dropshadow'> <params> <param name='opacity'>1.2</param> <param name='x'>0</param> <param name='y'>0</param> <param name='radius'>8</param> </params> </node> <node operation='gegl:path'> <params> <param name='d'>M30,4 C12,13 0,30 0,50 C0,78 23,100 50,100 C71,100 88,88 96,71 L56,71 C42,71 30,59 30,45 L30,4 z</param> <param name='fill'>rgb(1.0000, 1.0000, 1.0000)</param> </params> </node> </node> <node operation='gegl:rotate'> <params> <param name='origin-x'>0</param> <param name='origin-y'>0</param> <param name='filter'>linear</param> <param name='hard-edges'>false</param> <param name='lanczos-width'>3</param> <param name='degrees'>42</param> </params> </node> <node operation='gegl:checkerboard'> <params> <param name='x'>43</param> <param name='y'>44</param> <param name='x-offset'>0</param> <param name='y-offset'>0</param> <param name='color1'>rgb(0.7097, 0.7097, 0.7097)</param> <param name='color2'>rgb(0.7661, 0.7661, 0.7661)</param> </params> </node> </gegl>"

int
main (int argc, char **argv)
{
  GeglNode        *gegl;
  ClutterActor    *geglview, *stage;
  ClutterColor     stage_color = { 0x99, 0xcc, 0xff, 0xff };

  clutter_init (&argc, &argv);
  gegl_init (&argc, &argv);

  stage = clutter_stage_get_default ();
  g_signal_connect (stage, "button-press-event",
                    G_CALLBACK (clutter_main_quit),
                    NULL);

  clutter_stage_set_color (CLUTTER_STAGE (stage),
		           &stage_color);

  if (argv[1])
    {
      gegl = gegl_node_new_from_file (argv[1]);
    }
  else
    {
      gegl = gegl_node_new_from_xml (DEFAULT_COMPOSITION, "");
    }

  geglview = clutter_gegl_new_from_gegl_node (gegl);
  clutter_group_add (CLUTTER_GROUP(stage), geglview);
  clutter_actor_set_size (stage, clutter_actor_get_width (geglview),
                                 clutter_actor_get_height (geglview));

  clutter_actor_show_all (CLUTTER_ACTOR(stage));

  clutter_main();

  return 1;
}
