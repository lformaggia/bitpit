//
// Written by Andrea Iob <andrea_iob@hotmail.com>
//
#ifndef DISABLE_OCTREE
#ifndef __PATCHMAN_PATCH_OCTREE_HPP__
#define __PATCHMAN_PATCH_OCTREE_HPP__

/*! \file */

#include "patch.hpp"

#include "Class_Para_Tree.hpp"

#include <cstddef>
#include <vector>

namespace pman {

struct OctreeLevelInfo{
    int    level;
    double h;
    double area;
    double volume;
};

class PatchOctree : public Patch {

public:
	PatchOctree(const int &id, const int &dimension, std::array<double, 3> origin,
			double length, double dh);

	~PatchOctree();

	int get_cell_octant(const int &id) const;

protected:
	void _update(const vector<uint32_t> &cellMapping);
	void _mark_for_refinement(Cell &cell);

private:
	int m_nInternalCells;
	int m_nGhostCells;

	std::unordered_map<int, int, Element::IdHasher> m_cell_to_octant;

	Class_Para_Tree<2> m_tree_2D;
	Class_Para_Tree<3> m_tree_3D;

	vector<double> m_tree_dh;
	vector<double> m_tree_area;
	vector<double> m_tree_volume;

	std::unique_ptr<double[]> m_centroids;

	std::unique_ptr<CollapsedArrayArray<double> > m_normals;

	void update_vertices();
	void import_vertices();
	void reload_vertices();

	void update_cells();
	void import_cells();
	void reload_cells();

	void update_interfaces();
	void import_interfaces();
	void reload_interfaces();
};

}

#endif
#endif