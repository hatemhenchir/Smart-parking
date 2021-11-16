function ChangerImage1(){
    var x=Math.floor(Math.random() * 2);
    

    if(x==1){
        document.getElementById("car1").src ="images/car1.png";
    }
    else{
        document.getElementById("car1").src ="images/free1.png";
    }

setTimeout("ChangerImage1()", 500)
}
function ChangerImage2(){
    var x=Math.floor(Math.random() * 2);
    

    if(x==1){
        document.getElementById("car2").src ="images/car1.png";
    }
    else{
        document.getElementById("car2").src ="images/free1.png";
    }

setTimeout("ChangerImage2()", 500)
}
function ChangerImage3(){
    var x=Math.floor(Math.random() * 2);
    

    if(x==1){
        document.getElementById("car3").src ="images/car1.png";
    }
    else{
        document.getElementById("car3").src ="images/free1.png";
    }

setTimeout("ChangerImage3()", 500)
}
function ChangerImage4(){
    var x=Math.floor(Math.random() * 2);
    

    if(x==1){
        document.getElementById("car4").src ="images/car1.png";
    }
    else{
        document.getElementById("car4").src ="images/free1.png";
    }

setTimeout("ChangerImage4()", 500)
}




// Charge la fonction
window.onload = function(){
ChangerImage1();
ChangerImage2();
ChangerImage3();
ChangerImage4();


}