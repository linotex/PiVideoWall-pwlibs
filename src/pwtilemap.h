/*=======================================================================
 * pwlibs - Libraries used by the PiWall video wall
 * Copyright (C) 2013  Colin Hogben <colin@piwall.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *-----------------------------------------------------------------------
 *	Combine wall and tile geometry to map picture to screen
 *=======================================================================*/
#ifndef INC_pwtilemap_h
#define INC_pwtilemap_h

#include <glib.h>
#include "pwtypes.h"

typedef struct _PwTileMap PwTileMap;

extern PwTileMap *pwtilemap_create(void);
extern void pwtilemap_set_tilecode(PwTileMap *, guint /*code*/);
extern void pwtilemap_set_framesize(PwTileMap *, gdouble /*x*/, gdouble /*y*/);
extern void pwtilemap_set_auto(PwTileMap *);
extern void pwtilemap_set_role(PwTileMap *, const gchar *);
extern void pwtilemap_set_config(PwTileMap *, const gchar *);
extern void pwtilemap_set_wall(PwTileMap *, const PwRect *);
extern void pwtilemap_set_tile(PwTileMap *, const PwRect *);
extern void pwtilemap_set_orient(PwTileMap *, PwOrient);
extern void pwtilemap_set_fit(PwTileMap *, PwFit);
extern void pwtilemap_set_screen(PwTileMap *, const PwIntRect *);
extern void pwtilemap_get_tile(PwTileMap *, PwRect *);

extern gboolean pwtilemap_define(PwTileMap *, GError **);

extern gboolean pwtilemap_map_picture(PwTileMap *, const PwIntRect */*pic*/,
				      PwIntRect */*src*/, PwIntRect */*dest*/,
				      PwVcTransform *,
				      GError **);
extern void pwtilemap_add_options(PwTileMap *, GOptionContext *);
extern void pwtilemap_add_option_group(PwTileMap *, GOptionContext *);
extern void pwtilemap_free(PwTileMap *);

#endif /* INC_pwtilemap_h */
