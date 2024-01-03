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
let velocityY = 0;//Doodler jump speed
let initialVelocityY = -8;//starting velocity Y
let gravity = .4;

//platforms
let platformArray = []; // create an empty platform array
let platformWidth = 60;
let platformHeight = 18;
let platformImg;  //load image for platform

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
    velocityY = initialVelocityY;

    //draw the doodler
    // context.fillStyle = "";
    // context.fillRect(doodler.x,doodler.y,doodler.width,doodler.height);
    
    //Get doodler's right image
    doodlerRightImg = new Image();
    doodlerRightImg.src = "D:/Git Repositories/IMPORTANT-Projects/Game Builds/JavaScript Game Projects/doodler-right.png";
    doodler.img = doodlerRightImg;

    doodlerRightImg.onload=function(){
        context.drawImage(doodler.img,doodler.x,doodler.y,doodler.width,doodler.height);
    }

    //Get doodler's left image
     doodlerLeftImg = new Image();
     doodlerLeftImg.src = "D:/Git Repositories/IMPORTANT-Projects/Game Builds/JavaScript Game Projects/doodler-left.png";

     //Get platform image
     platformImg = new Image();
     platformImg.src = "D:/Git Repositories/IMPORTANT-Projects/Game Builds/JavaScript Game Projects/platform.png";
 
    
    placePlatforms();
    requestAnimationFrame(update);
     document.addEventListener("keydown",moveDoodler);
}

function update()
{
    requestAnimationFrame(update);
    context.clearRect(0,0,board.width,board.height);
  
    context.drawImage(doodler.img,doodler.x,doodler.y,doodler.width,doodler.height);
   
    //If doodler goes off screen bring it back to the canvas
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

    doodler.x+=velocityX;
    velocityY+=gravity;
    doodler.y+=velocityY;
    

    for(let i=0; i<platformArray.length; i++)
    {
        let platform=platformArray[i];
        //if doodler is jumping and has not yet reached 3/4's of the board height, slide the platforms downward
        if(velocityY<0 && doodler.y<=boardHeight*3/4)
        {
            platform.y-=initialVelocityY/2;
        }

         //detect collision between platform and doodler
         if(DetectCollision(doodler,platform)&&velocityY>=0)
         velocityY = initialVelocityY;//jump

        context.drawImage(platform.img,platform.x,platform.y,platform.width,platform.height);
    }
        //If a platform has fallen off of the board remove it from the array
         while(platformArray.length>0&&platformArray[0].y>boardHeight)
         {
            platformArray.shift();
            CreateNewPlatform();
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
        velocityX = -2
        ;
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

function placePlatforms()
{
    platformArray = [];

    //Starting platforms
    let platform = {
        img: platformImg,
        x: boardWidth/2,
        y: boardHeight-50,
        width: platformWidth,
        height:platformHeight
    }
    platformArray.push(platform);

    // platform = {
    //     img: platformImg,
    //     x: boardWidth/2,
    //     y: boardHeight-150,
    //     width: platformWidth,
    //     height:platformHeight
    // }
    // platformArray.push(platform);

    //Create randomized platforms
    for(let i=0; i<6;i++)
    {
        platform = {
            img: platformImg,
            x: randomXorY(0,(boardWidth*(3/4))),
            y: boardHeight-75*i-150,
            width: platformWidth,
            height:platformHeight
        }
        platformArray.push(platform);
    }
}

//Detect the collision between doodler and platform
function DetectCollision(a,b){
    return a.x < b.x + b.width&& // object a's x position is less than object b's x position + its width, meaning object a resides between the object b's xpos and width
         a.x+a.width> b.x && // object a's x position + width is greater than object b's x position, same as above but object b resides between object a's x pos and width
           a.y < b.y+b.width&& // object a's y position is less than object b's y position + its height, meaning object a resides between the object b's ypos and height
           a.y+a.height>b.y // object a's y position + height is greater than object b's y position, meaning object b resides between the object a's xpos and height
}


function CreateNewPlatform(){
    
    platform = {
        img: platformImg,
        x: randomXorY(0,(boardWidth*(3/4))),
        y: boardWidth*1/4,
        width: platformWidth,
        height:platformHeight
    }
    platformArray.push(platform);
}
function randomXorY(min, max) {
    return Math.random() * (max - min) + min;
}