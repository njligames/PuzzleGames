#include "MazeCreator.hpp"
#include <random>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
//#define MAZE_NODE(row, column) ((*m_MazeConstruct)[Index2D(row, column)])

MazeCreator *MazeCreator::sInstance = 0;

bool MazeCreator::CreateInstance(){
	if(sInstance != NULL){
		delete sInstance;
		sInstance = NULL;
	}
	sInstance = new MazeCreator();
	return (sInstance != NULL);
}
void MazeCreator::DestroyInstance(){
	if(sInstance != NULL){
		delete sInstance;
		sInstance = NULL;
	}
}

MazeCreator *const MazeCreator::GetInstance(){
	return sInstance;
}

MazeGeneric *MazeCreator::CreateNew(size_t row_count, size_t column_count, const MazeRenderType type, unsigned seed){
	MazeGeneric *ret = NULL;
	
	switch (type) {
		case MazeRenderType_HTML:
			ret = (MazeGeneric*)(new MazeHTML());
			break;
        case MazeRenderType_SVG:
            ret = (MazeGeneric*)(new MazeSVG());
            break;
		default:
			ret = new MazeGeneric();
			break;
	}
	
	ret->CreateMaze(row_count, column_count, seed);
	
	return ret;
}
MazeGeneric *MazeCreator::Duplicate(const MazeGeneric &rhs, const MazeRenderType type) {
    MazeGeneric *ret = NULL;
    
    switch (type) {
        case MazeRenderType_HTML:
            ret = (MazeGeneric*)(new MazeHTML(rhs));
            break;
        case MazeRenderType_SVG:
            ret = (MazeGeneric*)(new MazeSVG(rhs));
            break;
        default:
            ret = new MazeGeneric();
            break;
    }
    
    return ret;
}
MazeCreator::MazeCreator(void){
}
MazeCreator::~MazeCreator(void){
}



MazeGeneric::MazeNode::MazeNode() :
	_data(0),
	m_pNorthNode(NULL),
	m_pEastNode(NULL),
	m_pSouthNode(NULL),
	m_pWestNode(NULL),
	m_ID(0)
{
	has_north_wall = 1;
	has_east_wall = 1;
	has_south_wall = 1;
	has_west_wall = 1;
	
	is_visited = 0;
}
MazeGeneric::MazeNode::MazeNode(const MazeNode &rhs) :
	_data(rhs._data),
	m_pNorthNode(rhs.m_pNorthNode),
	m_pEastNode(rhs.m_pEastNode),
	m_pSouthNode(rhs.m_pSouthNode),
	m_pWestNode(rhs.m_pWestNode),
	m_ID(rhs.m_ID)
{
}

