#include "API.h"
#include "D:\micromouse\floodfillfunc.h"
using namespace std;


void log(const std::string& text) {
    std::cerr << text << std::endl;
}


void displayStack( std::stack<int> s) {
    std::stack<int> tempStack = s;  // Create a copy of the stack to avoid modifying the original
    while (!tempStack.empty()) {
        log(std::to_string(tempStack.top()));
        tempStack.pop();
    }
}


void storeWalls(int &orientation, int &ycoord, int &xcoord, vector<vector<int>> &horizontal_walls, vector<vector<int>> &vertical_walls,vector<vector<int>> &cost)
{
    int n=horizontal_walls.size();
    if(orientation==1)
    {
        if(API::wallFront())
        {
          
            horizontal_walls[ycoord][xcoord]=1; 
            API::setWall(xcoord,n-1-ycoord,'n');
          
        }
        if(valid_cell(horizontal_walls.size(),xcoord-1) && API::wallLeft() )
        {
            vertical_walls[ycoord][xcoord-1]=1;
            API::setWall(xcoord,n-1-ycoord,'w');
        }
        if(API::wallRight())
        {   
                vertical_walls[ycoord][xcoord]=1;
                API::setWall(xcoord,n-1-ycoord,'e');
        }
        
    }

     if(orientation==2)
    {
        if(API::wallFront())
        {
             vertical_walls[ycoord][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'e');
        }
        if(API::wallLeft())
        {
            horizontal_walls[ycoord][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'n');
        }
        if(valid_cell(vertical_walls.size(),ycoord+1) && API::wallRight() )
        {
            horizontal_walls[ycoord+1][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'s');
        }
    }


     if(orientation==3)
    {
        if(valid_cell(horizontal_walls.size(),ycoord+1) && API::wallFront())
        {
          
            horizontal_walls[ycoord+1][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'s');
        }
        if(API::wallLeft())
        {
            vertical_walls[ycoord][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'e');
        }
        if( valid_cell(horizontal_walls.size(),xcoord-1) && API::wallRight() )
        {
            vertical_walls[ycoord][xcoord-1]=1;
             API::setWall(xcoord,n-1-ycoord,'w');
        }
    }

    if(orientation==4)
    {
     if(valid_cell(horizontal_walls.size(),xcoord-1) && API::wallFront() )
        {
            
                vertical_walls[ycoord][xcoord-1]=1;
            
            
             API::setWall(xcoord,n-1-ycoord,'w');
        }
        if(valid_cell(horizontal_walls.size(),ycoord+1) && API::wallLeft())
        {
            horizontal_walls[ycoord+1][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'s');
        }
        if(API::wallRight())
        {
            horizontal_walls[ycoord][xcoord]=1;
             API::setWall(xcoord,n-1-ycoord,'n');
        }   
    }
    
}




void logsameline(const std::string& text) {
    std::cerr << text;
}

void logArray(vector<vector<int>> &horizontal_walls,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            logsameline(to_string(horizontal_walls[i][j]) + ", ");
        }
        log(" ");
    }  
}

void changeOrientation(int turn,int &ori)
{
    if(turn==2)
    {
        if(ori==1 or ori==2 or ori==3)
        {
            ori+=1;
        }
        else if(ori==4)
        {
            ori=1;
        }
    }
    if(turn==3)
    {
        if(ori==4 or ori==2 or ori==3)
        {
            ori-=1;
        }
        else if(ori==1)
        {
            ori=4;
        }
    }
    log("orientation is: " +  to_string(ori));
}

void returntostart(stack<int> &returnpath,int &orientation)
{
    API::turnRight();
    API::turnRight();
    changeOrientation(2,orientation);
    changeOrientation(2,orientation);
     while(returnpath.size()!=0)
    {
        
        if(!returnpath.empty() && returnpath.top()==1)
        {
           API::moveForward();
           returnpath.pop();
        }
        else if(!returnpath.empty() && returnpath.top()==2)
        {
            API::turnLeft();
            changeOrientation(3,orientation);
            returnpath.pop();
        }
        else if(!returnpath.empty() && returnpath.top()==3)
        {
            API::turnRight();
            changeOrientation(2,orientation);
            returnpath.pop();
        }
        
    }
    

}


