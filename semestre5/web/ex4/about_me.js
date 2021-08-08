//---------- Questão 1 ----------//
document.querySelector("body").style.fontFamily = "Roboto"
console.log(document.querySelector("body").style)
//---------- Questão 2 ----------//
document.querySelector("#nickname").textContent = "Brenocq"
document.querySelector("#favorites").textContent = "C++, robots, computer graphics"
document.querySelector("#hometown").textContent = "Salvador - BA"
//---------- Questão 3 ----------//
let myImage = document.createElement("img")
myImage.src = "breno.jpg"
myImage.height = 100
let list = document.querySelector("ul")
list.parentNode.insertBefore(myImage, list)
