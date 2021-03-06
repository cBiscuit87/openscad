#pragma once

#include <stddef.h>
#include <string>
#include <list>

#include "linalg.h"
#include "memory.h"

class Geometry
{
public:
  typedef std::pair<const class AbstractNode *, shared_ptr<const Geometry>> GeometryItem;
  typedef std::list<GeometryItem> Geometries;

	Geometry() : convexity(1) {}
	virtual ~Geometry() {}

	virtual size_t memsize() const = 0;
	virtual BoundingBox getBoundingBox() const = 0;
	virtual std::string dump() const = 0;
	virtual unsigned int getDimension() const = 0;
	virtual bool isEmpty() const = 0;
	virtual Geometry *copy() const = 0;
	virtual size_t numFacets() const = 0;

	unsigned int getConvexity() const { return convexity; }
	void setConvexity(int c) { this->convexity = c; }

protected:
	int convexity;
};

class GeometryList : public Geometry
{
public:
	Geometries children;

	GeometryList();
	GeometryList(const Geometry::Geometries &geometries);
	virtual ~GeometryList();

	size_t memsize() const override;
	BoundingBox getBoundingBox() const override;
	std::string dump() const override;
	unsigned int getDimension() const override;
	bool isEmpty() const override;
	Geometry *copy() const override { return new GeometryList(*this); };
	size_t numFacets() const override { assert(false && "not implemented"); return 0; };

	const Geometries &getChildren() const { 
		return this->children;
	}

	Geometries flatten() const;

};
