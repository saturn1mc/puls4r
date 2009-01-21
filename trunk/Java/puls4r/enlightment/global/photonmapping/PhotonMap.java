package puls4r.enlightment.global.photonmapping;

import java.util.Vector;

public final class PhotonMap {
	private Vector<Photon> photons;

	private int stored_photons;
	private int half_stored_photons;
	private int max_photons;
	private int prev_scale;

	private float costheta[] = new float[256];
	private float sintheta[] = new float[256];
	private float cosphi[] = new float[256];
	private float sinphi[] = new float[256];

	private float bbox_min[] = new float[3]; // use bbox_min;
	private float bbox_max[] = new float[3]; // use bbox_max;

	public PhotonMap(int max_photons) {
		this.max_photons = max_photons;
		this.stored_photons = 0;
		this.prev_scale = 1;

		this.photons = new Vector<Photon>(max_photons + 1);

		this.bbox_min[0] = this.bbox_min[1] = this.bbox_min[2] = Float.POSITIVE_INFINITY;
		this.bbox_max[0] = this.bbox_max[1] = this.bbox_max[2] = Float.NEGATIVE_INFINITY;

		for (int i = 0; i < 256; i++) {
			double angle = (double) i * (1.0 / 256.0) * Math.PI;
			this.costheta[i] = (float) Math.cos(angle);
			this.sintheta[i] = (float) Math.sin(angle);
			this.cosphi[i] = (float) Math.cos(2.0 * angle);
			this.sinphi[i] = (float) Math.sin(2.0 * angle);
		}
	}

	private void photon_dir(float dir[], Photon p) {
		dir[0] = sintheta[p.theta] * cosphi[p.phi];
		dir[1] = sintheta[p.theta] * sinphi[p.phi];
		dir[2] = costheta[p.theta];
	}

	public void irradiance_estimate(float irrad[], float pos[], float normal[], float max_dist, int nphotons) {

		irrad[0] = irrad[1] = irrad[2] = 0.0f;

		NearestPhotons np = new NearestPhotons();
		np.dist2 = new float[nphotons + 1];
		np.index = new Photon[nphotons + 1];

		np.pos[0] = pos[0];
		np.pos[1] = pos[1];
		np.pos[2] = pos[2];
		np.max = nphotons;
		np.found = 0;
		np.got_heap = 0;
		np.dist2[0] = max_dist * max_dist;

		// locate the nearest photons
		locate_photons(np, 1);

		// if less than 8 photons return
		if (np.found < 8)
			return;

		float pdir[] = new float[3];

		// sum irradiance from all photons
		for (int i = 1; i <= np.found; i++) {
			Photon p = np.index[i];
			// the photon_dir call and following if can be omitted (for speed)
			// if the scene does not have any thin surfaces
			photon_dir(pdir, p);
			if ((pdir[0] * normal[0] + pdir[1] * normal[1] + pdir[2] * normal[2]) < 0.0f) {
				irrad[0] += p.power[0];
				irrad[1] += p.power[1];
				irrad[2] += p.power[2];
			}
		}

		float tmp = (float) ((1.0f / Math.PI) / (np.dist2[0])); // estimate of
		// density

		irrad[0] *= tmp;
		irrad[1] *= tmp;
		irrad[2] *= tmp;
	}

	private void locate_photons(NearestPhotons np, int index) {

		Photon p = photons.elementAt(index);
		float dist1;

		if (index < half_stored_photons) {
			dist1 = np.pos[p.plane] - p.pos[p.plane];

			if (dist1 > 0.0) { // if dist1 is positive search right plane
				locate_photons(np, 2 * index + 1);
				if (dist1 * dist1 < np.dist2[0])
					locate_photons(np, 2 * index);
			} else { // dist1 is negative search left first
				locate_photons(np, 2 * index);
				if (dist1 * dist1 < np.dist2[0])
					locate_photons(np, 2 * index + 1);
			}
		}

		// compute squared distance between current photon and np.pos

		dist1 = p.pos[0] - np.pos[0];
		float dist2 = dist1 * dist1;
		dist1 = p.pos[1] - np.pos[1];
		dist2 += dist1 * dist1;
		dist1 = p.pos[2] - np.pos[2];
		dist2 += dist1 * dist1;

		if (dist2 < np.dist2[0]) {
			// we found a photon :) Insert it in the candidate list

			if (np.found < np.max) {
				// heap is not full; use array
				np.found++;
				np.dist2[np.found] = dist2;
				np.index[np.found] = p;
			} else {
				int j, parent;

				if (np.got_heap == 0) { // Do we need to build the heap?
					// Build heap
					float dst2;
					Photon phot;
					int half_found = np.found >> 1;
					for (int k = half_found; k >= 1; k--) {
						parent = k;
						phot = np.index[k];
						dst2 = np.dist2[k];
						while (parent <= half_found) {
							j = parent + parent;
							if (j < np.found && np.dist2[j] < np.dist2[j + 1])
								j++;
							if (dst2 >= np.dist2[j])
								break;
							np.dist2[parent] = np.dist2[j];
							np.index[parent] = np.index[j];
							parent = j;
						}
						np.dist2[parent] = dst2;
						np.index[parent] = phot;
					}
					np.got_heap = 1;
				}

				// insert new photon into max heap
				// delete largest element, insert new and reorder the heap

				parent = 1;
				j = 2;
				while (j <= np.found) {
					if (j < np.found && np.dist2[j] < np.dist2[j + 1])
						j++;
					if (dist2 > np.dist2[j])
						break;
					np.dist2[parent] = np.dist2[j];
					np.index[parent] = np.index[j];
					parent = j;
					j += j;
				}
				np.index[parent] = p;
				np.dist2[parent] = dist2;

				np.dist2[0] = np.dist2[1];
			}
		}
	}