MazeGeneric::MazeNode::~MazeNode(){
	m_pNorthNode = NULL;
	m_pEastNode = NULL;
	m_pSouthNode = NULL;
	m_pWestNode = NULL;
}
MazeGeneric::MazeNode &MazeGeneric::MazeNode::operator=(const MazeGeneric::MazeNode &rhs){
	if(this != &rhs){
		_data = rhs._data;
		m_pNorthNode = rhs.m_pNorthNode;
		m_pEastNode = rhs.m_pEastNode;
		m_pSouthNode = rhs.m_pSouthNode;
		m_pWestNode = rhs.m_pWestNode;
		m_ID = rhs.m_ID;
	}
	return *this;
}
void MazeGeneric::MazeNode::Initialize(const size_t id, 
									  MazeGeneric::MazeNode * north_node,
									  MazeGeneric::MazeNode * east_node, 
									  MazeGeneric::MazeNode * south_node, 
									  MazeGeneric::MazeNode * west_node){
	m_ID = id;
	
	m_pNorthNode = north_node;
	m_pEastNode = east_node;
	m_pSouthNode = south_node;
	m_pWestNode = west_node;
}
void MazeGeneric::MazeNode::BreakWall(const MazeNodeWall wall){
	switch (wall) {
		case MazeNodeWall_NORTH:
			has_north_wall = 0;
			break;
		case MazeNodeWall_EAST:
			has_east_wall = 0;
			break;
		case MazeNodeWall_SOUTH:
			has_south_wall = 0;
			break;
		case MazeNodeWall_WEST:
			has_west_wall = 0;
			break;
		default:
			break;
	}
}
bool MazeGeneric::MazeNode::IsBrokenWall(const MazeNodeWall wall)const {
	switch (wall) {
		case MazeNodeWall_NORTH:
			return (has_north_wall == 0);
		case MazeNodeWall_EAST:
			return (has_east_wall == 0);
		case MazeNodeWall_SOUTH:
			return (has_south_wall == 0);
		case MazeNodeWall_WEST:
			return (has_west_wall == 0);
	}
	return false;
}
void MazeGeneric::MazeNode::Visit(const bool visit){
	if(visit)
		is_visited = 1;
	else
		is_visited = 0;
}
bool MazeGeneric::MazeNode::IsVisited()const {
	return (is_visited == 1);
}
void MazeGeneric::MazeNode::SetIsPartOfSolvedPath(const bool part_of_solved_path){
	if(part_of_solved_path){
		this->is_part_of_solved_path = 1;
	}else{
		this->is_part_of_solved_path = 0;
	}
}
bool MazeGeneric::MazeNode::IsPartOfSolvedPath()const {
	return (is_part_of_solved_path == 1);
}
bool MazeGeneric::MazeNode::operator==(const MazeNode &right)const {
	return (m_ID == right.m_ID);
}
bool MazeGeneric::MazeNode::operator!=(const MazeNode &right)const {
	return !(*this == right);
}
MazeGeneric::MazeNode *const MazeGeneric::MazeNode::GetNorthNode()const {
	return m_pNorthNode;
}
MazeGeneric::MazeNode *const MazeGeneric::MazeNode::GetEastNode()const {
	return m_pEastNode;
}
MazeGeneric::MazeNode *const MazeGeneric::MazeNode::GetSouthNode()const {
	return m_pSouthNode;
}
MazeGeneric::MazeNode *const MazeGeneric::MazeNode::GetWestNode()const {
	return m_pWestNode;
}

size_t MazeGeneric::MazeNode::GetID()const {
	return m_ID;
}

MazeNodeType MazeGeneric::MazeNode::GetType()const
{
	int nnode, enode, snode, wnode;
	nnode = (int)!this->IsBrokenWall(MazeNodeWall_NORTH);
	enode = (int)!this->IsBrokenWall(MazeNodeWall_EAST);
	snode = (int)!this->IsBrokenWall(MazeNodeWall_SOUTH);
	wnode = (int)!this->IsBrokenWall(MazeNodeWall_WEST);
	return ((MazeNodeType)( (nnode<<3) | (enode<<2) | (snode<<1) | (wnode<<0) ));
}

MazeGeneric::MazeGeneric() :
	m_RenderType(MazeRenderType_NONE),
	m_NumColumns(0),
	m_NumRows(0),
	m_Maze(NULL),
	m_MazeNodeStack(new MazeNodeStack()),
	m_BeginningID(0),
	m_EndID(0),
	m_IsFoundSolution(false)
{
}
MazeGeneric::MazeGeneric(const MazeGeneric &rhs) :
	m_RenderType(rhs.m_RenderType),
	m_NumColumns(rhs.m_NumColumns),
	m_NumRows(rhs.m_NumRows),
	m_Maze(NULL),
	m_MazeNodeStack(new MazeNodeStack()),
	m_BeginningID(rhs.m_BeginningID),
	m_EndID(rhs.m_EndID),
	m_IsFoundSolution(rhs.m_IsFoundSolution)
{
	if(rhs.m_Maze){
		m_NumRows = rhs.m_NumRows;
		m_NumColumns = rhs.m_NumColumns;
		
		m_Maze = new MazeNode*[m_NumRows];
		for(size_t i = 0; i < m_NumRows; i++)
			m_Maze[i] = new MazeNode[m_NumColumns];
	}
	
	this->Clone(rhs);
}
MazeGeneric &MazeGeneric::operator=(const MazeGeneric &rhs){
	if(this != &rhs){
		if(m_Maze != NULL){
			for(size_t i = 0; i < m_NumRows; i++)
				delete [] m_Maze[i];
			delete [] m_Maze;
		}
		delete m_MazeNodeStack;
		
		m_Maze = new MazeNode*[m_NumRows];
		for(size_t i = 0; i < m_NumRows; i++)
			m_Maze[i] = new MazeNode[m_NumColumns];
		m_MazeNodeStack = new MazeNodeStack();
		
		this->Clone(rhs);
	}
	return *this;
}

