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

#define DEFAULT_COMPOSITION "<?xml version='1.0' encoding='UTF-8'?> <gegl> <node operation='crop'> <params> <param name='x'>0.000000</param> <param name='y'>0.000000</param> <param name='width'>400.000000</param> <param name='height'>290.000000</param> </params> </node> <node operation='over'> <node operation='shift'> <params> <param name='x'>50.000000</param> <param name='y'>113.000000</param> </params> </node> <node operation='dropshadow'> <params> <param name='opacity'>2.000000</param> <param name='x'>2.000000</param> <param name='y'>2.000000</param> <param name='radius'>3.000000</param> </params> </node> <node operation='text'> <params> <param name='string'>A graph based image processing and\ncompositing engine.</param> <param name='font'>Sans</param> <param name='size'>10.000000</param> <param name='color'>rgb(1.0000, 1.0000, 1.0000)</param> <param name='wrap'>-1</param> <param name='alignment'>0</param> <param name='width'>178</param> <param name='height'>26</param> </params> </node> </node> <node operation='over'> <node operation='shift'> <params> <param name='x'>132.000000</param> <param name='y'>180.000000</param> </params> </node> <node operation='dropshadow'> <params> <param name='opacity'>2.000000</param> <param name='x'>2.000000</param> <param name='y'>2.000000</param> <param name='radius'>3.000000</param> </params> </node> <node operation='text'> <params> <param name='string'>2000-2007 © Calvin Williamson, Caroline Dahloff, Manish Singh, Jay Cox, Daniel Rogers, Sven Neumann, Michael Natterer, Øyvind Kolås, Philip Lafleur, Dominik Ernst, Richard Kralovic, Kevin Cozens, Victor Bogado, Martin Nordholts, Geert Jordaens, Michael Schumacher, Garry R. Osgood and Jakub Steiner</param> <param name='font'>Sans</param> <param name='size'>10.458599</param> <param name='color'>rgb(1.0000, 1.0000, 1.0000)</param> <param name='wrap'>240</param> <param name='alignment'>0</param> <param name='width'>237</param> <param name='height'>130</param> </params> </node> </node> <node operation='over'> <node name='dropshadow' operation='dropshadow'> <params> <param name='opacity'>-4.487179</param> <param name='x'>3.750000</param> <param name='y'>2.500000</param> <param name='radius'>10.597015</param> </params> </node> <node operation='shift'> <params> <param name='x'>42.000000</param> <param name='y'>23.000000</param> </params> </node> <node operation='text'> <params> <param name='string'>GEGL</param> <param name='font'>Sans</param> <param name='size'>76.038217</param> <param name='color'>rgb(0.3093, 0.3910, 0.1680)</param> <param name='wrap'>-1</param> <param name='alignment'>0</param> <param name='width'>208</param> <param name='height'>89</param> </params> </node> </node> <node operation='whitebalance'> <params> <param name='high-a-delta'>0.365079</param> <param name='high-b-delta'>0.026511</param> <param name='low-a-delta'>0.000000</param> <param name='low-b-delta'>0.000000</param> <param name='saturation'>0.319548</param> </params> </node> <node operation='brightness-contrast'> <params> <param name='contrast'>0.229008</param> <param name='brightness'>0.000000</param> </params> </node> <node operation='fractal-explorer'> <params> <param name='width'>400</param> <param name='height'>290</param> <param name='fractaltype'>1</param> <param name='xmin'>-1.312500</param> <param name='xmax'>0.000000</param> <param name='ymin'>-0.609375</param> <param name='ymax'>0.562500</param> <param name='iter'>100</param> <param name='cx'>-0.820312</param> <param name='cy'>0.195312</param> <param name='redstretch'>1.000000</param> <param name='greenstretch'>1.000000</param> <param name='bluestretch'>1.000000</param> <param name='redmode'>1</param> <param name='greenmode'>1</param> <param name='bluemode'>0</param> <param name='redinvert'>false</param> <param name='greeninvert'>false</param> <param name='blueinvert'>false</param> <param name='ncolors'>256</param> <param name='useloglog'>false</param> </params> </node> </gegl>"

int
main (int argc, char **argv)
{
  GeglNode        *gegl;
  ClutterActor    *geglview, *stage;
  ClutterColor     stage_color = { 0x99, 0xcc, 0xff, 0xff };

  clutter_init (&argc, &argv);
  gegl_init (&argc, &argv);

  stage = clutter_stage_get_default ();
  clutter_actor_set_size (stage, 512, 384);
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

  geglview = clutter_gegl_new_from_gegl_node (512, 384, gegl);
  clutter_group_add (CLUTTER_GROUP(stage), geglview);

  clutter_actor_show_all (CLUTTER_ACTOR(stage));

  clutter_main();

  return 1;
}