	public void store(float power[], float pos[], float dir[]) {
		if (stored_photons >= max_photons)
			return;

		stored_photons++;
		Photon node = photons.elementAt(stored_photons);

		for (int i = 0; i < 3; i++) {
			node.pos[i] = pos[i];

			if (node.pos[i] < bbox_min[i])
				bbox_min[i] = node.pos[i];
			if (node.pos[i] > bbox_max[i])
				bbox_max[i] = node.pos[i];

			node.power[i] = power[i];
		}

		int theta = (int) (Math.acos(dir[2]) * (256.0 / Math.PI));
		if (theta > 255)
			node.theta = (byte) 255;
		else
			node.theta = (byte) theta;

		int phi = (int) (Math.atan2(dir[1], dir[0]) * (256.0 / (2.0 * Math.PI)));
		if (phi > 255)
			node.phi = (byte) 255;
		else if (phi < 0)
			node.phi = (byte) (phi + 256);
		else
			node.phi = (byte) phi;
	}

	public void scale_photon_power(float scale) {
		for (int i = prev_scale; i <= stored_photons; i++) {
			photons.elementAt(i).power[0] *= scale;
			photons.elementAt(i).power[1] *= scale;
			photons.elementAt(i).power[2] *= scale;
		}
		prev_scale = stored_photons;
	}

	public void balance() {
		if (stored_photons > 1) {
			// allocate two temporary arrays for the balancing procedure
			Photon pa1[] = new Photon[stored_photons + 1];
			Photon pa2[] = new Photon[stored_photons + 1];

			for (int i = 0; i <= stored_photons; i++)
				pa2[i] = photons.elementAt(i);

			balance_segment(pa1, pa2, 1, 1, stored_photons);

			// reorganize balanced kd-tree (make a heap)
			int d, j = 1, foo = 1;
			Photon foo_photon = photons.elementAt(j);

			for (int i = 1; i <= stored_photons; i++) {

				// d=pa1[j]-photons; POSITION DE PA1[J] DANS PHOTONS
				d = photons.indexOf(pa1[j]);
				pa1[j] = null;

				if (d != foo)
					//TODO
					photons[j] = photons[d];
					//
				else {
					photons.remove(j);
					photons.add(j,foo_photon);

					if (i < stored_photons) {
						for (; foo <= stored_photons; foo++)
							if (pa1[foo] != null)
								break;
						foo_photon = photons.elementAt(foo);
						j = foo;
					}
					continue;
				}
				j = d;
			}
		}

		half_stored_photons = stored_photons / 2 - 1;
	}

	private void swap(Photon ph[], int a, int b) {
		Photon ph2 = ph[a];
		ph[a] = ph[b];
		ph[b] = ph2;
	}

	private void median_split(Photon p[], int start, int end, int median, int axis) {
		int left = start;
		int right = end;

		while (right > left) {
			float v = p[right].pos[axis];
			int i = left - 1;
			int j = right;
			for (;;) {
				while (p[++i].pos[axis] < v)
					;
				while (p[--j].pos[axis] > v && j > left)
					;
				if (i >= j)
					break;
				swap(p, i, j);
			}

			swap(p, i, right);
			if (i >= median)
				right = i - 1;
			if (i <= median)
				left = i + 1;
		}
	}

	private void balance_segment(Photon pbal[], Photon porg[], int index, int start, int end) {
		// --------------------
		// compute new median
		// --------------------

		int median = 1;
		while ((4 * median) <= (end - start + 1))
			median += median;

		if ((3 * median) <= (end - start + 1)) {
			median += median;
			median += start - 1;
		} else
			median = end - median + 1;

		// --------------------------
		// find axis to split along
		// --------------------------

		int axis = 2;
		if ((bbox_max[0] - bbox_min[0]) > (bbox_max[1] - bbox_min[1]) && (bbox_max[0] - bbox_min[0]) > (bbox_max[2] - bbox_min[2]))
			axis = 0;
		else if ((bbox_max[1] - bbox_min[1]) > (bbox_max[2] - bbox_min[2]))
			axis = 1;

		// ------------------------------------------
		// partition photon block around the median
		// ------------------------------------------

		median_split(porg, start, end, median, axis);

		pbal[index] = porg[median];
		pbal[index].plane = (short) axis;

		// ----------------------------------------------
		// recursively balance the left and right block
		// ----------------------------------------------

		if (median > start) {
			// balance left segment
			if (start < median - 1) {
				float tmp = bbox_max[axis];
				bbox_max[axis] = pbal[index].pos[axis];
				balance_segment(pbal, porg, 2 * index, start, median - 1);
				bbox_max[axis] = tmp;
			} else {
				pbal[2 * index] = porg[start];
			}
		}

		if (median < end) {
			// balance right segment
			if (median + 1 < end) {
				float tmp = bbox_min[axis];
				bbox_min[axis] = pbal[index].pos[axis];
				balance_segment(pbal, porg, 2 * index + 1, median + 1, end);
				bbox_min[axis] = tmp;
			} else {
				pbal[2 * index + 1] = porg[end];
			}
		}
	}
}