MazeGeneric::~MazeGeneric(){
	if(m_Maze != NULL){
		for(size_t i = 0; i < m_NumRows; i++)
			delete [] m_Maze[i];
		delete [] m_Maze;
	}
	delete m_MazeNodeStack;
}
void MazeGeneric::Clone(const MazeGeneric &rhs){
	//the stack needs to be empty to copy this object.
	assert(rhs.m_MazeNodeStack->empty());
	
	for(int row = 0; row < rhs.m_NumRows; row++){
		for(int column = 0; column < rhs.m_NumColumns; column++){
			m_Maze[row][column] = rhs.m_Maze[row][column];
		}
	}
	
	m_RenderType = rhs.m_RenderType;
	m_NumColumns = rhs.m_NumColumns;
	m_NumRows = rhs.m_NumRows;
	m_BeginningID = rhs.m_BeginningID;
	m_EndID = rhs.m_EndID;
	m_IsFoundSolution = rhs.m_IsFoundSolution;
}

MazeRenderType MazeGeneric::GetRenderType()const {
	return m_RenderType;
}

void MazeGeneric::CreateMaze(const size_t num_rows, const size_t num_columns, unsigned seed){
	if(num_rows == 0 || num_columns == 0)
		return;
	
	assert(num_rows);
	assert(num_columns);
	
	std::srand(seed);
	
	size_t id = 0;
//	size_t start_row;
//	size_t start_column;
	
	if(m_Maze != NULL){
		for(size_t i = 0; i < m_NumRows; i++)
			delete [] m_Maze[i];
		delete [] m_Maze;
	}
	
	m_NumRows = num_rows;
	m_NumColumns = num_columns;
	
	m_Maze = new MazeNode*[m_NumRows];
	for(size_t i = 0; i < m_NumRows; i++)
		m_Maze[i] = new MazeNode[m_NumColumns];
	
	assert(m_Maze);
	
	for(int row = 0; row < m_NumRows; row++){
		for(int column = 0; column < m_NumColumns; column++){
			MAZE_NODE(row, column)->Initialize(id++, 
											   ((row - 1) >= 0)?MAZE_NODE(row - 1, column):NULL,
											   ((column + 1) < m_NumColumns)?MAZE_NODE(row, column + 1):NULL,
											   ((row + 1) < m_NumRows)?MAZE_NODE(row + 1, column):NULL,
											   ((column - 1) >= 0)?MAZE_NODE(row, column - 1):NULL);
		}
	}
	
//	start_row = (size_t)rand() % m_NumRows;
//	start_column = (size_t)rand() % m_NumColumns;
//	CarveMaze(MAZE_NODE(start_row, start_column));
    
    CarveMaze();
	
	//MAZE_NODE(0, 0)->BreakWall(MazeNodeWall_NORTH);
	//MAZE_NODE(m_NumRows - 1, m_NumColumns - 1)->BreakWall(MazeNodeWall_SOUTH);
	
	m_BeginningID = MAZE_NODE(0, 0)->GetID();
	m_EndID = MAZE_NODE(m_NumRows - 1, m_NumColumns - 1)->GetID();
    
    mDifficulty = 0;
}

