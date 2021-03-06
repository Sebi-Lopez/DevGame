#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "Brofiler/Brofiler.h"	

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.list.count();
}

uint PathNode::FindFloorWalkableAdjacents(PathList & list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	// Tries to expand below 
	cell.create(pos.x, pos.y + 1);
	
	
	if (App->pathfinding->IsWalkable(cell))
	{
		list_to_fill.list.add(PathNode(-1, -1, cell, this));
	}
	// If it cant goes sideways
	else 
	{
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));
	}
	return list_to_fill.list.count();
}


// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	if (last_path.Count() > 0) last_path.Clear();

	if (!IsWalkable(origin) || !IsWalkable(destination))
	{
		return -1;
	}

	PathList open;
	PathList closed;
	PathNode origin_node(0, origin.DistanceTo(destination), origin, NULL);
	open.list.add(origin_node);

	while (open.list.count() > 0)
	{
		// Its the same process as a push

		p2List_item<PathNode>*	lowest_node = open.GetNodeLowestScore();

		PathNode* current_node = &closed.list.add(lowest_node->data)->data;
		open.list.del(lowest_node);	

		// Case destination is just added
	
		if (current_node->pos == destination)
		{
			const p2List_item<PathNode>* iterator = closed.list.end;
			while (iterator->data.parent != nullptr)
			{
				last_path.PushBack(iterator->data.pos);
				iterator = closed.Find(iterator->data.parent->pos);
			}
			last_path.Flip();			// Makes the path in the opposite order
			return last_path.GetCapacity();
		}

		// Calculates the neighbours nodes

		PathList adjacent;
		current_node->FindWalkableAdjacents(adjacent);

		// Iterates the neighbours nodes 

		p2List_item<PathNode>* adj_iterator = adjacent.list.start;
		for (; adj_iterator != NULL; adj_iterator = adj_iterator->next)
		{
			if (closed.Find(adj_iterator->data.pos))						// Ignores nodes in the closed list
			{
				continue;
			}

			if (open.Find(adj_iterator->data.pos) != NULL)					//If it is already in the open list, check if it is a better path(compare G)
			{
				PathNode check = open.Find(adj_iterator->data.pos)->data;
				adj_iterator->data.CalculateF(destination);
				if (adj_iterator->data.g < check.g)
				{
					check.parent = adj_iterator->data.parent;				// If it is a better path, Update the parent
				}
			}
			else															// If it is NOT found, calculate its F and add it to the open list
			{
				adj_iterator->data.CalculateF(destination);
				open.list.add(adj_iterator->data);
			}
		}
	}

	return -1;
}

int j1PathFinding::CreateFloorPath(const iPoint& origin, const iPoint& destination)
{
	if (last_path.Count() > 0) last_path.Clear();

	if (!IsWalkable(origin) || !IsWalkable(destination))
	{
		return -1;
	}

	PathList open;
	PathList closed;
	PathNode origin_node(0, origin.DistanceTo(destination), origin, NULL);
	open.list.add(origin_node);

	while (open.list.count() > 0)
	{
		// Its the same process as a push

		p2List_item<PathNode>*	lowest_node = open.GetNodeLowestScore();

		PathNode* current_node = &closed.list.add(lowest_node->data)->data;
		open.list.del(lowest_node);

		// Case destination is just added

		if (current_node->pos == destination)
		{
			const p2List_item<PathNode>* iterator = closed.list.end;
			while (iterator->data.parent != nullptr)
			{
				last_path.PushBack(iterator->data.pos);
				iterator = closed.Find(iterator->data.parent->pos);
			}
			last_path.Flip();			// Makes the path in the opposite order
			return last_path.GetCapacity();
		}

		// Calculates the neighbours nodes

		PathList adjacent;
		current_node->FindFloorWalkableAdjacents(adjacent);

		// Iterates the neighbours nodes 

		p2List_item<PathNode>* adj_iterator = adjacent.list.start;
		for (; adj_iterator != NULL; adj_iterator = adj_iterator->next)
		{
			if (closed.Find(adj_iterator->data.pos))						// Ignores nodes in the closed list
			{
				continue;
			}

			if (open.Find(adj_iterator->data.pos) != NULL)					//If it is already in the open list, check if it is a better path(compare G)
			{
				PathNode check = open.Find(adj_iterator->data.pos)->data;
				adj_iterator->data.CalculateF(destination);
				if (adj_iterator->data.g < check.g)
				{
					check.parent = adj_iterator->data.parent;				// If it is a better path, Update the parent
				}
			}
			else															// If it is NOT found, calculate its F and add it to the open list
			{
				adj_iterator->data.CalculateF(destination);
				open.list.add(adj_iterator->data);
			}
		}
	}

	return -1;
}
