/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_instruct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:25:56 by mnaimi            #+#    #+#             */
/*   Updated: 2022/01/16 15:25:58 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/* -------------------------------------------------------------------------- */

static void	assign_cl(t_vars *vars)
{
	vars->linedraw.cl0 = \
		vars->matrix.matrix_ptr[vars->linedraw.y0][vars->linedraw.x0][1];
	vars->linedraw.cl1 = \
		vars->matrix.matrix_ptr[vars->linedraw.y1][vars->linedraw.x1][1];
	if (vars->linedraw.cl0 > vars->linedraw.cl1)
		vars->linedraw.cl = vars->linedraw.cl0;
	else
		vars->linedraw.cl = vars->linedraw.cl1;
}

/* -------------------------------------------------------------------------- */

static void	assign_z(t_vars *vars)
{
	vars->linedraw.z0 = \
		vars->matrix.matrix_ptr[vars->linedraw.y0][vars->linedraw.x0][0];
	vars->linedraw.z1 = \
		vars->matrix.matrix_ptr[vars->linedraw.y1][vars->linedraw.x1][0];
}

/* -------------------------------------------------------------------------- */

static void	assign_y_z_cl_ndraw(t_vars *vars, int y0, int y1)
{
	vars->linedraw.y0 = y0;
	vars->linedraw.y1 = y1;
	assign_z(vars);
	assign_cl(vars);
	drawline_calcul(vars);
}

/* -------------------------------------------------------------------------- */

static void	assign_x(t_vars *vars, int x0, int x1)
{
	vars->linedraw.x0 = x0;
	vars->linedraw.x1 = x1;
}

/* -------------------------------------------------------------------------- */

void	draw_map(t_vars	*vars)
{
	vars->loop.y = 0;
	while (vars->loop.y < vars->matrix.max_y - 1)
	{
		vars->loop.x = 0;
		while (vars->loop.x < vars->matrix.max_x - 1)
		{
			assign_x(vars, vars->loop.x, vars->loop.x + 1);
			assign_y_z_cl_ndraw(vars, vars->loop.y, vars->loop.y);
			assign_x(vars, vars->loop.x, vars->loop.x);
			assign_y_z_cl_ndraw(vars, vars->loop.y, vars->loop.y + 1);
			if (vars->loop.x == vars->matrix.max_x - 2)
			{
				assign_x(vars, vars->loop.x + 1, vars->loop.x + 1);
				assign_y_z_cl_ndraw(vars, vars->loop.y, vars->loop.y + 1);
			}
			if (vars->loop.y == vars->matrix.max_y - 2)
			{
				assign_x(vars, vars->loop.x, vars->loop.x + 1);
				assign_y_z_cl_ndraw(vars, vars->loop.y + 1, vars->loop.y + 1);
			}
			vars->loop.x++;
		}
		vars->loop.y++;
	}
}

/* -------------------------------------------------------------------------- */