void MazeGeneric::SolveMaze(){
	assert(m_Maze);
	
	MazeNode *node_current = NULL;
    MazeNode *node_next = NULL;
	
	m_IsFoundSolution = false;
	
	for(int row = 0; row < m_NumRows; row++){
		for(int column = 0; column < m_NumColumns; column++){
			MAZE_NODE(row, column)->Visit(false);
			if(MAZE_NODE(row, column)->GetID() == m_BeginningID){
                node_current = MAZE_NODE(row, column);
			}
		}
	}
//	SolveMaze(start_node);
    
    while(NULL != node_current) {
        MazeNodeVector mazenode_vector;
        

        node_current->Visit();
        node_current->SetIsPartOfSolvedPath(true);

        if((node_current->GetID() == m_EndID) || m_IsFoundSolution){
            m_IsFoundSolution = true;
            node_current = NULL;
        } else {
            

            AdjacentNodesTraversable(node_current, mazenode_vector);

            if(mazenode_vector.size() > 0){
                m_MazeNodeStack->push(node_current);

                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(mazenode_vector.begin(), mazenode_vector.end(), g);

                node_next = mazenode_vector.at(0);

    //            SolveMaze(node_next);
                node_current = node_next;
            }else{
                node_current->SetIsPartOfSolvedPath(false);

                if(m_MazeNodeStack->size() > 0){
                    node_next = m_MazeNodeStack->top();

                    m_MazeNodeStack->pop();
    //                SolveMaze(node_next);
                    node_current = node_next;
                } else {
                    node_current = NULL;
                }
            }
        }
    }
    
    float total_cells_in_solution(0);
    for(int row = 0; row < m_NumRows; row++){
        for(int column = 0; column < m_NumColumns; column++){
            if(MAZE_NODE(row, column)->IsPartOfSolvedPath()) {
                total_cells_in_solution++;
            }
        }
    }
    
    double size(m_NumRows * m_NumColumns);
    double r(m_NumRows), c(m_NumColumns);
    double base = sqrt((r * r) + (c * c));
    base = (base/((r * c))) * size;
    
    double numerator(total_cells_in_solution - base);
    double denominator(size - base);
    
    mDifficulty = numerator / denominator;
}
void MazeGeneric::UnSolveMaze(){
	assert(m_Maze);
	
	for(int row = 0; row < m_NumRows; row++){
		for(int column = 0; column < m_NumColumns; column++){
			MAZE_NODE(row, column)->SetIsPartOfSolvedPath(false);
		}
	}
		
}

void MazeGeneric::CarveMaze(MazeGeneric::MazeNode *node_current){
	assert(m_Maze);
	
	/*
	 The depth-first search algorithm of maze generation is frequently implemented using backtracking:
	 Mark the current cell as 'Visited'
	 If the current cell has any neighbours which have not been visited
		Choose randomly one of the unvisited neighbours
		add the current cell to the stack
		remove the wall between the current cell and the chosen cell
		Make the chosen cell the current cell
		Recursively call this function
	 else
		remove the last current cell from the stack
		Backtrack to the previous execution of this function
	 */
	
	MazeNodeVector mazenode_vector;
	MazeGeneric::MazeNode *node_next = NULL;
	
	node_current->Visit();
	
	AdjacentNodes(node_current, mazenode_vector);
	
	if(mazenode_vector.size() > 0){
		m_MazeNodeStack->push(node_current);
		
        std::random_device rd;
        std::mt19937 g(rd());
		std::shuffle(mazenode_vector.begin(), mazenode_vector.end(), g);
		
		node_next = mazenode_vector.at(0);
		KnockDownWall(node_current, node_next);
		CarveMaze(node_next);
	}else{
		if(m_MazeNodeStack->size() > 0){
			node_next = m_MazeNodeStack->top();
			m_MazeNodeStack->pop();
			CarveMaze(node_next);
		}
	}
}

void MazeGeneric::CarveMaze() {
    size_t start_row;
    size_t start_column;
    start_row = (size_t)rand() % m_NumRows;
    start_column = (size_t)rand() % m_NumColumns;
    MazeGeneric::MazeNode *node_current = MAZE_NODE(start_row, start_column);
    MazeGeneric::MazeNode *node_next = NULL;
    while(NULL != node_current) {
        MazeNodeVector mazenode_vector;
        node_current->Visit();
        AdjacentNodes(node_current, mazenode_vector);
        if(mazenode_vector.size() > 0){
            m_MazeNodeStack->push(node_current);
            
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(mazenode_vector.begin(), mazenode_vector.end(), g);
            
            node_next = mazenode_vector.at(0);
            KnockDownWall(node_current, node_next);
//            CarveMaze(node_next);
            node_current = node_next;
        }else{
            if(m_MazeNodeStack->size() > 0){
                node_next = m_MazeNodeStack->top();
                m_MazeNodeStack->pop();
//                CarveMaze(node_next);
                node_current = node_next;
            } else {
                node_current = NULL;
            }
        }
    }
    
}

