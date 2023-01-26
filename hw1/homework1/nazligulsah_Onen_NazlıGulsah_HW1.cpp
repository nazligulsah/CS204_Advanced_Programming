//  Created by Nazlı Gülşah Önen on 8.10.2020.
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>


using namespace std;


bool isValid(vector<vector<int>> &vect, vector<vector<int>> &constVect) {
    //row check
    for(int r = 0; r < vect.size(); r++) {
        for (int i = 0; i < vect.size() - 1; i++) {
            for (int j = i + 1; j < vect.size(); j++) {
                if (vect[r][i] == vect[r][j])
                    if (vect[r][i] !=-1 && vect[r][j] != -1)
                        return false;
            }
        }
    }
  //column check
    for(int c = 0; c < vect.size(); c++) {
        for (int i = 0; i < vect.size() - 1; i++) {
            for (int j = i + 1; j < vect.size(); j++) {
                if (vect[i][c] == vect[j][c])
                    if (vect[i][c] !=-1 && vect[j][c] != -1)
                        return false;
            }
        }
    }

    for(int i = 0; i < constVect.size(); i++) {
        int x1 = constVect[i][0];
        int y1 = constVect[i][1];
        int x2 = constVect[i][2];
        int y2 = constVect[i][3];

        if(vect[x1-1][y1-1]  != -1 && vect[x2-1][y2-1]  != -1)
            if(vect[x1-1][y1-1] <= vect[x2-1][y2-1])
                return false;

    }

        return true;
}



bool isComplete(vector<vector<int>> &vect) {
    for(int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect.size(); j++) {
            if (vect[i][j] == -1 )
                return false;
        }
    }
        return true;
}

void setValue(vector<vector<int>> &vect, int x, int y, int i ) {
    vect[x][y] = i;
}

void x_finder(vector<vector<int>> &vect, int *xp, int *yp){
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if (vect[i][j] == -1){
                *xp = i;
                *yp = j;
            }
        }
    }
}

bool solver(vector<vector<int>> &vect, vector<vector<int>> &constVect){
    if (!isValid(vect, constVect)){return false;}
    if (isComplete(vect)){return true;}

    int x ;
    int y ;
    x_finder(vect, &x, &y);


    for (int i = 1; i <= vect.size(); i++){
        setValue(vect, x, y, i);
        if (solver(vect, constVect)){
            return true;
        }
    }
    setValue(vect, x, y, 0);
    return false;
}


void CheckFileSize(ifstream &file, int &n, bool &t){

    string sn;
    getline(file,sn);
    n = stoi(sn);
    // cout << "n=" << s << endl;
    int count=0;
    while(!file.eof()){
        string line;
        getline(file,line);
        count ++;
    }
    //  cout << count << endl;
    if (n+1 == count){
        t = true;
    }
    else if (n+1 > count){
        cout << "File contains less lines than size" << endl;
    }
    else{
        cout << "File contains more lines than size" << endl;

    }
    file.seekg(0);
    file.clear();
}


int main() {


    int n =0;
    int m=0;
    bool t= false; // control the checkfilesize
    bool s = false; // control the checkcontsize
    bool v = true; // check value whether out of matriz size
    bool z = true;
    int x1, x2, y1, y2;

    string boardFileName ;
    string constFileName ;
    cout << "Enter the board file: ";       // open the board file
    cin >> boardFileName;
    ifstream input;
    input.open(boardFileName.c_str());
    if (input.fail()){
        cout << boardFileName << endl;
        cout << "Board file cannot be open!" << endl;
    }

    cout << "Enter the constraint file:";       // open the constraint file
    cin >> constFileName ;
    ifstream in ;
    in.open(constFileName.c_str());
    if (in.fail()){
        cout << "Constraint file cannot be open!"<< endl;
    }

    CheckFileSize(input, n, t);
    string sn;
    getline(in,sn);
    m = stoi(sn);
    int count=0;
    string line;
    while(getline(in,line)){
        count ++;
    }

    if (m == count){
        s = true;
    }
    else if (m > count){
        cout << "There are less constraints then previously stated" << endl;
    }
    else{
        cout << "There are more constraints then previously stated" << endl;
    }
    in.seekg(0);
    in.clear();

// create a matrix nxn and read board file put the number in the matrix
    input.seekg(0);
    input.clear();
    vector<vector<int>> vect(n, vector<int>(n));   // Create a matrix for board
    input >> n;
    vect[n][n];
    string board;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n ; j++) {
            input >> board;
            if (board == "X" ){           // if value of board X put 0 in the matrix
                vect[i][j] = -1 ;

            }
            else{
                vect[i][j] = stoi(board);
            }}
    }

    in.seekg(0);
    in.clear();
    vector<vector<int>> constVect(m, vector<int>(4));   // Create a matrix for board
    in >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 4 ; j++) {
            in >> constVect[i][j];
        }
    }



    // Check whether value is out of matrix size or not
    for(int i=0; i < n; i++){
        for(int j=0; j < n ; j++){
            if (vect[i][j] != -1){
                if (!( 0 <= vect[i][j] && vect[i][j] <= n)){
                    cout << "Value " << vect[i][j] << " is out of matrix size "<< endl;
                    v = false;
                }
            }
        }
    }
    in.clear();
    in.seekg(0);
    // the number in the constraint file must be between 1 and n
    int p;
    in >> p;
    while(in >> p){
        if (1 <= p && p <= n){
        }
        else {
            cout << m <<  " does not match board cordinates"<< endl;
        }
    }
    in.clear();
    in.seekg(0);


    // is there any repeating value in the row or col
    int num  = 0;
    z = false;
    for(int i=0; i < n; i++){
        while(num == 0 && !z){
            for (int j =0; j < n; j++){
                for(int k= j+1; k < n ; k ++){
                    if (vect[i][j] == vect[i][k] && vect[i][j] != -1){
                        cout << "There is a value repeating in same row" << endl;
                        num++;
                        z = false;
                    }
                    else if(vect[i][j] == vect[k][j] && vect[i][j] != -1){
                        cout << "There is a value repeating in same column" << endl;
                        num ++;
                        z = false;
                    }
                    else
                        z = true;
                }
            }
        }}


   if( s && t && v && z ){



        bool solve = solver(vect, constVect);

        for (int i = 0; i < vect.size(); i++) {
            for (int j = 0; j < vect[i].size(); j++) {
                cout << vect[i][j] << " ";
            }
            cout << endl;
        }
    }

    input.close();
    in.close();



}

