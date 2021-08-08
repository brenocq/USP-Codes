var myP = document.createElement("p")
myP.innerHTML = "Testing"
console.log(myP)

var qDiv = document.getElementById("q-all")
qDiv.appendChild(myP)
//document.getElementById("q-all").removeChild(myP)

console.log(qDiv.childNodes)
console.log(qDiv.childNodes[1].nodeName)
console.log(qDiv.childNodes[1].nodeType)
console.log(myP.parentNode)

document.getElementById("test-b").addEventListener("click", function(){
	document.getElementById("test-b").innerHTML = "Clicked";
	document.getElementById("test-b").setAttribute("class", "red");
})

document.getElementById("remove-b").addEventListener("click", function(){
	console.log(document.getElementById("test-b").getAttribute("class"))
	document.getElementById("test-b").removeAttribute("class");
})

var texto = document.createTextNode("Testing createText")
document.querySelector("h1").appendChild(texto)


var befP = document.createElement("p")
befP.textContent = "Created before"
document.querySelector("h1").parentNode.insertBefore(befP, document.querySelector("h1"))

var repP = document.createElement("p")
repP.textContent = "H1 replaced"
document.querySelector("body").replaceChild(repP, document.querySelector("h1"));

// Tipos de dados
// var -> global scope
// let -> local scope