void execfloodfill(int n,int &orientation, int &ycoord, int &xcoord, vector<vector<int>> &horizontal_walls, vector<vector<int>> &vertical_walls,vector<vector<int>> &cost,stack<int> &returnpath,deque<dqele> &deq){
     while (cost[ycoord][xcoord] != 0) {
    
    storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);
    log("maze coordinates are: " + to_string(xcoord) + " " + to_string(n - 1 - ycoord));
    log("horizontal walls are: ");
    log(" ");
    logArray(horizontal_walls, n);
    log("vertical walls are :");
    log(" ");
    logArray(vertical_walls, n);
    log(" ");
    logArray(cost, n);
    log(" ");



    if (valid_cell(cost.size(), xcoord - 1) && vertical_walls[ycoord][xcoord - 1] == 0 && cost[ycoord][xcoord - 1] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 4) {
            if(orientation!=1){
                API::turnRight();
                changeOrientation(2, orientation);
                returnpath.push(2);
            }
            
            else{
                API::turnLeft();
                changeOrientation(3,orientation);
                returnpath.push(3);
            }
        }
        xcoord -= 1;

        API::moveForward();
        returnpath.push(1);
    } else if (valid_cell(n, ycoord - 1) && horizontal_walls[ycoord][xcoord] == 0  && cost[ycoord][xcoord] > cost[ycoord - 1][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 1) {
            if(orientation!=2){
                API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
             else{
                API::turnLeft();
                changeOrientation(3,orientation);
                returnpath.push(3);
            }

        }

        ycoord -= 1;
        API::moveForward();
        returnpath.push(1);


    } else if (valid_cell(cost.size(),ycoord+1) && horizontal_walls[ycoord + 1][xcoord] == 0 && cost[ycoord + 1][xcoord] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 3) {
            if(orientation!=4){
                 API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
           else{
            API::turnLeft();
            changeOrientation(3,orientation);
            returnpath.push(3);
           }
        }
        ycoord += 1;
        API::moveForward();
        returnpath.push(1);
    } else if (valid_cell(n,xcoord+1) && vertical_walls[ycoord][xcoord] == 0 && cost[ycoord][xcoord + 1] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 2) {
            if(orientation!=3){
                API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
            else{
                API::turnLeft();
            changeOrientation(3,orientation);
            returnpath.push(3);
            }
        }
        xcoord += 1;

        API::moveForward();
        returnpath.push(1);
    }
    else{resetMaze(n,cost,deq);
        floodfill(n,cost,deq,horizontal_walls,vertical_walls);}
        
    
  
}
}