void MazeGeneric::SolveMaze(MazeNode *node_current){
	assert(m_Maze);
	
	MazeNodeVector mazenode_vector;
	MazeNode *node_next = NULL;
	
	node_current->Visit();
	node_current->SetIsPartOfSolvedPath(true);
	
	if(node_current->GetID() == m_EndID || m_IsFoundSolution){
		m_IsFoundSolution = true;
		return;
	}
	
	AdjacentNodesTraversable(node_current, mazenode_vector);
	
	if(mazenode_vector.size() > 0){
		m_MazeNodeStack->push(node_current);
		
        std::random_device rd;
        std::mt19937 g(rd());
		std::shuffle(mazenode_vector.begin(), mazenode_vector.end(), g);
		
		node_next = mazenode_vector.at(0);
		
		SolveMaze(node_next);
	}else{
		node_current->SetIsPartOfSolvedPath(false);
		
		if(m_MazeNodeStack->size() > 0){
			node_next = m_MazeNodeStack->top();
			
			m_MazeNodeStack->pop();
			SolveMaze(node_next);
		}
	}
}

void MazeGeneric::KnockDownWall(MazeNode *node1, MazeNode *node2){
	assert(m_Maze);
	
	if(node1->GetEastNode() != NULL){
		if(*(node1->GetEastNode()) == *(node2)){
			node1->BreakWall(MazeNodeWall_EAST);
			node2->BreakWall(MazeNodeWall_WEST);
		}
	}
	if(node1->GetWestNode() != NULL){
		if(*(node1->GetWestNode()) == *(node2)){
			node1->BreakWall(MazeNodeWall_WEST);
			node2->BreakWall(MazeNodeWall_EAST);
		}
	}
	if(node1->GetNorthNode() != NULL){
		if(*(node1->GetNorthNode()) == *(node2)){
			node1->BreakWall(MazeNodeWall_NORTH);
			node2->BreakWall(MazeNodeWall_SOUTH);
		}
	}
	if(node1->GetSouthNode() != NULL){
		if(*(node1->GetSouthNode()) == *(node2)){
			node1->BreakWall(MazeNodeWall_SOUTH);
			node2->BreakWall(MazeNodeWall_NORTH);
		}
	}
}
void MazeGeneric::AdjacentNodes(MazeNode *root_node, MazeNodeVector &maze_vector){
	assert(m_Maze);
	
	maze_vector.clear();
	
	if(root_node->GetNorthNode() != NULL)
		if(!root_node->GetNorthNode()->IsVisited())
			maze_vector.push_back(root_node->GetNorthNode());
	
	if(root_node->GetSouthNode() != NULL)
		if(!root_node->GetSouthNode()->IsVisited())
			maze_vector.push_back(root_node->GetSouthNode());
	
	if(root_node->GetEastNode() != NULL)
		if(!root_node->GetEastNode()->IsVisited())
			maze_vector.push_back(root_node->GetEastNode());
	
	if(root_node->GetWestNode() != NULL)
		if(!root_node->GetWestNode()->IsVisited())
			maze_vector.push_back(root_node->GetWestNode());
}

void MazeGeneric::AdjacentNodesTraversable(MazeNode *root_node, MazeNodeVector &maze_vector){
	assert(m_Maze);
	
	maze_vector.clear();
	
	if(root_node->GetNorthNode() != NULL)
		if(root_node->IsBrokenWall(MazeNodeWall_NORTH))
			if(!root_node->GetNorthNode()->IsVisited())
				maze_vector.push_back(root_node->GetNorthNode());
	
	if(root_node->GetSouthNode() != NULL)
		if(root_node->IsBrokenWall(MazeNodeWall_SOUTH))
			if(!root_node->GetSouthNode()->IsVisited())
				maze_vector.push_back(root_node->GetSouthNode());
	
	if(root_node->GetEastNode() != NULL)
		if(root_node->IsBrokenWall(MazeNodeWall_EAST))
			if(!root_node->GetEastNode()->IsVisited())
				maze_vector.push_back(root_node->GetEastNode());
	
	if(root_node->GetWestNode() != NULL)
		if(root_node->IsBrokenWall(MazeNodeWall_WEST))
			if(!root_node->GetWestNode()->IsVisited())
				maze_vector.push_back(root_node->GetWestNode());
}



