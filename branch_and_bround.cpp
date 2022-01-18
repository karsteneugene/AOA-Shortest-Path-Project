#include <bits/stdc++.h>
#define inf INT_MAX
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;


 

// initializing functions and variables
const int n = 7;
int finalpath[n];
bool visitednode[n];
int finalresult = INT_MAX;
void copy(int current_path[]);
int firstmin(double arr[n][n], int i);
int secondmin(double arr[n][n], int i);
void Recursion(double arr[n][n], int curr_bound, int curr_weight,int level, int current_path[]);
void solve(double arr[n][n]);
void displaymatrix(double arr[n][n]);
	 
		
 
// function for displaying the matrix
void displaymatrix(double arr[n][n])
{
	for(int row = 0 ; row < n ; row++)
	{
		cout << "{ ";
		for(int col = 0; col < n ; col++)
		{
			cout << arr[n][n] << ", ";
		}
		cout << " }"<< endl;
	}
}

// copying the current path's elements to the final path
void  copy(int current_path[])
{
	for(int i = 0; i < n ; i++)
	{
		finalpath[i] = current_path[i];
	}
 } 
 // finding the first minimum cost of the old node
int  firstmin(double arr[n][n], int row )
{
	double minval = INT_MAX;
	for(int num = 0 ; num < n  ; num++ )
	{
		if(arr[row][num]< minval&& num != row)
		{
			minval = arr[row][num];
		}
	}
	return minval;
}

// finding the second minimum cost of the old node
int  secondmin(double arr[n][n], int row)
{
	double first_node_min = INT_MAX; 
	double second_node_min = INT_MAX;
	for(int num = 0 ; num < n ; num++)
	{
		if(row == num)
		{
			continue;
		}
		if(arr[row][num]<= first_node_min)
		{
			second_node_min = first_node_min;
			first_node_min = arr[row][num];
		}
		// finding the second minimum value other than the first minimum value
		else if(arr[row][num] <= second_node_min && arr[row][num] != first_node_min)
		{
			 second_node_min = arr[row][num];
		}
    }
    return second_node_min;
}

void  Recursion(double arr[n][n], int curr_bound, int curr_weight,int level, int current_path[])
{
	// if we have reached the final node of the graph or traversed through all of vertices 
	 if (level==n)
    {
     // if the final value is not 0
        if (arr[current_path[level-1]][current_path[0]] != 0)
        {
      	//add the current result with the edge of the node you want to connect
            int currentresult = curr_weight + arr[current_path[level-1]][current_path[0]];
  
        	// copy the result to the final result from current result
            if (currentresult < finalresult)
            {
                copy(current_path);
                finalresult = currentresult;
            }
        }
        return;
    }
  

    for (int i=0; i<n; i++)
    {
       // if they haven't visited the node and chcek every element on the row
        if (arr[current_path[level-1]][i] != 0 && visitednode[i] == false)
        {
            int temp = curr_bound;
            curr_weight += arr[current_path[level-1]][i];
  
          // finding the least sum of the 2 nodes connected to the original vertice
            if (level==1)
              curr_bound -= ((firstmin(arr, current_path[level-1]) +firstmin(arr, i))/2);
            else
              curr_bound -= ((secondmin(arr, current_path[level-1]) +firstmin(arr, i))/2);
  
  			//updating the current path array
            if (curr_bound + curr_weight < finalresult)
            {
                current_path[level] = i;
                visitednode[i] = true;
  
               // continue the process with level+1 
                Recursion(arr, curr_bound, curr_weight, level+1,current_path);
            }
  
       		// updating the current weight and bound
            curr_weight -= arr[current_path[level-1]][i];
            curr_bound = temp;
  
         	// updatedthe visiting node array
            memset(visitednode, false, sizeof(visitednode));
            for (int j=0; j<=level-1; j++)
              {
              	visitednode[current_path[j]] = true;
			  }
        }
    }
 } 
 
