#ifndef MAZECREATOR_H
#define MAZECREATOR_H

#include <utility>
#include <map>
#include <string.h>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>

using namespace std;

#define MAZE_NODE(row, column) (&m_Maze[row][column])

class MazeGeneric;
class MazeNode;
class MazeHasher;
class MazeCreator;

class MazeHTML;

typedef enum MazeRenderType_e{
	MazeRenderType_NONE,
	MazeRenderType_GENERIC,
	MazeRenderType_HTML,
    MazeRenderType_SVG
}MazeRenderType;

typedef enum MazeNodeWall_e{
	MazeNodeWall_NONE,
	MazeNodeWall_NORTH,
	MazeNodeWall_EAST,
	MazeNodeWall_SOUTH,
	MazeNodeWall_WEST,
	MazeNodeWall_MAX
}MazeNodeWall;
/*
 0000
 0001
 0010
 0011
 
 0100
 0101
 0110
 0111
 
 1000
 1001
 1010
 1011
 
 1100
 1101
 1110
 1111
 */


//clock-wise existance of walls
//starting from the north wall.
//0 = no wall
//1 = wall
typedef enum MazeNodeType_e {
	MazeNodeType_0000 = 0x0,
	MazeNodeType_0001 = 0x1,
	MazeNodeType_0010 = 0x2,
	MazeNodeType_0011 = 0x3,
	MazeNodeType_0100 = 0x4,
	MazeNodeType_0101 = 0x5,
	MazeNodeType_0110 = 0x6,
	MazeNodeType_0111 = 0x7,
	MazeNodeType_1000 = 0x8,
	MazeNodeType_1001 = 0x9,
	MazeNodeType_1010 = 0xA,
	MazeNodeType_1011 = 0xB,
	MazeNodeType_1100 = 0xC,
	MazeNodeType_1101 = 0xD,
	MazeNodeType_1110 = 0xE,
	MazeNodeType_1111 = 0xF,
	MazeNodeType_Amount
} MazeNodeType;

static const char *const cMazeNodeNames[] =
{
	"0000",
	"0001",
	"0010",
	"0011",
	"0100",
	"0101",
	"0110",
	"0111",
	"1000",
	"1001",
	"1010",
	"1011",
	"1100",
	"1101",
	"1110",
	"1111"
};




class MazeCreator{
public:
	static bool CreateInstance();
	static void DestroyInstance();
	
	static MazeCreator *const GetInstance();
protected:
	static MazeCreator *sInstance;
	
public:
	MazeGeneric *CreateNew(size_t row_count, size_t column_count, const MazeRenderType type = MazeRenderType_SVG, unsigned seed = time(0));
    MazeGeneric *Duplicate(const MazeGeneric &rhs, const MazeRenderType type);
//	bool DestroyMaze(
private:
	MazeCreator();
	MazeCreator(const MazeCreator &rhs){}
	MazeCreator &operator=(const MazeCreator &rhs){return *this;}
	virtual ~MazeCreator();
};



class MazeGeneric{
protected:
	class MazeNode{
	public:
		MazeNode();
		MazeNode(const MazeNode &rhs);
		virtual ~MazeNode();
		MazeNode &operator=(const MazeNode &rhs);
		
		void Initialize(const size_t id, MazeNode * north_node, MazeNode * east_node, MazeNode * south_node, MazeNode * west_node);
		void BreakWall(const MazeNodeWall wall);
		bool IsBrokenWall(const MazeNodeWall wall)const ;
		
		void Visit(const bool visit = true);
		bool IsVisited()const ;
		
		void SetIsPartOfSolvedPath(const bool part_of_solved_path);
		bool IsPartOfSolvedPath()const ;
		
		bool operator==(const MazeNode &right)const ;
		bool operator!=(const MazeNode &right)const ;
		
		MazeNode *const GetNorthNode()const ;
		MazeNode *const GetEastNode()const ;
		MazeNode *const GetSouthNode()const ;
		MazeNode *const GetWestNode()const ;
		
		size_t GetID()const ;
		
		MazeNodeType GetType()const;
	private:
		MazeNode *m_pNorthNode;
		MazeNode *m_pEastNode;
		MazeNode *m_pSouthNode;
		MazeNode *m_pWestNode;
		
		unsigned long long int m_ID;
		
		//TODO: Make generic number of walls.
		union{
			struct{
				unsigned int has_north_wall : 1;
				unsigned int has_east_wall : 1;
				unsigned int has_south_wall : 1;
				unsigned int has_west_wall : 1;
				
				unsigned int is_visited : 1;
				
				unsigned int is_part_of_solved_path : 1;
				
				unsigned int _unused : 26;
			};
			unsigned int _data;
		};
	};
	
	typedef std::vector<MazeGeneric::MazeNode*> MazeNodeVector;
	typedef std::stack<MazeGeneric::MazeNode*> MazeNodeStack;
	
public:
	MazeGeneric();
	MazeGeneric(const MazeGeneric &rhs);
	MazeGeneric &operator=(const MazeGeneric &rhs);
	virtual ~MazeGeneric();
private:
	void Clone(const MazeGeneric &rhs);
public:
	MazeRenderType GetRenderType()const ;
	
	void CreateMaze(const size_t num_rows, const size_t num_columns, unsigned seed = time(0));
	
	const MazeNode *const GetNode(const size_t row, const size_t column)const{assert(row<m_NumRows);assert(column<m_NumColumns);return MAZE_NODE(row, column);}
	size_t GetNumRows()const{return m_NumRows;}
	size_t GetNumColumns()const{return m_NumColumns;}
	virtual void Draw() {}
    virtual void Save() {}
	
	void SolveMaze();
	void UnSolveMaze();
    float GetDifficulty()const {return mDifficulty;}
protected:
	MazeRenderType m_RenderType;
	
	size_t m_NumColumns;
	size_t m_NumRows;
	
	MazeNode **m_Maze;
	MazeNodeStack *m_MazeNodeStack;
	
	size_t m_BeginningID;
	size_t m_EndID;
	bool m_IsFoundSolution;
    float mDifficulty;
private:
	void CarveMaze(MazeNode *node);
    void CarveMaze();
	void SolveMaze(MazeNode *node);
	/*
	 TODO: will need to make another class for walls, specifically so that the walls know which are directly next to eachother.
	 */
	void KnockDownWall(MazeNode *node1, MazeNode *node2);
	void AdjacentNodes(MazeNode *root_node, MazeNodeVector &maze_vector);
	void AdjacentNodesTraversable(MazeNode *root_node, MazeNodeVector &maze_vector);
};

class MazeHTML : MazeGeneric{
public:
	MazeHTML();
    MazeHTML(const MazeGeneric &rhs):MazeGeneric(rhs){}
	virtual ~MazeHTML();
	
	void Draw();
    void Save();
};

class MazeSVG : MazeGeneric{
public:
    MazeSVG();
    MazeSVG(const MazeGeneric &rhs):MazeGeneric(rhs){}
    virtual ~MazeSVG();
    
    void Draw();
    void Save();
private:
    string GetNorth(int x, int y, int dim)const;
    string GetEast(int x, int y, int dim)const;
    string GetSouth(int x, int y, int dim)const;
    string GetWest(int x, int y, int dim)const;
    string GetDot(int x, int y, int dim)const;
    string DrawCell(MazeNode *node, int x, int y, int dim, bool isStart, bool isEnd);
};
#endif