void execreturnfloodfill(int n,int &orientation, int &ycoord, int &xcoord, vector<vector<int>> &horizontal_walls, vector<vector<int>> &vertical_walls,vector<vector<int>> &cost,stack<int> &returnpath,deque<dqele> &deq){
     int starty=n-1;
    int startx=0;
     while (cost[ycoord][xcoord] != 0) {
    
    storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);
    log("maze coordinates are: " + to_string(xcoord) + " " + to_string(n - 1 - ycoord));
    log("horizontal walls are: ");
    log(" ");
    logArray(horizontal_walls, n);
    log("vertical walls are :");
    log(" ");
    logArray(vertical_walls, n);
    log(" ");
    logArray(cost, n);
    log(" ");



    if (valid_cell(cost.size(), xcoord - 1) && vertical_walls[ycoord][xcoord - 1] == 0 && cost[ycoord][xcoord - 1] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 4) {
            if(orientation!=1){
                API::turnRight();
                changeOrientation(2, orientation);
                returnpath.push(2);
            }
            
            else{
                API::turnLeft();
                changeOrientation(3,orientation);
                returnpath.push(3);
            }
        }
        xcoord -= 1;

        API::moveForward();
        returnpath.push(1);
    } else if (valid_cell(n, ycoord - 1) && horizontal_walls[ycoord][xcoord] == 0  && cost[ycoord][xcoord] > cost[ycoord - 1][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 1) {
            if(orientation!=2){
                API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
             else{
                API::turnLeft();
                changeOrientation(3,orientation);
                returnpath.push(3);
            }

        }

        ycoord -= 1;
        API::moveForward();
        returnpath.push(1);


    } else if (valid_cell(cost.size(),ycoord+1) && horizontal_walls[ycoord + 1][xcoord] == 0 && cost[ycoord + 1][xcoord] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 3) {
            if(orientation!=4){
                 API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
           else{
            API::turnLeft();
            changeOrientation(3,orientation);
            returnpath.push(3);
           }
        }
        ycoord += 1;
        API::moveForward();
        returnpath.push(1);
    } else if (valid_cell(n,xcoord+1) && vertical_walls[ycoord][xcoord] == 0 && cost[ycoord][xcoord + 1] < cost[ycoord][xcoord]) {
        storeWalls(orientation, ycoord, xcoord, horizontal_walls, vertical_walls, cost);

        while (orientation != 2) {
            if(orientation!=3){
                API::turnRight();
            changeOrientation(2, orientation);
            returnpath.push(2);
            }
            else{
                API::turnLeft();
            changeOrientation(3,orientation);
            returnpath.push(3);
            }
        }
        xcoord += 1;

        API::moveForward();
        returnpath.push(1);
    }
    else{
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = -1;
            }
        }
        cost[starty][startx]=0;
    deq.push_back(make_pair(make_pair(starty, startx), 0));
    floodfill(n,cost,deq,horizontal_walls,vertical_walls);
}
}
}
int main(int argc, char* argv[]) {
    
    int orientation=1;
    int n=API::mazeWidth( );
    for(int i=0;i<n;i++)
    {
        API::setWall(i,0,'s');      
        API::setWall(0,i,'w');
        API::setWall(n-1,i,'e');
        API::setWall(i,n-1,'n');
    }
    stack<int> returnpath;
    int ycoord=n-1;int xcoord=0;
    log("Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
   
    vector<vector<int>> vertical_walls(n,vector<int>(n,0));
     vector<vector<int>> horizontal_walls(n,vector<int>(n,0));

    vector<vector<int>>cost(n,vector<int>(n,-1));
    deque<dqele> deq;
    
    
    resetMaze(n,cost,deq);
    floodfill(n,cost,deq,horizontal_walls,vertical_walls);
    
    
    execfloodfill(n,orientation,ycoord,xcoord,horizontal_walls,vertical_walls,cost,returnpath,deq);
   
 
    log("end");
    if(cost[ycoord][xcoord]==0)
    {
        storeWalls(orientation,ycoord,xcoord,horizontal_walls,vertical_walls,cost);
        log("maze coordinates are: " + to_string(xcoord) + " " + to_string(n-1-ycoord));
        log("horizontal walls are: ");
        log(" ");
        logArray(horizontal_walls,n);
        log("vertical walls are :");
        log(" ");
        logArray(vertical_walls,n);

         //dynamically update walls

        

         resetMaze(n,cost,deq);
        floodfill(n,cost,deq,horizontal_walls,vertical_walls);

      
    }

    vector<int> shortestpath;unordered_set<int> shortestpathset;
    while(shortestpath.size()==shortestpathset.size()){

    int starty=n-1;
    int startx=0;
    resetMaze(n,cost,deq);
    shortestpath.push_back(cost[starty][startx]);
    shortestpathset.insert(cost[starty][startx]);
    floodfill(n,cost,deq,horizontal_walls,vertical_walls);
    execfloodfill(n,orientation,ycoord,xcoord,horizontal_walls,vertical_walls,cost,returnpath,deq);
     
    if(shortestpath.size()!=shortestpathset.size()){
        continue;
    }

    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = -1;
            }
        }
    cost[starty][startx]=0;
    deq.push_back(make_pair(make_pair(starty, startx), 0));
    floodfill(n,cost,deq,horizontal_walls,vertical_walls);
    shortestpath.push_back(cost[starty][startx]);
    shortestpathset.insert(cost[starty][startx]);
    execreturnfloodfill(n,orientation,ycoord,xcoord,horizontal_walls,vertical_walls,cost,returnpath,deq);   
    }
      resetMaze(n,cost,deq);
     floodfill(n,cost,deq,horizontal_walls,vertical_walls);
}

