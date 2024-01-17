//Create a Vector data structure
class Vector extends Array{
    add(other)
    {
        return this.map((e,i) => e+ other[i])
    }
}

//Create a class for the Puzzle state
class PuzzleState{
    constructor(n,m){
        this.tiles = [n*m];
        this.rows=n;
        this.cols=m;
    }
    SetEqual(other)
    {
        this.tiles=[];
        for(i=0;i<numOfTiles;i++)
        {
            this.tiles.push(other.tiles[i]);
        }
    }
    IsEqual(other)
    {
        for(i=0;i<numOfTiles;i++)
        {
            if(this.tiles[i]!=other.tiles[i])
            return false;
        }
    
        return true;
    }

    Size()
    {
        return this.tiles.size;
    }

    GetColsandRows()
    {
        return this.cols;
    }

    GetEvaluation()
    {
        return this.f;
    }

    getheuristic()
    {
        return this.h;
    }
    getG()
    {
        return this.g;
    }
    setG(g)
    {
        this.g = g;
    }
    setHeuristic(h)
    {
	    this.h = h;
    }
    setEvaluation(f)
    {
	    this.f = f;
    }
    getTiles()
    {
        return this.tiles;
    }

    isNullState()
    {
        return rows==0;
    }

    canMoveUp()
    {
        return this.blank_position_row>0;
    }

    canMoveDown()
    {
        return this.blank_position_row +1 <this.rows;
    }

    canMoveLeft()
    {
        return this.blank_position_col>0;
    }

    canMoveRight()
    {
        return this.blank_position_col<this.cols-1;
    }

    moveBlankUp()
    {
        this.tempVal = this.tiles[((this.blank_position_row*this.cols)+this.blank_position_col)-this.rows]//get index of number on top of the blank's index
        this.tiles[((this.blank_position_row*this.cols)+this.blank_position_col)-this.rows] = this.tiles[((this.blank_position_row*this.cols))+this.blank_position_col];//Move blank position into the position above it
        this.tiles[(this.blank_position_row*this.cols)+this.blank_position_col] = this.tempVal;//Move number in the index above blank's position to the blank's position
        this.blank_position_row--;//decrement the row that the blank position is in

        return this;
    }

    moveBlankDown()
    {
        this.tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + this.rows];//get index of number below the blank's index
        this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + this.rows] = this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col];//Move blank position into the position below it
        this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = this.tempVal;//Move number in the index below blank's position to the blank's position
        this.blank_position_row++;//increment the row that the blank position is in

        return this;
    }

    moveBlankLeft()
    {
        this.tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) - 1];//get index of number to the left of the blank's index
        this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) - 1] = this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col];//Move blank to the left
        this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = this.tempVal; //move number in the index to the left of the blank's position
        this.blank_position_col--;//decrement the column that the blank position is in

        return this;
    }

    moveBlankRight()
    {
    this.tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + 1];//get index of number to the right of the blank's index
    this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + 1] = this.tiles[this.blank_position_row * this.cols+ this.blank_position_col];//Move blank to the right
   this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = this.tempVal;//Move number in the index to the right of the blank's position
    this.blank_position_col++;//increment the column that the blank position is in

    return this;
    }

    IsGreater(other)
    {
        return this.f>other.f;
    }

    IsLess(other)
    {
        return this.f<other.f;
    }
}

//Create a class for the Puzzle move 
class PuzzleMove{
    PuzzleMove(){ }
    PuzzleMove(s,p,m)
    {
        this.state=s;
        this.parent=p;
        this.move = m;
    }

    getState()
    {
        return this.state;
    }

    getParent()
    {
        return this.parent;
    }

    getMoveName()
    {
        return this.move;
    }
}

//board
let initial_state;
let goal_state;
let rows_and_cols=3;
let solution = [];
let ids=[];
let numOfTiles=9;

window.onload = function(){
  
}

function Main()
{   
    initial_state=new PuzzleState(rows_and_cols,rows_and_cols);

    goal_state= new PuzzleState(rows_and_cols,rows_and_cols);

    ids.push("b1");
    ids.push("b2");
    ids.push("b3");
    ids.push("b4");
    ids.push("b5");
    ids.push("b6");
    ids.push("b7");
    ids.push("b8");
    ids.push("b9");


    //Make goal puzzle state
     for(i=0;i<numOfTiles-1;i++)
     {
         goal_state.tiles[i]=i+1;
     }

     goal_state.tiles.push(0);

     //Retrieve data
     for(i=0;i<numOfTiles;i++)
     {
         initial_state.tiles[i] = document.getElementById(ids[i]).value;

         if(initial_state.tiles[i]==0)
         {
            initial_state.blank_position_col = i%rows_and_cols;
            initial_state.blank_position_row = Math.floor(i/rows_and_cols);
         }
     }

     //Solve Puzzle
     Solve();

    //show solution
    if(solution.length>0)
    RunThroughSolution(solution);

    
}

function Solve()
{
     //base case, inital is already equal to the goal state
     if(initial_state.IsEqual(goal_state))
     document.getElementById("demo").innerHTML="Solved, inital state already equals the goal state";

}

function DisplayBoard(boardToBeDisplayed){
    
    for(i=0;i<numOfTiles;i++)
    {
      document.getElementById(ids[i]).value =  boardToBeDisplayed.tiles[i];
    }

}

function RunThroughSolution(puzzleSolution)
{
for(let i=0; i<puzzleSolution.length;i++)
{
     setTimeout(() => {
        DisplayBoard(puzzleSolution[i]);
          }, 1000*i);
}
}