MazeHTML::MazeHTML() : 
MazeGeneric()
{
	m_RenderType = MazeRenderType_HTML;
}
MazeHTML::~MazeHTML(){
	
}
void MazeHTML::Draw(){
	MazeNode *node;
	
	printf( "<html>\n<body>\n\t" );
    printf( "\n\t\t<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" >" );
	
	for(size_t row = 0; row < m_NumRows; row++){
		printf( "\n\t\t\t<tr>" );
		for(size_t column = 0; column < m_NumColumns; column++){
			printf( "\n\t\t\t\t<td height=\"8\" width=\"8\">" );
			
			node = MAZE_NODE(row, column);
            if(node->IsPartOfSolvedPath()) {
                printf("<img src=\"%sred.png\" width=\"8\" height=\"8\" alt=\"%zu => %sred\" />", cMazeNodeNames[node->GetType()], node->GetID(), cMazeNodeNames[node->GetType()]);
            } else {
                printf("<img src=\"%s.png\" width=\"8\" height=\"8\" alt=\"%zu => %s\" />", cMazeNodeNames[node->GetType()], node->GetID(), cMazeNodeNames[node->GetType()]);
            }
			
			
			printf( "</td>" );
		}
		printf("\n\t\t\t</tr>\n" );
	}
    printf( "\n\t\t</table>" );
    printf( "\n\t</body>\n</html>\n\n" );
}

void MazeHTML::Save() {
    
}


MazeSVG::MazeSVG() :
MazeGeneric()
{
    m_RenderType = MazeRenderType_SVG;
}
MazeSVG::~MazeSVG(){
    
}

/*
 string temp_path("out/puzzle/" + name + ".svg");
 if(solved)
 {
     temp_path = "out/solved/" + name + ".svg";
 }

 string cmd;

   
 system("mkdir -p out/puzzle");
 system("mkdir -p out/solved");

//    cmd = "mkdir -p out/puzzle/" + to_string(this->difficultyLevel) + "/";
//    system(cmd.c_str());
//    cmd = "mkdir -p out/solved/" + to_string(this->difficultyLevel) + "/";
//    system(cmd.c_str());
 

 ofstream outFile(temp_path, std::ofstream::out);
 outFile << svgheadText;

 for(int i=0;i<9;i++)
 {
   for(int j=0;j<9;j++)
   {
     if(this->grid[i][j]!=0)
     {
       int x = (50*j + 16);
       int y = (50*i + 35);

       stringstream text;
       text<<"<text x=\""<<x<<"\" y=\""<<y<<"\" style=\"font-weight:bold\" font-size=\"30px\">"<<this->grid[i][j]<<"</text>\n";

       outFile << text.rdbuf();
     }
   }
 }

   outFile << "<text x=\"10\" y=\"480\" style=\"font-weight:bold\" font-size=\"30px\">" << this->difficultyLevel<<"</text>\n";
//    outFile << "<image width=\"30\" height=\"30\" preserveAspectRatio=\"none\" xlink:href=\"/Users/jamesfolk/Work/Sudoku-Generator/level.png\" id=\"image728\" x=\"10\" y=\"455\" />\n";
   outFile << "</svg>";

   outFile.close();
 */
void MazeSVG::Draw(){
    MazeNode *node;
    int dim(50);
    
    std::string head = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg version="1.1"
     baseProfile="full"
)";
    head += "width=\"" + to_string(dim * m_NumColumns) + "\" height=\"" + to_string(dim * m_NumRows) + "\"\n";
    head += "xmlns=\"http://www.w3.org/2000/svg\" style=\"padding:10px;margin:10px\">\n";
    printf("%s", head.c_str());
    int x(0), y(0);
    for(size_t row = 0; row < m_NumRows; row++){
        for(size_t column = 0; column < m_NumColumns; column++){
            node = MAZE_NODE(row, column);
            bool isStart = (row == 0 && column == 0);
            bool isEnd = (row = (m_NumRows - 1) && column == (m_NumColumns - 1));
            printf("%s", DrawCell(node, x, y, dim, isStart, isEnd).c_str());
            x += dim;
        }
        x = 0;
        y += dim;
    }
    std::string tail = R"(
</svg>
)";
    printf("%s", tail.c_str());
}

string MazeSVG::GetNorth(int x, int y, int dim)const {
    return "<polyline points=\"" + to_string(x) + "," + to_string(y) + " " + to_string(x + dim) + "," + to_string(y) + "\" style=\"fill:none; stroke:black ; stroke-width:1\" />\n";
}

string MazeSVG::GetEast(int x, int y, int dim)const {
    return "<polyline points=\"" + to_string(x + dim) + "," + to_string(y) + " " + to_string(x + dim) + "," + to_string(y + dim) + "\" style=\"fill:none; stroke:black ; stroke-width:1\" />\n";
}

