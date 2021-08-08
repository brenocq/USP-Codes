//---------- Ex2 ----------//
// a
window.addEventListener('DOMContentLoaded', (event) => {
	// b
	document.getElementById("change_heading").innerHTML = "Choose your favorite!";

	// c
	let boxes = document.querySelectorAll("div")

	const showBoxColor = (box)=>{
		document.getElementsByClassName("selected")[0].innerHTML = box.className
	}

	const defaultText = ()=>{
		document.getElementsByClassName("selected")[0].innerHTML = "None!"
	}

	boxes.forEach((box)=>{
		box.addEventListener('mouseover', ()=>{showBoxColor(box)})
		box.addEventListener('mouseout', defaultText)
	})

	// d
	let section = document.querySelectorAll("section")[0]

	let boxRandom = document.createElement("div")
	boxRandom.className = "random"
	section.appendChild(boxRandom)

	const changeColor = ()=>{
		let randomColor = '#'+Math.floor(Math.random()*16777215).toString(16);
		document.getElementsByClassName("random")[0].style.backgroundColor = randomColor;
	}
	setInterval(changeColor, 500);
});


