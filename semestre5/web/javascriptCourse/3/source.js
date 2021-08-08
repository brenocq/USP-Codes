//window.alert("Hello world!");
console.log("Testing")
console.log(document.getElementById("titulo"))
console.log(window)
console.log(screen.width)
console.log(navigator)

function add() {
	document.getElementById("titulo").innerHTML += " id"
	document.getElementsByClassName("car")[1].innerHTML += " class"
	document.getElementsByTagName("p")[1].innerHTML += " tag"
	document.querySelector("p").innerHTML += " (query p)"
	document.querySelector(".car").innerHTML += " (query class)"
	var test1 = document.getElementById("q-all").querySelectorAll("p")[1];
	test1.innerHTML += " (query all)"
	test1.style.color = "blue"
	console.log(test1)
	test1.id = "testId"
}

function avancar() {
	history.forward()
}