string MazeSVG::GetSouth(int x, int y, int dim)const {
    return "<polyline points=\"" + to_string(x) + "," + to_string(y + dim) + " " + to_string(x + dim) + "," + to_string(y + dim) + "\" style=\"fill:none; stroke:black ; stroke-width:1\" />\n";
}

string MazeSVG::GetWest(int x, int y, int dim)const {
    return "<polyline points=\"" + to_string(x) + "," + to_string(y) + " " + to_string(x) + "," + to_string(y + dim) + "\" style=\"fill:none; stroke:black ; stroke-width:1\" />\n";
}
std::string MazeSVG::DrawCell(MazeNode *node, int x, int y, int dim, bool isStart, bool isEnd) {
    std::string ret;
    
    ret += "<!-- ";
    ret += cMazeNodeNames[node->GetType()];
    ret += " -->\n";
    
    if(node->IsPartOfSolvedPath()) {
        ret += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(dim) + "\" height=\"" + to_string(dim) + "\" style=\"fill-opacity: .25;\" />\n";
    }
    
    if(string(cMazeNodeNames[node->GetType()]) == "0000") {
    }else if(string(cMazeNodeNames[node->GetType()]) == "0001") {
        ret += GetWest(x, y, dim);
    }else  if(string(cMazeNodeNames[node->GetType()]) == "0010") {
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
    }else if(string(cMazeNodeNames[node->GetType()]) == "0011") {
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "0100") {
        ret += GetEast(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "0101") {
        ret += GetEast(x, y, dim);
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "0110") {
        ret += GetEast(x, y, dim);
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
    }else if(string(cMazeNodeNames[node->GetType()]) == "0111") {
        ret += GetEast(x, y, dim);
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "1000") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
    }else if(string(cMazeNodeNames[node->GetType()]) == "1001") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "1010") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
    }else if(string(cMazeNodeNames[node->GetType()]) == "1011") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "1100") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        ret += GetEast(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "1101") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        ret += GetEast(x, y, dim);
        ret += GetWest(x, y, dim);
    }else if(string(cMazeNodeNames[node->GetType()]) == "1110") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        ret += GetEast(x, y, dim);
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
    }else if(string(cMazeNodeNames[node->GetType()]) == "1111") {
        if(isStart) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetNorth(x, y, dim);
        }
        ret += GetEast(x, y, dim);
        if(isEnd) {
            ret += GetDot(x, y, dim);
        } else {
            ret += GetSouth(x, y, dim);
        }
        ret += GetWest(x, y, dim);
    }
    
    return ret;
}

string MazeSVG::GetDot(int x, int y, int dim)const {
    return "<circle cx=\"" + to_string(x + ((float)dim / 2.f)) + "\" cy=\"" + to_string(y + ((float)dim / 2.f)) + "\" r=\"" + to_string((float)dim / 4.f) + "\" />\n";
}

void MazeSVG::Save() {
    MazeNode *node;
    int  dim(50);
    
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d_%m_%Y_%H_%M_%S");
    auto name = oss.str();

    string temp_path("out/puzzle/maze." + name + ".svg");
    if(m_IsFoundSolution)
    {
        temp_path = "out/solved/maze." + name + ".svg";
    }
    
    system("mkdir -p out/puzzle");
    system("mkdir -p out/solved");
    
    ofstream outFile(temp_path, std::ofstream::out);
    
    std::string head = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg version="1.1"
     baseProfile="full"
)";
    outFile << head;
    
    outFile <<  "width=\"" + to_string(dim * m_NumColumns) + "\" height=\"" + to_string(dim * m_NumRows) + "\"\n";
    outFile <<  "xmlns=\"http://www.w3.org/2000/svg\" style=\"padding:10px;margin:10px\">\n";
//    printf("%s", head.c_str());
    int x(0), y(0);
    for(size_t row = 0; row < m_NumRows; row++){
        for(size_t column = 0; column < m_NumColumns; column++){
            node = MAZE_NODE(row, column);
            bool isStart = (row == 0 && column == 0);
            bool isEnd = (row == (m_NumRows - 1) && column == (m_NumColumns - 1));
            outFile <<  DrawCell(node, x, y, dim, isStart, isEnd);
            x += dim;
        }
        x = 0;
        y += dim;
    }
    std::string tail = R"(
</svg>
)";
    outFile <<  tail.c_str();
    
    
    outFile.close();
}
