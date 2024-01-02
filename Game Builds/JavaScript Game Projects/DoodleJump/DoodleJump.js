//board
let board;
let boardWidth=360;
let boardHeight=576;
let context;

//doodler
let doodlerWidth = 46;
let doodlerHeight = 46;
let doodlerX = boardWidth/2 - doodlerWidth/2; //Gets middle width of the page in respect to the player
let doodlerY = boardHeight*(7/8) - doodlerHeight/2;//Gets 7/8 of the page and pushes the player upward by its height
let doodlerRightImg;
let doodlerLeftImg;

//physics
let velocityX = 0;
let velocityY = 0;

let doodler={
    img:null,
    x: doodlerX,
    y: doodlerY,
    width: doodlerWidth,
    height: doodlerHeight
}

window.onload = function(){
    board = document.getElementById("board");
    board.height = boardHeight;
    board.width = boardWidth;
    context = board.getContext("2d");

    //draw the doodler
    // context.fillStyle = "";
    // context.fillRect(doodler.x,doodler.y,doodler.width,doodler.height);
    
    //Get doodler's right image
    doodlerRightImg = new Image();
    doodlerRightImg.src = "D:/Unity repos/IMPORTANT-Projects/Game Builds/JavaScript Game Projects/doodler-right.png";
    doodler.img = doodlerRightImg;

    doodlerRightImg.onload=function(){
        context.drawImage(doodler.img,doodler.x,doodler.y,doodler.width,doodler.height);
    }

    //Get doodler's left image
     doodlerLeftImg = new Image();
     doodlerLeftImg.src = "D:/Unity repos/IMPORTANT-Projects/Game Builds/JavaScript Game Projects/doodler-left.png";
   
     requestAnimationFrame(update);
     document.addEventListener("keydown",moveDoodler);
}

function update()
{
    requestAnimationFrame(update);
    context.clearRect(0,0,board.width,board.height);
    doodler.x+=velocityX;
    //doodler.y+=velocityY;
    context.drawImage(doodler.img,doodler.x,doodler.y,doodler.width,doodler.height);
   
    if(doodler.x>boardWidth)
    {
        doodler.x = 0;
        doodler.velocityX*=-1;
    }
    else if(doodler.x<0)
    {
        doodler.x = boardWidth
        doodler.velocityX*=-1;
    }
}

function moveDoodler(e)
{
    if(e.code=="ArrowRight"||e.code=="KeyD")
    {
        velocityX = 2;
        doodler.img = doodlerRightImg;
    }
    else if (e.code=="ArrowLeft"||e.code=="KeyA")
    {
        velocityX = -2;
        doodler.img = doodlerLeftImg;
    }
    //  else if (e.code=="ArrowUp"||e.code=="KeyW")
    // {
    //      velocityY = -4;
    //  }
    //  else if (e.code=="ArrowDown"||e.code=="KeyS")
    //  {
    //      velocityY = 4;
    //  }

}