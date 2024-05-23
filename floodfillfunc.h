#include<bits/stdc++.h>
#include "D:\micromouse\mms-cpp\API.h"
using namespace std;
#pragma once
using dqele = pair<pair<int, int>, int>; 

    void display_dqele(const dqele& element) {
        cout << "Coordinates: (" << element.first.first << ", " << element.first.second << ")\n";
        cout << "md: " << element.second << "\n";
    }

    bool valid_cell(int n,int xcoord){
        if(xcoord>=0 && xcoord<n)  
        {
            return true;
        }
        else{
            return false;
        }
    }



    void setandPushNextNeighbour(int &prevx, int &prevy, vector<vector<int>> &cost, int &prevmd, deque<dqele> &deq,vector<vector<int>> &horizontal_walls,vector<vector<int>> &vertical_walls){
         int n=cost[0].size();
         
          
        int next=prevmd+1;
        
        //n=9;
        if(valid_cell(n,prevx+1)){
            
                if(cost[prevx+1][prevy]==-1 && horizontal_walls[prevx+1][prevy]==0 )
                {
                cost[prevx+1][prevy]=prevmd+1;
                deq.push_back(make_pair(make_pair(prevx+1,prevy),next));
            
                }
            
        }

        if(valid_cell(n,prevx-1)){
                if(cost[prevx-1][prevy]==-1 && horizontal_walls[prevx][prevy]==0)
                {
                cost[prevx-1][prevy]=prevmd+1;
                deq.push_back(make_pair(make_pair(prevx-1,prevy),next));
                }  
        }    

        if(valid_cell(n,prevy+1)){
            
                if(cost[prevx][prevy+1]==-1 && vertical_walls[prevx][prevy]==0)
                {
                cost[prevx][prevy+1]=prevmd+1;
                deq.push_back(make_pair(make_pair(prevx,prevy+1),next));
                }
            }

        if(valid_cell(n,prevy-1))
        {
            
                if(cost[prevx][prevy-1]==-1 && vertical_walls[prevx][prevy-1]==0)
                {
                cost[prevx][prevy-1]=prevmd+1;
                deq.push_back(make_pair(make_pair(prevx,prevy-1),next));
                }
            
        }    
            
            
    }

    void resetMaze(int n, vector<vector<int>> &cost, deque<dqele> &deq)
    {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cost[i][j] = -1;
            }
        }
        int mid=n/2;
        cost[mid][mid]=0;
        cost[mid-1][mid]=0;
        cost[mid][mid-1]=0;
        cost[mid-1][mid-1]=0;

        
        //cout<<endl;
        deq.push_back(make_pair(make_pair(mid, mid), 0));
        deq.push_back(make_pair(make_pair(mid-1, mid), 0));
        deq.push_back(make_pair(make_pair(mid, mid-1), 0));
        deq.push_back(make_pair(make_pair(mid-1, mid-1), 0));
    }



    void floodfill(int n,vector<vector<int>> &cost, deque<dqele> &deq, vector<vector<int>> &horizontal_walls, vector<vector<int>> &vertical_walls)
    {
    while(deq.size()!=0)
        {
            //cout<<deq.size()<<endl;
            //cout<<"here";
            int prevmd,prevx,prevy,startx,starty;
            
            prevmd=deq.front().second;
            prevx=deq.front().first.first;
            prevy=deq.front().first.second;
            //cout<<prevmd<<" "<<prevx<<" "<<prevy<<endl;
            deq.pop_front();
           
            API::setText(prevy,n-1-prevx,to_string(cost[prevx][prevy]));   
            setandPushNextNeighbour(prevx,prevy,cost,prevmd,deq,horizontal_walls,vertical_walls);
           
            // cout << "Contents of deq:\n";
            // for (const auto& elem : deq) {
            // display_dqele(elem);
            // cout << "------\n";
            //     }
            // cout << endl;
            

        }   
    }

// int main(){
// int n;
// cin>>n;
// vector<vector<int>>cost(n,vector<int>(n,-1));
// deque<dqele> deq;
// resetMaze(n,cost,deq);
// floodfill(n,cost,deq);
// for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cout << cost[i][j] << " ";
//         }
//         cout << endl;
//     }

// return 0;
// }
