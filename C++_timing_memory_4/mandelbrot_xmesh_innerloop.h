#ifndef MANDELBROT_XMESH_INNERLOOP_H
#define MANDELBROT_XMESH_INNERLOOP_H

#include <omp.h>
#include "mandelbrot_xmesh.h"


class mandelbrot_xmesh_innerloop : public mandelbrot_xmesh
{
public:
	mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys);
	mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const thread_config& _thread_config);
	mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const std::string& _file_name);
	mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const thread_config& _thread_config, const std::string& _file_name);
	mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, const int& n_threads_x, const int& _n_threads_y, const std::string& _file_name);

	void calculate();
};


#endif