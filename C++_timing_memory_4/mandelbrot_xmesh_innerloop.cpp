#include "mandelbrot_xmesh_innerloop.h"

mandelbrot_xmesh_innerloop::mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys) :
	mandelbrot_xmesh(_allocation_mode,_bnds,_n_xs,_n_ys)
{}
mandelbrot_xmesh_innerloop::mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys,
	const thread_config& _thread_config) :
	mandelbrot_xmesh(_allocation_mode, _bnds, _n_xs, _n_ys, _thread_config)
{}
mandelbrot_xmesh_innerloop::mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys, 
	const std::string& _file_name) :
	mandelbrot_xmesh(_allocation_mode,_bnds,_n_xs,_n_ys,_file_name)
{}
mandelbrot_xmesh_innerloop::mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys,
	const thread_config& _thread_config, const std::string& _file_name):
	mandelbrot_xmesh(_allocation_mode,_bnds,_n_xs,_n_ys,_thread_config,_file_name)
{}
mandelbrot_xmesh_innerloop::mandelbrot_xmesh_innerloop(const int& _allocation_mode, const bounds& _bnds, const int& _n_xs, const int& _n_ys,
	const int& _n_threads_x, const int& _n_threads_y, const std::string& _file_name) :
	mandelbrot_xmesh(_allocation_mode, _bnds, _n_xs, _n_ys, _n_threads_x, _n_threads_y, _file_name)
{}


void mandelbrot_xmesh_innerloop::calculate()

{
	double ara = 0.0;
#pragma omp parallel reduction(+:ara) // default(none) shared(n_xs,x_min,x_max,y_min,y_max,y_size,num_iterations,X,first_range,last_range,size_per_thread)
	{
		int thread_id = omp_get_thread_num();
		if (thread_id == 0)
			std::cout << "Using " << omp_get_num_threads() << " omp threads" << std::endl;
		int first = first_range[thread_id];
		int last = last_range[thread_id];

		for (int j = 0; j < n_ys; j++)
		{
			for (int i = first; i < last; i++)
			{
				complex min(static_cast<double> (this->x_min), static_cast<double> (this->y_min));
				double _i = static_cast<double> (i % this->n_xs);
				double _j = static_cast<double> (j);
				_i = static_cast<double> ((_i + this->n_xs / 2.0) / 2.0);
				_j = static_cast<double> ((_j + this->n_ys / 2.0) / 2.0);

				complex delta((double)(_i * (this->x_max - this->x_min) / (this->n_xs - 1)), (double)(_j * (this->y_max - this->y_min) / (this->n_ys - 1)));
				complex c = min + delta;
				complex z(0.0);


				int k = 0;
				for (k = 0; k < this->num_iterations; k++)
				{
					z = z * z + c;
					if (z.abs_complex() > 2.0) break;
				}
				if (k == this->num_iterations)
				{
					ara++;
				}
				(*(this->img))(i, j) = static_cast<double>(k) / static_cast<double>(this->num_iterations);
			}
		}
	}
	area = ara;
	for (int k = 0; k < n_threads_x; k++)
		for (int i = first_range[k]; i < last_range[k]; i++)
			for (int j = 0; j < n_ys; j++)
				(*(this->img))(i - k * this->n_xs, j) = (*(this->img))(i, j);
}