void  solve(double arr[n][n], int start)
{
	// initialising current path
	 int currentpath[n];
  
  	// initialising currentbound
    int currentbound = 0;
    
	// resetting the arrays 
	memset(currentpath, -1, sizeof(currentpath));
    memset(visitednode, 0, sizeof(currentpath));
  
	// finding the first lower bound
    for (int i=0; i<n; i++)
    {
    	 currentbound += (firstmin(arr, i) + secondmin(arr, i));
	}
       
  
	// rounding off to the nearest whole number
    currentbound = (currentbound&1)? currentbound/2 + 1 : currentbound/2;
	
	// we  initialize the starting point
    visitednode[start] = true;
    currentpath[0] = start;
  
	// do the recursive function
    Recursion(arr, currentbound, 0, 1, currentpath);
}

 
// driver code
int main()
{
	int choice ;
	// initialize matrix
	double matrix[n][n] =  {
					{INT_MAX,151.0,442.4,560.0,876.6,780.6,1184.2},
					{151.0,INT_MAX,438.0,558.0 ,874.6 ,777.6 ,1180.0 },
					{442.4,438.0 ,INT_MAX,130.0 ,445.7 ,349.6 ,753.2},
					{560.0 ,558.0 ,130.0 ,INT_MAX,420.5 ,324.2 ,727.8 },
					{876.6 ,874.6 ,445.7 ,420.5 ,INT_MAX,96.8 ,529.8 },
					{780.6 , 777.6 ,349.6 ,324.2 ,96.8 ,INT_MAX,429.5 },
					{1184.2 ,1180.0 ,753.2,727.8 ,529.8 ,429.5 ,INT_MAX}};
	cout << "Do you want to use the dummy data?" << endl;
	cout << "0.Yes  1.No  2.End" << endl;
	cin >> choice ; 
	
	switch(choice)
	{
		//using the dummy data
		case 0:
			{
				int startingnode ;
			cout << "Where do you want to start?" << endl;
			cin >> startingnode;
			auto start = steady_clock::now();
			solve(matrix,startingnode);
			auto stop = steady_clock::now();
			auto duration = double(duration_cast<nanoseconds>(stop - start).count());
			cout <<"The runtime is " <<duration* 1E-9  << " seconds" <<endl;
			cout << "The shortest distance is " << finalresult<< endl;
			cout << "The path is ";
			for(int i = 0 ;  i<n; i++)
			{
				cout << finalpath[i] << " ";
			}
			}
			break;
		
		case 1:
			{
				//int dim;
				 //int temp ;
				 int start;
				//cout << "Type in your dimension"<< endl;
				//cin >> dim;	 
				int temp = n;
			 // making the martrix
					double matrixalt[n][n]= {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
					for(int i = 0 ; i <n; i ++)
					{
						for(int j = 0 ; j < n ; j++)
						{
							if(i == j )
							{
								matrixalt[i][j] = INT_MAX;
							}else{
								continue;
							}
						}
					}
				bool yes = true;
				// makes the user input the connecting nodes and the edges between them
				while(yes == true)
				{
					int i;
					int j;
					int next;
					double val;
					cout << "Please select a node" << endl;
					cin >> i;
					cout << "Please select the node you want to connect" << endl;
					cin >> j;
					cout << "Please input the value between the 2 nodes" << endl;
					cin >> val;
					
					matrixalt[i][j] = val;
					matrixalt[j][i] = val;
					
					cout << "Do you want to continue?" << endl;
					cout << "0 for yes 1 for no" << endl;
					cin >> next;
					if(next == 0)
					{yes = true;}
					else if(next == 1)
					{
					yes = false;
					break;
					}
					else{yes = false;}
				}
				// return matrix just in case
			 	 for(int i = 0 ; i < n ; i++)
			 {
			 		cout << "{ ";
			 	for(int j = 0; j < n ; j++)
			 	{
			 			cout << matrixalt[i][j] << ", ";
				 }
				 	cout << " }"<< endl;
			 }
				cout << "Please type in the starting point"<<endl;
				cin>> start;
				auto start1 = steady_clock::now();
				solve(matrixalt,start);
				 auto end1 = steady_clock::now();
				 auto duration1 = double(duration_cast<nanoseconds>(end1 - start1).count()); 
				cout <<"The runtime is " <<duration1* 1E-9  << " seconds" <<endl;
				cout << "The shortest distance is " << finalresult<< endl;
				cout << "The path is ";
				for(int i = 0 ;  i<n; i++)
				{
					cout << finalpath[i] << " ";
				}
				break;
			}
					
		case 2: 
			return 0;
		default:
			return 0;
		 	
	}
	

	return 0;
 } 


