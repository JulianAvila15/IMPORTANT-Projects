//Create a Vector data structure
class Vector extends Array{
    add(other)
    {
        return this.map((e,i) => e+ other[i])
    }
}

//Create a class for the Puzzle state
class PuzzleState{
    PuzzleState(){this.rows=0; this.cols=0;}
    PuzzleState(n,m){
        this.tiles = tiles[n*m];
        this.rows=n;
        this.cols=m;
    }
   
    //Copy Constructor
    PuzzleState(other)
    {
        if(other instanceof PuzzleState)
        {
            this.PuzzleState = other.PuzzleState
        }
        else
        {
            this.PuzzleState = other
        }
    }

    IsEqual(other)
    {
        return this.PuzzleState.tiles==other.tiles;
    }
    
    
    IsNotEqual(other)
    {
        return this.PuzzleState.tiles==other.tiles;
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
        return blank_position_row>0;
    }

    canMoveDown()
    {
        return blank_position_row +1 <this.rows;
    }

    canMoveLeft()
    {
        return blank_position_col>0;
    }

    canMoveRight()
    {
        return blank_position_col<cols-1;
    }

    moveBlankUp()
    {
        tempVal = this.tiles[((this.blank_position_row*this.cols)+this.blank_position_col)-this.rows]//get index of number on top of the blank's index
        this.tiles[((this.blank_position_row*this.cols)+this.blank_position_col)-this.rows] = this.tiles[((this.blank_position_row*this.cols))+this.blank_position_col];//Move blank position into the position above it
        this.tiles[(blank_position_row*cols)+blank_position_col] = tempVal;//Move number in the index above blank's position to the blank's position
        this.blank_position_row--;//decrement the row that the blank position is in

        return this;
    }

    moveBlankDown()
    {
        tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + this.rows];//get index of number below the blank's index
        this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + this.rows] = this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col];//Move blank position into the position below it
        this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = tempVal;//Move number in the index below blank's position to the blank's position
        this.blank_position_row++;//increment the row that the blank position is in

        return this;
    }

    moveBlankLeft()
    {
        tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) - 1];//get index of number to the left of the blank's index
        this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) - 1] = this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col];//Move blank to the left
        this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = tempVal; //move number in the index to the left of the blank's position
        this.blank_position_col--;//decrement the column that the blank position is in

        return this;
    }

    moveBlankRight()
    {
    tempVal = this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + 1];//get index of number to the right of the blank's index
    this.tiles[((this.blank_position_row * this.cols) + this.blank_position_col) + 1] = this.tiles[this.blank_position_row * this.cols+ this.blank_position_col];//Move blank to the right
   this.tiles[(this.blank_position_row * this.cols) + this.blank_position_col] = tempVal;//Move number in the index to the right of the blank's position
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

// //Get tiles
// let Tiles=[];